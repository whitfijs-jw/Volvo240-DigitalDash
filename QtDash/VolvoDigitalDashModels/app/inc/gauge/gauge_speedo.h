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
        mSpeedoConfig = mConfig->getSpeedoConfig();

        // setup speedo
        ((SpeedometerModel *)mModel)->setMinValue(mSpeedoConfig.gaugeConfig.min);
        ((SpeedometerModel *)mModel)->setMaxValue(mSpeedoConfig.gaugeConfig.max);
        ((SpeedometerModel *)mModel)->setUnits(mSpeedoConfig.gaugeConfig.displayUnits);
        ((SpeedometerModel *)mModel)->setCurrentValue(0.0);

        // setup secondary units display (usually ambient temperature)
        ((SpeedometerModel *)mModel)->setTopUnits(mSpeedoConfig.topUnits);
        ((SpeedometerModel *)mModel)->setTopValue(0.0);

        // connect the speed to the model value
        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [&](QVariant data) {
            if (mSensors.length() > 0) {
                QString units = mSensors.at(0)->getUnits();
                QString displayUnits = mSpeedoConfig.gaugeConfig.displayUnits;
                QString modelUnits = ((SpeedometerModel *)mModel)->units();

                qreal val = SensorUtils::convert(data.toReal(), modelUnits, units);
                ((SpeedometerModel *)mModel)->setCurrentValue(val);
            }
        });

        // connect the secondary values
        QObject::connect(
                    sensors.at(1), &Sensor::sensorDataReady,
                    [&](QVariant data) {
            // get raw value
            qreal val = data.toReal();
            if (mSensors.length() > 1) {
                Sensor * sensor = mSensors.at(1);

                // get units
                QString units = sensor->getUnits();
                QString displayUnits = mSpeedoConfig.topUnits;

                val = SensorUtils::convert(val, displayUnits, units);

                ((SpeedometerModel *)mModel)->setTopValue(val);
            }
        });
    }

private:
    GaugeConfig::SpeedoConfig mSpeedoConfig;
};

#endif // GAUGE_SPEEDO_H
