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
    }

    QString getUnits() override {
        return mSensorConfig.units;
    }

public slots:
    /**
     * @brief transform adc voltage into desired output
     * @param data: adc source data
     * @param channel: adc source channel
     */
    void transform(QVariant data, int channel) override {
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

            value = (mSensorConfig.lag * value) + (1 - mSensorConfig.lag) * mPreviousValue;

            mPreviousValue = value;

            emit sensorDataReady(value);
        }
    }

private:
    SensorConfig::ResistiveSensorConfig mSensorConfig; //!< resistive sensor config
    qreal mPreviousValue = 0; //!< previous value (used for filtering)
};

#endif // SENSOR_RESISTIVE_H
