PWD := $(shell pwd)
obj-m += pulse_counter.o

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL) SUBDIRS=$(PWD) clean
