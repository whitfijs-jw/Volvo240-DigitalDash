#ifndef GAUGE_COOLANT_TEMPERATURE_H
#define GAUGE_COOLANT_TEMPERATURE_H

#include <gauge.h>
#include <sensor_source_adc.h>
#include <accessory_gauge_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <ntc.h>

template <class T>
class CoolantTempGauge : public Gauge {
public:
    CoolantTempGauge(QObject * parent, Config * config,
                     AdcSource * source, T * model) :
        Gauge(parent, config, source, model) {

        static_assert(std::is_base_of<QAbstractListModel, T>::value,
                "T must inherit from QAbstractListModel");

        mChannel = mConfig->getSensorConfig().value(Config::COOLANT_TEMP_KEY);

        // setup coolant temp sensors
        QList<Config::TempSensorConfig_t> * tempSensorConfigs = mConfig->getTempSensorConfigs();
        for (Config::TempSensorConfig_t config : *tempSensorConfigs) {
            if (config.isValid()) {
                if (config.type == Config::TemperatureSensorType::COOLANT) {
                    mNtc = new Ntc(config);
                }
            } else {
                qDebug() << "Temperature Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
            }
        }
    }

    bool init() {
        mSource->init();
    }

public slots:
    void update(QList<QVariant> data) {

    }

    void update(QVariant data, int channel) {
        if (channel == mChannel) {
            if (std::is_base_of<AccessoryGaugeModel, T>::value) {
                ((AccessoryGaugeModel *)model)->setCurrentValue(data.toReal());
            } else if (std::is_base_of<TempAndFuelGaugeModel, T>::value) {
                ((TempAndFuelGaugeModel *)model)->setCurrentTemp(data.toReal());
            }
        }
    }

private:
    int mChannel;
    Ntc * mNtc;

    qreal getCoolantTemp() {
        qreal coolantTempVolts = mAnalogInputs.readValue(mChannel);
        return mNtc->calculateTemp(coolantTempVolts, Config::TemperatureUnits::FAHRENHEIT);
    }
};

#endif // GAUGE_COOLANT_TEMPERATURE_H
