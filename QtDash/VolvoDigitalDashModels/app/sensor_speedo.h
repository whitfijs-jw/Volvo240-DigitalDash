#ifndef SENSOR_SPEEDO_H
#define SENSOR_SPEEDO_H

#include <sensor.h>
#include <sensor_source.h>
#include <sensor_source_gps.h>
#include <sensor_source_vss.h>

template <class T>
class SpeedometerSensor : public Sensor {
public:
    SpeedometerSensor(QObject * parent, Config * config,
                      T * source, int channel) :
           Sensor(parent, config, source, channel) {

    }

public slots:
    void transform(QVariant data, int channel) override {
        if (std::is_base_of<T, GpsSource>::value) {
            if (channel == getChannel()) {
                qreal speed = data.toReal();
                sensorDataReady(speed);
            }
        } else if (std::is_base_of<T, VssSource>::value) {
            if (channel == getChannel()) {
                qreal speed = data.toReal();
                sensorDataReady(speed);
            }
        }
    }
};

#endif // SENSOR_SPEEDO_H
