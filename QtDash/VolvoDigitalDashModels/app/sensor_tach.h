#ifndef SENSOR_TACH_H
#define SENSOR_TACH_H

#include <sensor.h>
#include <sensor_source_tach.h>

class TachSensor : public Sensor {
public:
    TachSensor(QObject * parent, Config * config,
               TachSource * source, int channel) :
           Sensor(parent, config, source, channel) {
    }

public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            int rpm = data.toInt();
            sensorDataReady(rpm);
        }
    }
};

#endif // SENSOR_TACH_H
