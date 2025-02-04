#ifndef GAUGE_TEMP_FUEL_CLUSTER_H
#define GAUGE_TEMP_FUEL_CLUSTER_H

#include <gauge.h>
#include <temp_and_fuel_gauge_model.h>
#include <config.h>
#include <config_keys.h>

/**
 * @brief The TempFuelClusterGauge class
 */
class TempFuelClusterGauge : public Gauge {
public:
    /**
     * @brief TempFuelClusterGauge constructor
     * @param parent: parent object
     * @param config: dash config
     * @param sensors: list of sensor inputs
     * @param model: temp/fuel QML model
     * @param modelName: model name
     * @param context: QML context to register model
     */
    TempFuelClusterGauge(QObject * parent, Config * config, QList<const Sensor *> sensors,
                         TempAndFuelGaugeModel * model, QString modelName, QQmlContext * context) :
          Gauge(parent, config, sensors, model, modelName, context) {
        // get coolant temp config
        mCoolantConfig = mConfig->getGaugeConfig(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);

        // setup model
        auto tempFuelModel = static_cast<TempAndFuelGaugeModel*>(mModel);
        tempFuelModel->setMinTemp(mCoolantConfig.min);
        tempFuelModel->setMaxTemp(mCoolantConfig.max);
        tempFuelModel->setHighTempAlarm(mCoolantConfig.highAlarm);
        tempFuelModel->setTempUnits(mCoolantConfig.displayUnits);
        tempFuelModel->setCurrentTemp(0.0);

        // fuel gauge config
        GaugeConfig::GaugeConfig fuelLevelConfig = mConfig->getGaugeConfig(ConfigKeys::FUEL_GAUGE_GROUP);

        tempFuelModel->setLowFuelAlarm(fuelLevelConfig.lowAlarm);
        tempFuelModel->setFuelLevel(0.0);

        //hook it up
        QObject::connect(
                    mSensors.at(0),
                    &Sensor::sensorDataReady,
                    [&gaugeSensors = mSensors, &coolantConfig = mCoolantConfig, &gaugeModel = mModel](const QVariant& data) {
            // get raw value
            qreal val = data.toReal();

            if (!gaugeSensors.isEmpty()) {
                auto sensor = gaugeSensors.at(0);

                // get units
                QString units = sensor->getUnits();
                QString displayUnits = coolantConfig.displayUnits;

                val = SensorUtils::convert(val, displayUnits, units);

                static_cast<TempAndFuelGaugeModel*>(gaugeModel)->setCurrentTemp(val);
            }
        });

        // connect the secondary values
        QObject::connect(
                    mSensors.at(1),
                    &Sensor::sensorDataReady,
                    [&gaugeModel = mModel](const QVariant& data) {
            static_cast<TempAndFuelGaugeModel*>(gaugeModel)->setFuelLevel(data.toReal());
        });

    }

private:
    GaugeConfig::GaugeConfig mCoolantConfig; //!< coolant temp config
};


#endif // GAUGE_TEMP_FUEL_CLUSTER_H
