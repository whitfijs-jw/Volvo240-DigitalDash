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


#define PULSE_COUNTER_GPIO                  6
#define PULSE_COUNTER_GPIO_DESC             "Pulse Interrupt Pin"
#define PULSE_COUNTER_GPIO_DEVICE_DESC      "Pulse counter"

#define PULSE_COUNTER_LED_GPIO              18
#define PULSE_COUNTER_LED_GPIO_DESC         "Pulse counter led indicator pin"

#define PULSE_SPACING_NUM_SAMPLES           4
#define MAX_PULSE_SPACING_NUM_SAMPLES		32

#define PULSE_SPACING_TIMEOUT_MSEC			200
#define PULSE_SPACING_MIN_DEFAULT_USEC 		2500		


static __u16 pulse_counter_gpio_irq_num 	= 0;
static __u32 pulse_count_total				= 0;
static __u64 pulse_spacing[MAX_PULSE_SPACING_NUM_SAMPLES];
static __u64 pulse_spacing_index            = 0;
static __u64 pulse_spacing_avg              = 0;
static __u64 pulse_spacing_avg_num_samples  = PULSE_SPACING_NUM_SAMPLES;
static __u64 pulse_spacing_min				= PULSE_SPACING_MIN_DEFAULT_USEC * 1000;

struct timer_list timeout_timer;

void restart_timeout_timer(void) {
	mod_timer (&timeout_timer, jiffies + ( msecs_to_jiffies(PULSE_SPACING_TIMEOUT_MSEC)));	
}

void timeout_timer_function(struct timer_list *timer) {
	// reset pulse spacing
	pulse_spacing_avg = 0;
	pulse_spacing_index = 0;
	for (int i = 0; i < PULSE_SPACING_NUM_SAMPLES; i++) {
		pulse_spacing[i] = 0;
	}

	// restart the timer
	restart_timeout_timer();
}

static irqreturn_t pulse_irq_handler(__u32 irq, void * dev_id, struct pt_regs * regs){
	static ktime_t last;
	ktime_t now;
	static int lastInterrupt = 0;
    static __u8 on = 0;
	
	// temporary -- flip pin
    on = !on;
    gpio_set_value(PULSE_COUNTER_LED_GPIO, on);

	// set the pulse spacing avg
    if (lastInterrupt == 0) {
		last = ktime_get();
        lastInterrupt = jiffies;
    } else {
		now = ktime_get();
        __u64 now_nsec = ktime_to_ns(now);
		__u64 last_nsec = ktime_to_ns(last);
		__u64 spacing = (now_nsec - last_nsec);

		// if we've got someting erroneous skip it
		if (spacing < pulse_spacing_min) {
			spacing = pulse_spacing_min;
		}
		 
		pulse_spacing[pulse_spacing_index++] = spacing;
		pulse_spacing_index = pulse_spacing_index & (pulse_spacing_avg_num_samples - 1);		

		if (pulse_count_total > pulse_spacing_avg_num_samples) {
			__u64 avg = 0;
			for (int i = 0; i < pulse_spacing_avg_num_samples; i++) {
				avg += pulse_spacing[i];
			}
			pulse_spacing_avg = div_u64(avg, pulse_spacing_avg_num_samples);
		}
		

		last = now;
    }

	// increment pulse count total
    pulse_count_total++;

	// reset the timeout timer
	restart_timeout_timer();

    return IRQ_HANDLED;
}

static ssize_t set_pulse_count_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count){
	long int count_value = 0;
	if (kstrtol(buf, 10, &count_value) < 0)
		return -EINVAL;

	pulse_count_total = count_value;
	return count;
}

static ssize_t show_pulse_count_callback(struct device *d, struct device_attribute * attr, char * buf){
	__u32 pulse_count = pulse_count_total;
	return sprintf(buf, "%u\n", pulse_count);
}

static ssize_t set_pulse_spacing_avg_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count){
	long int spacing = 0;
	if (kstrtol(buf, 10, &spacing) < 0)
		return -EINVAL;

	pulse_spacing_avg = spacing;
	return count;
}

static ssize_t show_pulse_spacing_avg_callback(struct device *d, struct device_attribute * attr, char * buf){
	__u64 pulse_spacing = pulse_spacing_avg;
	return sprintf(buf, "%llu\n", pulse_spacing);
}

static ssize_t set_min_pulse_spacing_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count) {
	long int spacing = 0;
	if (kstrtol(buf, 10, &spacing) < 0)
		return -EINVAL;

	pulse_spacing_min = spacing;
	return count;
}

static ssize_t show_min_pulse_spacing_callback(struct device *d, struct device_attribute * attr, char * buf) {
	__u64 spacing = pulse_spacing_min;
	return sprintf(buf, "%llu\n", spacing);
}

static ssize_t set_avg_num_samples_callback(struct device* dev,struct device_attribute* attr, const char * buf, size_t count) {
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

	pulse_spacing_index = 0;
	pulse_spacing_avg = 0;
	pulse_count_total = 0;

	pulse_spacing_avg_num_samples = v;
	return count;
}

static ssize_t show_avg_num_samples_callback(struct device *d, struct device_attribute * attr, char * buf) {
	__u64 output = pulse_spacing_avg_num_samples;
	return sprintf(buf, "%llu\n", output);
}

static DEVICE_ATTR(pulse_count, 00664, show_pulse_count_callback, set_pulse_count_callback);
static DEVICE_ATTR(pulse_spacing_avg, 00664, show_pulse_spacing_avg_callback, set_pulse_spacing_avg_callback);
static DEVICE_ATTR(pulse_spacing_min, 00664, show_min_pulse_spacing_callback, set_min_pulse_spacing_callback);
static DEVICE_ATTR(pulse_spacing_avg_num_samples, 00664, show_avg_num_samples_callback, set_avg_num_samples_callback);

static struct class *s_pDeviceClass;
static struct device *s_pDeviceObject;

static int __init pulseCounterModule_init(void){
	int result;
	
	if (gpio_request(PULSE_COUNTER_LED_GPIO, "LED Pin")) {
	  printk("GPIO request faiure: %s\n", "LED Pin");
	  return -EINVAL;
	}
	gpio_direction_output(PULSE_COUNTER_LED_GPIO, 1);
    
    // create class in /sys/class
	s_pDeviceClass = class_create(THIS_MODULE, "volvo_dash");
	BUG_ON(IS_ERR(s_pDeviceClass));
    
    // create pulse_count attribute
	s_pDeviceObject = device_create(s_pDeviceClass, NULL, 0, NULL, "pulse_counter");
	BUG_ON(IS_ERR(s_pDeviceObject));

	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_count);
	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_spacing_avg);
	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_spacing_min);
	result = device_create_file(s_pDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);

   if (gpio_request(PULSE_COUNTER_GPIO, PULSE_COUNTER_GPIO_DESC)) {
      printk("GPIO request faiure: %s\n", PULSE_COUNTER_GPIO_DESC);
      return -EINVAL;
   }
   
 
   if ( (pulse_counter_gpio_irq_num = gpio_to_irq(PULSE_COUNTER_GPIO)) < 0 ) {
      printk("GPIO to IRQ mapping faiure %s\n", PULSE_COUNTER_GPIO_DESC);
      return -EINVAL;
   }
 
   printk(KERN_NOTICE "Mapped int %d\n", pulse_counter_gpio_irq_num);
 
   if (request_irq(pulse_counter_gpio_irq_num,
                   (irq_handler_t ) pulse_irq_handler,
                   IRQF_TRIGGER_FALLING,
                   PULSE_COUNTER_GPIO_DESC,
                   PULSE_COUNTER_GPIO_DEVICE_DESC)) {
      printk("Irq Request failure\n");
      return -EINVAL;
   }


	timer_setup(&timeout_timer, timeout_timer_function, 0);
	restart_timeout_timer();

	return 0;
}

static void __exit pulseCounterModule_exit(void) {
	del_timer(&timeout_timer);

	device_remove_file(s_pDeviceObject, &dev_attr_pulse_count);
	device_remove_file(s_pDeviceObject, &dev_attr_pulse_spacing_avg);
	device_remove_file(s_pDeviceObject, &dev_attr_pulse_spacing_min);
	device_remove_file(s_pDeviceObject, &dev_attr_pulse_spacing_avg_num_samples);
	device_destroy(s_pDeviceClass, 0);
	class_destroy(s_pDeviceClass);

	/*Free LED GPIO*/
	gpio_free(PULSE_COUNTER_LED_GPIO);

	/*Free pulse counter interrupt and GPIO*/
	free_irq(pulse_counter_gpio_irq_num, PULSE_COUNTER_GPIO_DEVICE_DESC);
	gpio_free(PULSE_COUNTER_GPIO);
}

module_init(pulseCounterModule_init);
module_exit(pulseCounterModule_exit);
