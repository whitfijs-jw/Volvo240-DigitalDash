#ifndef SENSOR_VOLTMETER_H
#define SENSOR_VOLTMETER_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <analog_12v_input.h>

/**
 * @brief Voltmeter Sensor class
 */
class VoltmeterSensor : public Sensor {
public:
    /**
     * @brief VoltmeterSensor constructor
     * @param parent: parent object
     * @param config: dash config
     * @param source: Adc sensor source
     * @param channel: source channel
     * @param analogConfig: 12V analog input configuration
     */
    VoltmeterSensor(QObject * parent, Config * config,
                    AdcSource * source, int channel,
                    Analog12VInput::Analog12VInputConfig analogConfig) :
        Sensor(parent, config, source, channel), m12VInput(analogConfig) {
    }

    QString getUnits() const override {
        return "V";
    }

public slots:
    /**
     * @brief Transform raw adc voltage to 12V
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            // these are true 3.3V inputs -- remove correction factor
            qreal adcVolts = data.toReal();
            adcVolts *= (3.3 / ((AdcSource *)mSource)->getVRef()); // convert to 3.3V vref
            qreal volts = m12VInput.getVoltage(adcVolts);
            emit sensorDataReady(volts);
        }
    }

private:
    Analog12VInput m12VInput; // Analog 12v input class
};

#endif // SENSOR_VOLTMETER_H
