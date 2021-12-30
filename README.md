# DigitalDash

Volvo 240 Digital Dash Project.  Designed to use existing dash connectors (circular connectors w/ 2mm pins and various spades) to
minimize extra wiring effort and installation of superfluous sensors.

Project components:
- Raspberry Pi 3
- 12.3" bar TFT LCD
- Qt Quick w/ EGLFS project to display renders of gauges
- Buildroot linux to cut down on footprint and boot time
- i2c/spi adc interface for reading temp, fuel, speed, etc sensors
- i2c IO expander for warning lights
- Raspberry Pi daughter board to read various sensors.
- DC/DC power supply for screen, pi and sensor supplies, if necessary
- Cheap USB GPS for speedometer and heading (leaving the original speedo behind the dash? Not planning on implementing a validated odometer)

Current parts (mainly driven by availability):
- MCP3208 for ADC inputs
- MCP23017SS for dash warning lights and left/right blinkers
- ILQ1 for isolated I/O inputs (3 for 12 inputs) add one more to completely fill the MCP23017
- IL300 for 12V to 3.3V for isolated analog signals (rheostat and battery voltage)
- lM358D for driving IL300 12V isolated analog inputs
- LM324 for 5V to 3.3V analog sensor inputs
- VK-162 USB GPS module -- needs to be manually configured with u-blox u-center to get 10Hz update rate.

![alt text](https://github.com/whitfijs-jw/Volvo240-DigitalDash/blob/develop/QtDash/project_preview.jpg?raw=true)
