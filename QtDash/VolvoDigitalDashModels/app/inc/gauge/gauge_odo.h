#ifndef GAUGE_ODO_H
#define GAUGE_ODO_H

#include <gauge.h>
#include <odometer_model.h>

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
    OdometerGauge(QObject * parent, Config * config, QList<Sensor *> sensors,
                   OdometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {
        SensorConfig::OdometerConfig odoConfig = mConfig->getOdometerConfig(Config::ODO_NAME_ODOMETER);
        SensorConfig::OdometerConfig tripAConfig = mConfig->getOdometerConfig(Config::ODO_NAME_TRIPA);
        SensorConfig::OdometerConfig tripBConfig = mConfig->getOdometerConfig(Config::ODO_NAME_TRIPB);

        //setup odo
        ((OdometerModel *)mModel)->setOdometerValue(odoConfig.value);
        ((OdometerModel *)mModel)->setTripAValue(tripAConfig.value);
        ((OdometerModel *)mModel)->setTripBValue(tripBConfig.value);

        // connect the odo to the model value
        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [&](QVariant data) {
            ((OdometerModel *)mModel)->setOdometerValue(data.toReal());
        });

        // connect the tripA to the model value
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
                    [&](QVariant data) {
            ((OdometerModel *)mModel)->setTripAValue(data.toReal());
        });

        // connect the odo to the model value
        QObject::connect(
                    sensors.at(2), &Sensor::sensorDataReady,
                    [&](QVariant data) {
            ((OdometerModel *)mModel)->setTripBValue(data.toReal());
        });

    }

private:
};

#endif // GAUGE_SPEEDO_H
