#ifndef SENSOR_TACH_H
#define SENSOR_TACH_H

#include <sensor.h>
#include <sensor_source_tach.h>

/**
 * @brief Tach Sensor
 */
class TachSensor : public Sensor {
public:
    /**
     * @brief TachSensor constructor
     * @param parent
     * @param config
     * @param source
     * @param channel
     */
    TachSensor(QObject * parent, Config * config,
               TachSource * source, int channel) :
           Sensor(parent, config, source, channel) {
    }

    QString getUnits() override {
        return "rpm";
    }

public slots:
    /**
     * @brief Transform incoming data for the gauge
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            int rpm = data.toInt();
            emit sensorDataReady(rpm);
        }
    }
};

#endif // SENSOR_TACH_H
