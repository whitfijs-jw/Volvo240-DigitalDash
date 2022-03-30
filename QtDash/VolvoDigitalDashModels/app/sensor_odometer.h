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
                   VssSource * source, int channel,
                   Config::OdometerConfig_t * odoConfig = nullptr) :
           Sensor(parent, config, source, channel) {

        // Check if the optional input
        if (odoConfig != nullptr) {
            // this has its own config -- likely a trip counter
            mOdoConfig = *odoConfig;
        } else {
            // use the odo values from the config file
            mOdoConfig = mConfig->getOdometerConfig();
        }
    }

    QString getUnits() override {
        Config::DistanceUnits units = mOdoConfig.units;

        switch ((int) units) {
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
            // Calculate distance traveled
            int pulseCount = data.toInt();
            int diff = pulseCount - mLastPulseCount;

            // calculate distance
            qreal distance = (qreal)diff / (qreal)mConfig->getVssConfig().pulsePerUnitDistance;

            // convert to odo units
            qreal distanceConverted = SensorUtils::convertDistance(distance,
                                                                   mOdoConfig.units,
                                                                   mConfig->getVssConfig().distanceUnits);
            // emit
            emit sensorDataReady(distanceConverted + mOdoConfig.value);

            // update internal values and emit write signal
            mLastPulseCount = pulseCount;
            mOdoConfig.value += distance;

            if (mLastPulseCount - mUpdatePulseCount > mOdoConfig.writeInterval) {
                emit writeOdoValue(mOdoConfig.value);
                mUpdatePulseCount = mLastPulseCount;
            }
        }
    }

private:
    Config::OdometerConfig_t mOdoConfig;
    int mLastPulseCount = 0;
    int mUpdatePulseCount = 0;
};

#endif // SENSOR_TACH_H
