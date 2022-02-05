#include <generated/autoconf.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/device.h>
#include <linux/err.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/math64.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("whitfijs");


#define TACH_PULSE_COUNTER_GPIO             6
#define TACH_PULSE_COUNTER_GPIO_DESC        "Tach Pulse Interrupt Pin"
#define TACH_PULSE_COUNTER_GPIO_DEVICE_DESC "Tach Pulse counter"

#define PULSE_SPACING_NUM_SAMPLES           4
#define MAX_PULSE_SPACING_NUM_SAMPLES		32

#define PULSE_SPACING_TIMEOUT_MSEC			200
#define PULSE_SPACING_MIN_DEFAULT_USEC 		2500		

#define VSS_PULSE_COUNTER_GPIO				19
#define VSS_PULSE_COUNTER_GPIO_DESC			"VSS Pulse Interrupt Pin"
#define VSS_PULSE_COUNTER_GPIO_DEVICE_DESC	"VSS Pulse Counter"

static struct class *s_pDeviceClass;

static struct device *s_pTachDeviceObject;
static struct device *s_pVssDeviceObject;

typedef struct {
	struct device * dev;
	 __u16 gpio_irq_num;
	 __u32 count_total;
	 __u64 spacing[MAX_PULSE_SPACING_NUM_SAMPLES];
	 __u64 spacing_index;
	 __u64 spacing_avg;
	 __u64 spacing_avg_num_samples;
	 __u64 spacing_min;

	 ktime_t last;
	 int last_interrupt;
	
	struct timer_list timeout_timer;
} pulse_counter_t;

static pulse_counter_t tach_pulse_counter;
static pulse_counter_t vss_pulse_counter;

void init_pulse_counter(pulse_counter_t * counter, int num_avg_samples, int spacing_min) {
	// set to default values
	counter->gpio_irq_num = 0;
	counter->count_total = 0;
	counter->spacing_index = 0;
	counter->spacing_avg = 0;
	counter->spacing_avg_num_samples = num_avg_samples;
	counter->spacing_min = spacing_min;
}

pulse_counter_t * get_counter_from_device(struct device * dev) {
	if (dev == tach_pulse_counter.dev) {
		return &tach_pulse_counter;
	} else if (dev == vss_pulse_counter.dev) {
		return &vss_pulse_counter;
	}

	return NULL;
}

void restart_timeout_timer(struct timer_list * timeout_timer, unsigned long timeout_msec) {
	mod_timer (timeout_timer, jiffies + ( msecs_to_jiffies(timeout_msec)));	
}

void timeout_timer_function(struct timer_list *timer) {
	pulse_counter_t * counter;

	if (timer == &tach_pulse_counter.timeout_timer) {
		counter = &tach_pulse_counter;
	} else if (timer == &vss_pulse_counter.timeout_timer) {
		counter = &vss_pulse_counter;
	}

	// reset pulse spacing
	counter->spacing_avg = 0;
	counter->spacing_index = 0;
	for (int i = 0; i < PULSE_SPACING_NUM_SAMPLES; i++) {
		counter->spacing[i] = 0;
	}

	// restart the timer
	restart_timeout_timer(timer, PULSE_SPACING_TIMEOUT_MSEC);
}

static irqreturn_t pulse_irq_handler(__u32 irq, void * dev_id, struct pt_regs * regs) {
	pulse_counter_t * counter;
	ktime_t now;

	if (irq == tach_pulse_counter.gpio_irq_num) {
		counter = &tach_pulse_counter;
	} else if (irq == vss_pulse_counter.gpio_irq_num) {
		counter = &vss_pulse_counter;
	} else {
		// dip out
		return IRQ_HANDLED;
	}

	if (counter->last_interrupt == 0) {
		counter->last = ktime_get();
		counter->last_interrupt = jiffies;
	} else {
		now = ktime_get();
		__u64 now_nsec = ktime_to_ns(now);
		__u64 last_nsec = ktime_to_ns(counter->last);
		__u64 spacing = (now_nsec - last_nsec);

		// skip too short pulses
		if (spacing < counter->spacing_min) {
			return IRQ_HANDLED;
			spacing = counter->spacing_min;
		}

		// accumulate
		counter->spacing[counter->spacing_index++] = spacing;
		counter->spacing_index = counter->spacing_index & (counter->spacing_avg_num_samples - 1);

		if (counter->count_total++ > counter->spacing_avg_num_samples) {
			__u64 avg = 0;
			for (int i = 0; i < counter->spacing_avg_num_samples; i++) {
				avg += counter->spacing[i];
			}
			counter->spacing_avg = div_u64(avg, counter->spacing_avg_num_samples);
		}

		counter->last = now;
	}	

	restart_timeout_timer(&counter->timeout_timer, PULSE_SPACING_TIMEOUT_MSEC);

    return IRQ_HANDLED;
}

static ssize_t set_pulse_count_callback(struct device* dev ,struct device_attribute* attr, const char * buf, size_t count) {
	pulse_counter_t * counter = get_counter_from_device(dev);

	long int count_value = 0;
	if (kstrtol(buf, 10, &count_value) < 0)
		return -EINVAL;

	if (counter != NULL) {
		counter->count_total = count_value;
	}

	return count;
}

static ssize_t show_pulse_count_callback(struct device *dev, struct device_attribute * attr, char * buf){
	pulse_counter_t * counter = get_counter_from_device(dev);
	if (counter != NULL) {
		__u32 pulse_count = counter->count_total;
		return sprintf(buf, "%u\n", pulse_count);
	}

	return 0;
}

static ssize_t set_pulse_spacing_avg_callback(struct device * dev,struct device_attribute * attr, const char * buf, size_t count){
	pulse_counter_t * counter = get_counter_from_device(dev);
	long int spacing = 0;
	if (kstrtol(buf, 10, &spacing) < 0)
		return -EINVAL;

	if (counter != NULL) {
		counter->spacing_avg = spacing;
	}
	return count;
}

static ssize_t show_pulse_spacing_avg_callback(struct device * dev, struct device_attribute * attr, char * buf) {
	pulse_counter_t * counter = get_counter_from_device(dev);

	if (counter != NULL) {
		__u64 pulse_spacing = counter->spacing_avg;
		return sprintf(buf, "%llu\n", pulse_spacing);
	}

	return 0;
}

static ssize_t set_min_pulse_spacing_callback(struct device * dev,struct device_attribute * attr, const char * buf, size_t count) {
	pulse_counter_t * counter = get_counter_from_device(dev);
	long int spacing = 0;
	if (kstrtol(buf, 10, &spacing) < 0)
		return -EINVAL;

	if (counter != NULL) {
		counter->spacing_min = spacing;
	}
	return count;
}

static ssize_t show_min_pulse_spacing_callback(struct device * dev, struct device_attribute * attr, char * buf) {
	pulse_counter_t * counter = get_counter_from_device(dev);
	if (counter != NULL) {
		__u64 spacing = counter->spacing_min;
		return sprintf(buf, "%llu\n", spacing);
	}

	return 0;
}

static ssize_t set_avg_num_samples_callback(struct device* dev, struct device_attribute * attr, const char * buf, size_t count) {
	pulse_counter_t * counter = get_counter_from_device(dev);
	long int num_samples = 0;
	if (kstrtol(buf, 10, &num_samples) < 0)
		return -EINVAL;
	
	// round up to a power of 2
	long int v = num_samples;
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	if (v > MAX_PULSE_SPACING_NUM_SAMPLES) {
		v = MAX_PULSE_SPACING_NUM_SAMPLES;
	}

	printk("Num samples to average: %ld\n", v);

	if (counter != NULL) {
		counter->spacing_index = 0;
		counter->spacing_avg = 0;
		counter->count_total = 0;

		counter->spacing_avg_num_samples = v;
	}
	return count;
}

static ssize_t show_avg_num_samples_callback(struct device * dev, struct device_attribute * attr, char * buf) {
	pulse_counter_t * counter = get_counter_from_device(dev);
	if (counter != NULL) {
		__u64 output = counter->spacing_avg_num_samples;
		return sprintf(buf, "%llu\n", output);
	}

	return 0;
}

static DEVICE_ATTR(pulse_count, 00664, show_pulse_count_callback, set_pulse_count_callback);
static DEVICE_ATTR(pulse_spacing_avg, 00664, show_pulse_spacing_avg_callback, set_pulse_spacing_avg_callback);
static DEVICE_ATTR(pulse_spacing_min, 00664, show_min_pulse_spacing_callback, set_min_pulse_spacing_callback);
static DEVICE_ATTR(pulse_spacing_avg_num_samples, 00664, show_avg_num_samples_callback, set_avg_num_samples_callback);

static int __init pulseCounterModule_init(void){
	int result;

	init_pulse_counter(&tach_pulse_counter, PULSE_SPACING_NUM_SAMPLES, PULSE_SPACING_MIN_DEFAULT_USEC * 1000);
	init_pulse_counter(&vss_pulse_counter, PULSE_SPACING_NUM_SAMPLES, PULSE_SPACING_MIN_DEFAULT_USEC * 1000);
    
    // create class in /sys/class
	s_pDeviceClass = class_create(THIS_MODULE, "volvo_dash");
	BUG_ON(IS_ERR(s_pDeviceClass));
    
    // create tach pulse counting attribute
	s_pTachDeviceObject = device_create(s_pDeviceClass, NULL, 0, NULL, "tach_counter");
	BUG_ON(IS_ERR(s_pTachDeviceObject));

	result = device_create_file(s_pTachDeviceObject, &dev_attr_pulse_count);
	result = device_create_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_avg);
	result = device_create_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_min);
	result = device_create_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);
	tach_pulse_counter.dev = s_pTachDeviceObject;

	// create vss pulse counting attribute
	s_pVssDeviceObject = device_create(s_pDeviceClass, NULL, 0, NULL, "vss_counter");
	BUG_ON(IS_ERR(s_pVssDeviceObject));

	result = device_create_file(s_pVssDeviceObject, &dev_attr_pulse_count);
	result = device_create_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_avg);
	result = device_create_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_min);
	result = device_create_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);
	vss_pulse_counter.dev = s_pVssDeviceObject;

	// Request GPIOS
	if (gpio_request(TACH_PULSE_COUNTER_GPIO, TACH_PULSE_COUNTER_GPIO_DESC)) {
		printk("GPIO request faiure: %s\n", TACH_PULSE_COUNTER_GPIO_DESC);
		return -EINVAL;
	}

	if (gpio_request(VSS_PULSE_COUNTER_GPIO, VSS_PULSE_COUNTER_GPIO_DESC)) {
		printk("GPIO request faiure: %s\n", VSS_PULSE_COUNTER_GPIO_DESC);
		return -EINVAL;
	}

	//setup IRQs
	if ( (tach_pulse_counter.gpio_irq_num = gpio_to_irq(TACH_PULSE_COUNTER_GPIO)) < 0 ) {
		printk("GPIO to IRQ mapping faiure %s\n", TACH_PULSE_COUNTER_GPIO_DESC);
		return -EINVAL;
	}
	printk(KERN_NOTICE "%s Mapped int %d\n", TACH_PULSE_COUNTER_GPIO_DESC, tach_pulse_counter.gpio_irq_num);

	if (request_irq(tach_pulse_counter.gpio_irq_num,
					(irq_handler_t ) pulse_irq_handler,
					IRQF_TRIGGER_FALLING,
					TACH_PULSE_COUNTER_GPIO_DESC,
					(void *)&tach_pulse_counter)) {
		printk("Irq Request failure\n");
		return -EINVAL;
	}

	if ( (vss_pulse_counter.gpio_irq_num = gpio_to_irq(VSS_PULSE_COUNTER_GPIO)) < 0 ) {
		printk("GPIO to IRQ mapping faiure %s\n", VSS_PULSE_COUNTER_GPIO_DESC);
		return -EINVAL;
	}
	printk(KERN_NOTICE "%s Mapped int %d\n", VSS_PULSE_COUNTER_GPIO_DESC, vss_pulse_counter.gpio_irq_num);

	if (request_irq(vss_pulse_counter.gpio_irq_num,
					(irq_handler_t ) pulse_irq_handler,
					IRQF_TRIGGER_FALLING,
					VSS_PULSE_COUNTER_GPIO_DESC,
					(void* )&vss_pulse_counter)) {
		printk("Irq Request failure\n");
		return -EINVAL;
	}

	//&tach_pulse_counter.timeout_timer.data = &tach_pulse_counter;
	timer_setup(&tach_pulse_counter.timeout_timer, timeout_timer_function, 0);
	restart_timeout_timer(&tach_pulse_counter.timeout_timer, PULSE_SPACING_TIMEOUT_MSEC);

	timer_setup(&vss_pulse_counter.timeout_timer, timeout_timer_function, 0);
	restart_timeout_timer(&vss_pulse_counter.timeout_timer, PULSE_SPACING_TIMEOUT_MSEC);

	return 0;
}

static void __exit pulseCounterModule_exit(void) {
	del_timer(&tach_pulse_counter.timeout_timer);
	del_timer(&vss_pulse_counter.timeout_timer);

	device_remove_file(s_pTachDeviceObject, &dev_attr_pulse_count);
	device_remove_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_avg);
	device_remove_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_min);
	device_remove_file(s_pTachDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);

	device_remove_file(s_pVssDeviceObject, &dev_attr_pulse_count);
	device_remove_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_avg);
	device_remove_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_min);
	device_remove_file(s_pVssDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);

	device_destroy(s_pDeviceClass, 0);
	class_destroy(s_pDeviceClass);

	/*Free pulse counter interrupts and GPIO*/
	free_irq(tach_pulse_counter.gpio_irq_num, TACH_PULSE_COUNTER_GPIO_DEVICE_DESC);
	gpio_free(TACH_PULSE_COUNTER_GPIO);

	free_irq(vss_pulse_counter.gpio_irq_num, VSS_PULSE_COUNTER_GPIO_DEVICE_DESC);
	gpio_free(VSS_PULSE_COUNTER_GPIO);
}

module_init(pulseCounterModule_init);
module_exit(pulseCounterModule_exit);
