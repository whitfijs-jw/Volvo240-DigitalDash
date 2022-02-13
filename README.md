# DigitalDash

Volvo 240 Digital Dash Project.  Designed to use existing dash connectors (circular connectors w/ 2mm pins and various spades) to
minimize extra wiring effort and installation of superfluous sensors.

## Project components:
- Raspberry Pi 3
- 12.3" bar TFT LCD
- Qt Quick w/ EGLFS project to display renders of gauges
- Buildroot linux to cut down on footprint and boot time
- i2c/spi adc interface for reading temp, fuel, speed, etc sensors
- i2c IO expander for warning lights
- Raspberry Pi daughter board to read various sensors.
- DC/DC power supply for screen, pi and sensor supplies, if necessary
- Cheap USB GPS for speedometer and heading (leaving the original speedo behind the dash? Not planning on implementing a validated odometer)

## Current parts (mainly driven by availability):
- MCP3208 for ADC inputs
- MCP23017SS for dash warning lights and left/right blinkers
- ILQ1 for isolated I/O inputs (3 for 12 inputs) add one more to completely fill the MCP23017
- IL300 for 12V to 3.3V for isolated analog signals (rheostat and battery voltage)
- lM358D for driving IL300 12V isolated analog inputs
- LMV324 & TVS912D for 5V to 3.3V analog sensor inputs
- VK-162 USB GPS module -- needs to be manually configured with u-blox u-center to get 10Hz update rate.

![alt text](https://github.com/whitfijs-jw/Volvo240-DigitalDash/blob/develop/QtDash/project_preview.jpg?raw=true)

## Setting up buildroot

Buildroot will build the custom linux image.  The image being build is based on the raspberry-pi3 image provided from the buildroot project.  Right now there is only support for raspberry pi 3.  Things are still a bit of a mess here and depending on your flavor of Linux you might have to setup your system a little differently than others.  You can find a lot of good information here on host packages that are absolutely necessary: [Buildroot System Requirements](https://buildroot.org/downloads/manual/manual.html#requirement)


1. To get things started:

From within the main project directory:

`cd buildroot`

`make volvodash_defconfig`

This will get buildroot configured to build the linux image. 


2. Start the build:

`make` 

This will take a while, go get a coffee or if you're on a laptop run it before going to bed. You might be missing packages dependencies here and there. Check the output and use your package manager to install what's missing. This will also build the host tools for building the qt app that actually runs the dash. As one of the last steps of this process the Qt App, called VolvoDigitalDashModels (for now), is built and copied to the target /opt directory along with the config.ini file.


3. Flash Image onto

At the end of the build that completed in the last step there should be a file called "sdcard.img" in the `buildroot/output/images` directory. The easiest way to flash this image onto an SD card for use on a pi is a utility like the [Raspberry Pi Imager](https://www.raspberrypi.com/software/). In the imager utility select the "Choose OS" option, scroll all the way down and select the "Use Custom" option. Navigate to where the repository is cloned then to `buildroot/output/images`.  There should be a file named `sdcard.img`.  After selecting the image file, select your sdcard using the "Choose Storage" option. Hit write and wait. 

After writing has completed you can plug the SD card into the pi and boot. The dash should start up after boot and using the numpad on a keyboard you should be able to switch between dash screens.

## Remote Access

1. SSH (ethernet)

**TODO: More and better information here** After boot the pi will be configured with a static ip address of 192.168.42.2.
Assuming you're running a version of linux that has network-manager you can run some variation of the following after connecting the pi to your computer with an ethernet cable:

`nmcli con add con-name dash-target type ethernet ifname <your-ethernet-interface> ip4 192.168.42.1/24`

`nmcli con up id dash-target`

You can find your ethernet interface by running:

`ip addr show`

You're looking for something like `enp2s0` or `eth0` depending on your flavor of linux.

After setting everything up you can test the connection using:

`ping 192.168.42.2` 

on the host machine and then run:

`ssh root@192.168.42.2` 

and enter the default credentials

2. Serial (serial to USB adapter)

**TODO: More and better information here**

Information on how to connect a serial to USB connection can be found [here](https://elinux.org/RPi_Serial_Connection). The output baud rate is 115200. You can use screen, minicom, picocom on /dev/ttyUSB0/1/2/3/4 (wherever your serial to usb get placed).

