#ifndef SENSOR_RESISTIVE_H
#define SENSOR_RESISTIVE_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <sensor_utils.h>

class ResistiveSensor : public Sensor {
public:
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
            emit sensorDataReady(value);
        }
    }

private:
    Config::ResistiveSensorConfig_t mSensorConfig;
};

#endif // SENSOR_RESISTIVE_H
