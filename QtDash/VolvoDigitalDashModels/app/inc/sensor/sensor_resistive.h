#ifndef SENSOR_RESISTIVE_H
#define SENSOR_RESISTIVE_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <sensor_utils.h>
#include <sensor_configs.h>
/**
 * @brief The ResistiveSensor class
 */
class ResistiveSensor : public Sensor {
public:

    /**
     * @brief ResistiveSensor: resistive sensor constuctor
     * @param parent: parent object
     * @param config: dash config
     * @param source: adc source
     * @param channel: adc channel
     * @param sensorConfig: resistive sensor config
     */
    ResistiveSensor(QObject * parent, Config * config,
                    AdcSource * source, int channel,
                    SensorConfig::ResistiveSensorConfig sensorConfig) :
        Sensor(parent, config, source, channel), mSensorConfig(sensorConfig) {
        // calculate curve
        mSensorConfig.coeff = SensorUtils::polynomialRegression(
                    mSensorConfig.x, mSensorConfig.y, mSensorConfig.order);
        // use vref from adc source
        mSensorConfig.vSupply = ((AdcSource *)mSource)->getVRef();
        mCurrentLag = mSensorConfig.lagStart;
    }

    QString getUnits() const override{
        return mSensorConfig.units;
    }

public slots:
    /**
     * @brief transform adc voltage into desired output
     * @param data: adc source data
     * @param channel: adc source channel
     */
    void transform(const QVariant& data, int channel) override {
        if (channel == getChannel()) {

            qreal volts = data.toReal();

            qreal resistance = SensorUtils::getResistance(
                        volts, mSensorConfig.vSupply, mSensorConfig.rBalance);
            qreal value = SensorUtils::polynomialValue(
                        resistance, mSensorConfig.coeff);

            // check for nan
            if (value != value) {
                value = 0;
            }

            // Check that we're not shorted to ground or VDD (could be disconnected)
            qreal vRef = ((AdcSource *)mSource)->getVRef();
            if (!SensorUtils::isValid(volts, vRef)) {
                value = 0;
            }

            if (!mSteadyState && mSensorConfig.lag != 1.0) {
                mCurrentLag = mSensorConfig.lagStart * qPow(1.0 - mSensorConfig.lagDecay, mDecayCount);
                mDecayCount++;

                if (mCurrentLag < mSensorConfig.lag) {
                    mCurrentLag = mSensorConfig.lag;
                    mSteadyState = true;
                }
            }

            value = (mCurrentLag * value) + (1 - mCurrentLag) * mPreviousValue;

            mPreviousValue = value;

            emit sensorDataReady(value);
        }
    }

private:
    SensorConfig::ResistiveSensorConfig mSensorConfig; //!< resistive sensor config
    qreal mPreviousValue = 0; //!< previous value (used for filtering)
    qreal mCurrentLag = 1.0;
    bool mSteadyState = false;
    uint32_t mDecayCount = 0;
};

#endif // SENSOR_RESISTIVE_H
