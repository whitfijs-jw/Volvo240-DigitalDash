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

Current parts (mainly driven by availability):
- MCP3208 for ADC inputs
- MCP23017SS for dash warning lights and left/right blinkers
- ILQ1 for isolated I/O inputs (3 for 12 inputs) add one more to completely fill the MCP23017
- IL300 for 12V to 3.3V for isolated analog signals (rheostat and battery voltage)
- lM358D for driving IL300 12V isolated analog inputs
- LM324 for 5V to 3.3V analog sensor inputs
