#ifndef SENSOR_VOLTMETER_H
#define SENSOR_VOLTMETER_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <analog_12v_input.h>

class VoltmeterSensor : public Sensor {
public:
    VoltmeterSensor(QObject * parent, Config * config,
                    AdcSource * source, int channel,
                    Config::Analog12VInputConfig_t analogConfig) :
        Sensor(parent, config, source, channel), m12VInput(analogConfig) {
    }

public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal adcVolts = data.toReal();
            qreal volts = m12VInput.getVoltage(adcVolts);
            emit sensorDataReady(volts);
        }
    }

private:
    Analog12VInput m12VInput;
};

#endif // SENSOR_VOLTMETER_H
