#ifndef SENSOR_NTC_H
#define SENSOR_NTC_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <ntc.h>


class NtcSensor : public Sensor {
public:
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
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();
            //get desired temperature units from config?
            emit sensorDataReady(
                        mNtc->calculateTemp(volts,Config::TemperatureUnits::FAHRENHEIT)
                        );
        }
    }

private:
    Ntc * mNtc;
};

#endif // SENSOR_NTC_H
