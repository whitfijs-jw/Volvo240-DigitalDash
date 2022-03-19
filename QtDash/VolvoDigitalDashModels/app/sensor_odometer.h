#ifndef SENSOR_ODOMETER_H
#define SENSOR_ODOMETER_H

#include <sensor.h>
#include <sensor_source_vss.h>

/**
 * @brief Odometer Sensor
 */
class OdometerSensor : public Sensor {
public:
    /**
     * @brief OdometerSensor constructor
     * @param parent
     * @param config
     * @param source
     * @param channel
     */
    OdometerSensor(QObject * parent, Config * config,
               VssSource * source, int channel) :
           Sensor(parent, config, source, channel) {
    }

    QString getUnits() override {
        Config::DistanceUnits units = mConfig->getOdometerConfig().units;

        switch (units) {
        case (int) Config::DistanceUnits::MILE:
            return Config::UNITS_MILE;
        case (int) Config::DistanceUnits::KILOMETER:
            return Config::UNITS_KILOMETER;
        default:
            return "";
        }
    }

signals:
    void writeOdoValue(qreal value);

public slots:
    /**
     * @brief Transform incoming data for the gauge
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            int pulseCount = data.toInt();
            int diff = pulseCount - mLastPulseCount;
            qreal distance = (qreal)diff / (qreal)mConfig->getVssConfig().pulsePerUnitDistance;

            sensorDataReady(distance + mLastDistance);

            mLastPulseCount = pulseCount;
            mLastDistance += distance;

            if (mLastPulseCount % mConfig->getOdometerConfig().writeInterval) {
                writeOdoValue(mLastDistance);
            }
        }
    }

private:
    int mLastPulseCount;
    qreal mLastDistance;
};

#endif // SENSOR_TACH_H
