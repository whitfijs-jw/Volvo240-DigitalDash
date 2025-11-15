#ifndef GAUGE_ODO_H
#define GAUGE_ODO_H

#include <gauge.h>
#include <odometer_model.h>
#include <config.h>
#include <config_keys.h>

/**
 * @brief The SpeedometerGauge class
 */
class OdometerGauge: public Gauge {
public:
    /**
     * @brief OdometerGauge constructor
     * @param parent: parent object
     * @param config: Dash config
     * @param sensors: list of sensors
     * @param model: Odometer QML model
     * @param modelName: model name
     * @param context: QML context to register model
     */
    OdometerGauge(QObject * parent, Config * config, QList<const Sensor *> sensors,
                   OdometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {
        SensorConfig::OdometerConfig odoConfig = mConfig->getOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER);
        SensorConfig::OdometerConfig tripAConfig = mConfig->getOdometerConfig(ConfigKeys::ODO_NAME_TRIPA);
        SensorConfig::OdometerConfig tripBConfig = mConfig->getOdometerConfig(ConfigKeys::ODO_NAME_TRIPB);

        //setup odo
        auto odoModel = static_cast<OdometerModel*>(mModel);
        odoModel->setOdometerValue(odoConfig.value);
        odoModel->setTripAValue(tripAConfig.value);
        odoModel->setTripBValue(tripBConfig.value);

        // connect the odo to the model value
        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [&gaugeModel = mModel](const QVariant& data) {
                static_cast<OdometerModel*>(gaugeModel)->setOdometerValue(data.toReal());
        });

        // connect the tripA to the model value
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
            [&gaugeModel = mModel](const QVariant& data) {
                static_cast<OdometerModel*>(gaugeModel)->setTripAValue(data.toReal());
        });

        // connect the odo to the model value
        QObject::connect(
                    sensors.at(2), &Sensor::sensorDataReady,
            [&gaugeModel = mModel](const QVariant& data) {
                static_cast<OdometerModel*>(gaugeModel)->setTripBValue(data.toReal());
        });

    }
};

#endif // GAUGE_SPEEDO_H
