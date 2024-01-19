#ifndef GAUGE_SPEEDO_H
#define GAUGE_SPEEDO_H

#include <gauge.h>
#include <speedometer_model.h>
#include <sensor_utils.h>
#include <sensor_ntc.h>
#include <sensor_map.h>
#include <sensor_resistive.h>

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

        // connect the secondary values
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            // get raw value
            qreal val = data.toReal();
            Sensor * sensor = sensors.at(1);

            // get units
            QString units = sensor->getUnits();
            QString displayUnits = speedoConfig.topUnits;

            val = SensorUtils::convert(val, displayUnits, units);

            ((SpeedometerModel *)mModel)->setTopValue(val);
        });

        if (sensors.length() > 2) {
            QObject::connect(
                        sensors.at(2), &Sensor::sensorDataReady,
                        [=](QVariant data) {
                int gear = data.toInt();

                ((SpeedometerModel *)mModel)->setCurrentGear(gear);
            });
        }
    }

private:
};

#endif // GAUGE_SPEEDO_H
