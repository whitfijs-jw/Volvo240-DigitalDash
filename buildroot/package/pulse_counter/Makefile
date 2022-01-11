obj-m += pulse_counter.o
ccflags-y := -DDEBUG -g -std=gnu99 -Wno-declaration-after-statement

.PHONY: all clean
 
all:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules
clean:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' clean
