# DigitalDash

Volvo 240 Digital Dash Project.

Project components:
- Raspberry Pi 3
- 12.3" bar TFT LCD
- Qt Quick w/ EGLFS project to display renders of gauges
- Buildroot linux to cut down on footprint and boot time
- i2c/spi adc interface for reading temp, fuel, speed, etc sensors
- Multiplexed IO for warning lights (to be determined)
- Raspberry Pi daughter board to read various sensors.
- DC/DC power supply for screen, pi and sensor supplies, if necessary
