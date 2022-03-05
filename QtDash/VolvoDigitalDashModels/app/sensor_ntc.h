#ifndef SENSOR_NTC_H
#define SENSOR_NTC_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <ntc.h>

/**
 * @brief The NtcSensor class
 */
class NtcSensor : public Sensor {
public:
    static constexpr Config::TemperatureUnits NTC_INTERNAL_UNITS = Config::TemperatureUnits::FAHRENHEIT;

    /**
     * @brief NtcSensor constructor
     * @param parent: parent object
     * @param config: dash config
     * @param source: adc source
     * @param channel: adc channel
     * @param type: type of ntc sensor
     */
    NtcSensor(QObject * parent, Config * config,
              AdcSource * source, int channel,
              Config::TemperatureSensorType type) :
    Sensor(parent, config, source, channel) {

        // setup temp sensors
        QList<Config::TempSensorConfig_t> * tempSensorConfigs =
                mConfig->getTempSensorConfigs();

        for (Config::TempSensorConfig_t config : *tempSensorConfigs) {
            if (config.isValid()) {
                if (config.type == type) {
                    mNtc = new Ntc(config);
                }
            } else {
                qDebug() << "Temperature Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
            }
        }
    }

public slots:
    /**
     * @brief transform adc votlage into temperature
     * @param data: adc votlage from adc source
     * @param channel: adc channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();

            qreal value = mNtc->calculateTemp(volts, NTC_INTERNAL_UNITS);

            // Check that we're not shorted to ground or VDD (could be disconnected)
            if (!SensorUtils::isValid(volts, mNtc->getSensorConfig()->vSupply)) {
                value = 0;
            }

            //get desired temperature units from config?
            emit sensorDataReady(value);
        }
    }

private:
    Ntc * mNtc;
};

#endif // SENSOR_NTC_H
