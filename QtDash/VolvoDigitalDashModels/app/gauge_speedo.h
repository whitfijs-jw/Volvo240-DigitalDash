#ifndef GAUGE_SPEEDO_H
#define GAUGE_SPEEDO_H

#include <gauge.h>
#include <speedometer_model.h>
#include <sensor_utils.h>
#include <sensor_ntc.h>

/**
 * @brief The SpeedometerGauge class
 */
class SpeedometerGauge: public Gauge {
public:
    /**
     * @brief SpeedometerGauge constructor
     * @param parent: parent object
     * @param config: Dash config
     * @param sensors: list of sensors
     * @param model: Speedometer QML model
     * @param modelName: model name
     * @param context: QML context to register model
     */
    SpeedometerGauge(QObject * parent, Config * config, QList<Sensor *> sensors,
                   SpeedometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {
        Config::SpeedoConfig_t speedoConfig = mConfig->getSpeedoConfig();

        // setup speedo
        ((SpeedometerModel *)mModel)->setMinValue(speedoConfig.gaugeConfig.min);
        ((SpeedometerModel *)mModel)->setMaxValue(speedoConfig.gaugeConfig.max);
        ((SpeedometerModel *)mModel)->setUnits(speedoConfig.gaugeConfig.displayUnits);
        ((SpeedometerModel *)mModel)->setCurrentValue(0.0);

        // setup secondary units display (usually ambient temperature)
        ((SpeedometerModel *)mModel)->setTopUnits(speedoConfig.topUnits);
        ((SpeedometerModel *)mModel)->setTopValue(0.0);

        // connect the speed to the model value
        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            ((SpeedometerModel *)mModel)->setCurrentValue(data.toReal());
        });

        if (std::is_base_of<T, NtcSensor>::value) {

        }

        // connect the secondary values
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            // Check top source
            qreal val = data.toReal();
            if (speedoConfig.topSource == Config::TEMP_TYPE_AMBIENT ||
                    speedoConfig.topSource == Config::TEMP_TYPE_COOLANT ||
                    speedoConfig.topSource == Config::TEMP_TYPE_OIL) {
                val = SensorUtils::convertTemperature(val,
                    Config::getTempUnits(speedoConfig.topUnits),
                    );

            }

            ((SpeedometerModel *)mModel)->setTopValue(data.toReal());
        });
    }

};

#endif // GAUGE_SPEEDO_H
