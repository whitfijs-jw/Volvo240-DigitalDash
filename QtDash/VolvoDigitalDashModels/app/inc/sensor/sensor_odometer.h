#ifndef SENSOR_ODOMETER_H
#define SENSOR_ODOMETER_H

#include <sensor.h>
#include <sensor_source_vss.h>
#include <config.h>
#include <config_keys.h>
/**
 * @brief Odometer Sensor
 */
class OdometerSensor : public Sensor {
Q_OBJECT
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
                   const SensorConfig::OdometerConfig& odoConfig) :
           Sensor(parent, config, source, channel) {

        // Check if the optional input
        if (odoConfig.name != ConfigKeys::ODO_NAME_ODOMETER) {
            // this has its own config -- likely a trip counter
            mOdoConfig = odoConfig;
        } else {
            // use the odo values from the config file
            mOdoConfig = mConfig->getOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER);
            mCanReset = false;
        }
    }

    QString getUnits() const override {
        Units::DistanceUnits units = mOdoConfig.units;

        switch ((int) units) {
        case (int) Units::DistanceUnits::MILE:
            return Units::UNITS_MILE;
        case (int) Units::DistanceUnits::KILOMETER:
            return Units::UNITS_KILOMETER;
        default:
            return "";
        }
    }

signals:
    void writeOdoValue(qreal value);

public slots:
    void reset() {
        if (mCanReset) {
            mOdoConfig.value = 0;
            mLastPulseCount = 0;
            mUpdatePulseCount = 0;

           mConfig->writeOdometerConfig(mOdoConfig.name,
                                        mOdoConfig);
        }
    }

    /**
     * @brief Transform incoming data for the gauge
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(const QVariant& data, int channel) override {
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
    SensorConfig::OdometerConfig mOdoConfig;
    int mLastPulseCount = 0;
    int mUpdatePulseCount = 0;
    bool mCanReset = true;
};

#endif // SENSOR_TACH_H
