#ifndef GAUGE_TEMP_FUEL_CLUSTER_H
#define GAUGE_TEMP_FUEL_CLUSTER_H

#include <gauge.h>
#include <temp_and_fuel_gauge_model.h>

class TempFuelClusterGauge : public Gauge {
public:
    TempFuelClusterGauge(QObject * parent, Config * config, QList<Sensor *> sensors,
                         TempAndFuelGaugeModel * model, QString modelName, QQmlContext * context) :
          Gauge(parent, config, sensors, model, modelName, context) {
        // get coolant temp config
        Config::GaugeConfig_t coolantConfig = mConfig->getGaugeConfig(Config::COOLANT_TEMP_GAUGE_GROUP);

        ((TempAndFuelGaugeModel*) mModel)->setMinTemp(coolantConfig.min);
        ((TempAndFuelGaugeModel*) mModel)->setMaxTemp(coolantConfig.max);
        ((TempAndFuelGaugeModel*) mModel)->setHighTempAlarm(coolantConfig.highAlarm);
        ((TempAndFuelGaugeModel*) mModel)->setTempUnits(coolantConfig.displayUnits);
        ((TempAndFuelGaugeModel*) mModel)->setCurrentTemp(0.0);

        // fuel gauge config
        Config::GaugeConfig_t fuelLevelConfig = mConfig->getGaugeConfig(Config::FUEL_GAUGE_GROUP);

        ((TempAndFuelGaugeModel*) mModel)->setLowFuelAlarm(fuelLevelConfig.lowAlarm);
        ((TempAndFuelGaugeModel*) mModel)->setFuelLevel(0.0);

        //hook it up
        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            ((TempAndFuelGaugeModel *)mModel)->setCurrentTemp(data.toReal());
        });

        // connect the secondary values
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            ((TempAndFuelGaugeModel *)mModel)->setFuelLevel(data.toReal());
        });

    }
};


#endif // GAUGE_TEMP_FUEL_CLUSTER_H
