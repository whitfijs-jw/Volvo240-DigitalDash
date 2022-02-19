#ifndef SENSOR_RESISTIVE_H
#define SENSOR_RESISTIVE_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <sensor_utils.h>

class ResistiveSensor : public Sensor {
public:
    static constexpr qreal MAX_PCT = .95;

    ResistiveSensor(QObject * parent, Config * config,
                    AdcSource * source, int channel,
                    Config::ResistiveSensorConfig_t sensorConfig) :
        Sensor(parent, config, source, channel), mSensorConfig(sensorConfig) {
        // calculate curve
        mSensorConfig.coeff = SensorUtils::polynomialRegression(
                    mSensorConfig.x, mSensorConfig.y, mSensorConfig.order);
    }

public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();

            qreal resistance = SensorUtils::getResistance(
                        volts, 5.0, mSensorConfig.rBalance);
            qreal value = SensorUtils::polynomialValue(
                        resistance, mSensorConfig.coeff);

            // check for nan
            if (value != value) {
                value = 0;
            }

            // If the sensor isn't connected we should be close to VDD
            if (volts > 5.0 * MAX_PCT) {
                value = 0;
            }

            value = (mSensorConfig.lag * value) + (1 - mSensorConfig.lag) * previousValue;

            previousValue = value;

            emit sensorDataReady(value);
        }
    }

private:
    Config::ResistiveSensorConfig_t mSensorConfig;
    qreal previousValue;
};

#endif // SENSOR_RESISTIVE_H
