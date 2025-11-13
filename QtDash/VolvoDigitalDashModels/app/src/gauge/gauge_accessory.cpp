#include <gauge_accessory.h>
#include <config_keys.h>

AccessoryGauge::AccessoryGauge(QObject *parent, Config *config,
                               QList<const Sensor *> sensors, AccessoryGaugeModel *model,
                               QString modelName, QQmlContext *context) :
    Gauge(parent, config, sensors, model, modelName, context) {

    // pull configs
    if (modelName == AccessoryGaugeModel::BOOST_GAUGE_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::BOOST_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::COOLANT_TEMP_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::OIL_PRESSURE_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::OIL_PRESSURE_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::OIL_TEMPERATURE_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::OIL_TEMPERATURE_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::VOLT_METER_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::VOLTMETER_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::FUEL_LEVEL_MODEL_NAME) {
        mGaugeConfig = config->getGaugeConfig(ConfigKeys::FUEL_GAUGE_GROUP);
    }

    model->setMinValue(mGaugeConfig.min);
    model->setMaxValue(mGaugeConfig.max);
    model->setHighAlarm(mGaugeConfig.highAlarm);
    model->setLowAlarm(mGaugeConfig.lowAlarm);
    model->setUnits(mGaugeConfig.displayUnits);

    // connect the sensor output to the model value
    QObject::connect(
        sensors.at(0), &Sensor::sensorDataReady,
        [&gaugeSensors = mSensors, &gaugeConfig = mGaugeConfig, &gaugeModel = mModel](const QVariant& data) {
            // get raw value
            qreal val = data.toReal();
            if (!gaugeSensors.isEmpty()) {
                auto sensor = gaugeSensors.at(0);

                if (sensor == nullptr) {
                    qDebug() << "No Sensor";
                    return;
                }

                // get units
                QString units = sensor->getUnits();
                QString displayUnits = gaugeConfig.displayUnits;

                if (gaugeConfig.altDisplayUnits.use && gaugeConfig.altDisplayUnits.checkCutoff(val)) {
                    static_cast<AccessoryGaugeModel*>(gaugeModel)->setUnits(gaugeConfig.altDisplayUnits.displayUnits);
                    displayUnits = gaugeConfig.altDisplayUnits.displayUnits;
                } else {
                    static_cast<AccessoryGaugeModel*>(gaugeModel)->setUnits(gaugeConfig.displayUnits);
                }

                val = SensorUtils::convert(val, displayUnits, units);

                static_cast<AccessoryGaugeModel*>(gaugeModel)->setCurrentValue(val);
            }
        });
}
