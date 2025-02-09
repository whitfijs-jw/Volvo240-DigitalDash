#ifndef SENSOR_SPEEDO_H
#define SENSOR_SPEEDO_H

#include <sensor.h>
#include <sensor_source.h>
#include <sensor_source_gps.h>
#include <sensor_source_vss.h>

/**
 * @brief The Speedometer Sensor class
 */
template <class T>
class SpeedometerSensor : public Sensor {
public:
    /**
     * @brief Speedometer Sensor
     * @param parent: parent QObject
     * @param config: dash config
     * @param source: speed sensor source
     * @param channel: source channel
     */
    SpeedometerSensor(QObject * parent, Config * config,
                      T * source, int channel) :
           Sensor(parent, config, source, channel) {

    }

    QString getUnits() const override {
        // pass through the units
        return mSource->getUnits(getChannel());
    }

public slots:
    /**
     * @brief transform data for the gauge
     * @param data: source data
     * @param channel: source channel
     */
    void transform(const QVariant& data, int channel) override {
        if (std::is_base_of_v<T, GpsSource> && channel == getChannel()) {
            qreal speed = data.toReal();
            sensorDataReady(speed);
        } else if (std::is_base_of_v<T, VssSource> && channel == getChannel()) {
            qreal speed = data.toReal();
            sensorDataReady(speed);
        }
    }
};

#endif // SENSOR_SPEEDO_H
