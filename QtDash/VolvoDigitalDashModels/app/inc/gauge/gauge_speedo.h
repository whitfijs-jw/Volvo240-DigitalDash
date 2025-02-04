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
    SpeedometerGauge(QObject * parent, Config * config, QList<const Sensor *> sensors,
                   SpeedometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {
        mSpeedoConfig = mConfig->getSpeedoConfig();

        // setup speedo
        auto speedoModel = static_cast<SpeedometerModel*>(mModel);
        speedoModel->setMinValue(mSpeedoConfig.gaugeConfig.min);
        speedoModel->setMaxValue(mSpeedoConfig.gaugeConfig.max);
        speedoModel->setUnits(mSpeedoConfig.gaugeConfig.displayUnits);
        speedoModel->setCurrentValue(0.0);

        // setup secondary units display (usually ambient temperature)
        speedoModel->setTopUnits(mSpeedoConfig.topUnits);
        speedoModel->setTopValue(0.0);

        // connect the speed to the model value
        QObject::connect(
                    mSensors.at(0), &Sensor::sensorDataReady,
                    [&gaugeSensors = mSensors, &speedoConfig = mSpeedoConfig, &gaugeModel = mModel](const QVariant& data) {
                if (!gaugeSensors.isEmpty()) {
                QString units = gaugeSensors.at(0)->getUnits();
                QString modelUnits = static_cast<SpeedometerModel*>(gaugeModel)->units();

                qreal val = SensorUtils::convert(data.toReal(), modelUnits, units);
                static_cast<SpeedometerModel*>(gaugeModel)->setCurrentValue(val);
            }
        });

        // connect the secondary values
        if (mSensors.length() > 1) {
            QObject::connect(
                        mSensors.at(1),
                        &Sensor::sensorDataReady,
                        [&gaugeSensors = mSensors, &speedoConfig = mSpeedoConfig, &gaugeModel = mModel](const QVariant& data) {
                // get raw value
                qreal val = data.toReal();
                if (gaugeSensors.length() > 1) {
                    auto sensor = gaugeSensors.at(1);

                    // get units
                    QString units = sensor->getUnits();
                    QString displayUnits = speedoConfig.topUnits;

                    val = SensorUtils::convert(val, displayUnits, units);

                    static_cast<SpeedometerModel*>(gaugeModel)->setTopValue(val);
                }
            });
        }
    }

private:
    GaugeConfig::SpeedoConfig mSpeedoConfig;
};

#endif // GAUGE_SPEEDO_H
