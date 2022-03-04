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
- HSD123KPW2-D10 12.3" TFT 1920x720 LCD Display w/ HDMI conversion board and custom mounts
- MCP3208 for ADC inputs
- MCP23017SS for dash warning lights and left/right blinkers
- ILQ1 for isolated I/O inputs (3 for 12 inputs) add one more to completely fill the MCP23017
- IL300 for 12V to 3.3V for isolated analog signals (rheostat and battery voltage)
- lM358D for driving IL300 12V isolated analog inputs
- LMV324 & TVS912D for 5V to 3.3V analog sensor inputs
- VK-162 USB GPS module -- needs to be manually configured with u-blox u-center to get 10Hz update rate.
- (optional and separate) LM3488 switching power supply to maintain 5.1V out from 3V-24V input
- (optional) MAX9924 VSS conditioning circuit
- (separate) optocoupler tach pulse input.

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

After boot the pi will be configured with a static ip address of 192.168.42.2.
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

## Dash Configuration

After linux is done booting and loading kernel modules, the init system will automatically start the Qt app stored in the /opt directory.  When the app is initializing it will load two configuration files from the /opt directory:

- config.ini
- config_gauges.ini

These files are parsed using QSettings ([more info here](https://doc.qt.io/qt-5/qsettings.html).

### Sensor input configuration (config.ini)

The sensor configuration file contains the configuration for the analog sensor inputs, dash light inputs, tach inputs, vss inputs, and the isolated 12V inputs

#### Sensor channels

Under the [sensor_channel] section the following inputs can be configured:

- *coolant_temp* -- Stock Volvo coolant temperature sensor/sender.
- *fuel_level* -- Stock Volvo Fuel Level sender
- *oil_pressure* -- Oil Pressure sender 
- *oil_temp* -- Oil temperature sender
- *map_sensor* -- MAP sensor sensor (GM 0-5V)
- *ambient_temp* -- Ambient Temperature sender (any NTC sensor can be used)
- *dimmer_voltage* -- Dimmer Rheostat output voltage
- *fuse8_12v* -- Volvo Fuse 8 to measure battery voltage

The default configuration is as follows:
```
[sensor_channels]
coolant_temp=0
fuel_level=1
oil_pressure=2
oil_temp=3
map_sensor=4
ambient_temp=5
dimmer_voltage=6
fuse8_12v=7
```

#### Dash Light Inputs

Under the [dash_lights] section the following inputs can be configured:

- *oil_pressure_sw* -- Stock oil pressure switch
- *od_lamp* -- Overdrive lamp
- *high_beam* -- High beam indication
- *brake_failure* -- brake failure indication
- *bulb_failure* -- bulb failure indication
- *charging* -- Alternator D+/Battery charge failure indication
- *blinker_left* -- Left blinker indication
- *blinker_right* -- Right blinker indication
- *od_lamp_auto* -- auto trans OD lamp
- *check_engine* -- Check Engine indication
- *parking_brake* -- Parking Brake engagement indication
- *conn_32_pin3* -- Half moon connector pin 3 (ABS light in newer 240s)

and one additional option:

- *active_low* -- Optoisolator outputs are open collector so this should be set to 1 unless changes to the hardware have been made

The default configuration is as follows:

```
[dash_lights]
active_low=1
oil_pressure_sw=0
od_lamp=1
high_beam=2
brake_failure=3
bulb_failure=7
charging=6
blinker_left=5
blinker_right=4
od_lamp_auto=8
check_engine=9
parking_brake=10
conn_32_pin3=11
```

#### MAP Sensor configuration

Designed for a GM style 0-5V output MAP sensor (1 bar, 2 bar, 3 bar). Under the [map_sensor] section the following parameters can be configured:

- *p_0v* -- pressure when sensor output is 0V
- *p_5v* -- pressure when sensor output is 5V
- *units* -- pressure units used for above values.  "kPa", "psi" or "bar" should be used

The default configuration is for a 3 bar GM style map sensor:

```
[map_sensor]
p_0v=3.6
p_5v=315
units="kPa"
```

#### Temperature Sensor (NTC) Configuration


