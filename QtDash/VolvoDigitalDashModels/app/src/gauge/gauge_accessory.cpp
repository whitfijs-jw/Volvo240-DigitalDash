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

    ((AccessoryGaugeModel *)mModel)->setMinValue(mGaugeConfig.min);
    ((AccessoryGaugeModel *)mModel)->setMaxValue(mGaugeConfig.max);
    ((AccessoryGaugeModel *)mModel)->setHighAlarm(mGaugeConfig.highAlarm);
    ((AccessoryGaugeModel *)mModel)->setLowAlarm(mGaugeConfig.lowAlarm);
    ((AccessoryGaugeModel *)mModel)->setUnits(mGaugeConfig.displayUnits);

    // connect the sensor output to the model value
    QObject::connect(
        sensors.at(0), &Sensor::sensorDataReady,
        [&](QVariant data) {
            // get raw value
            qreal val = data.toReal();
            if (mSensors.length() > 0) {
                auto sensor = mSensors.at(0);

                if (sensor == nullptr) {
                    qDebug() << "No Sensor";
                    return;
                }

                // get units
                QString units = sensor->getUnits();
                QString displayUnits = mGaugeConfig.displayUnits;

                if (mGaugeConfig.altDisplayUnits.use && mGaugeConfig.altDisplayUnits.checkCutoff(val)) {
                    static_cast<AccessoryGaugeModel*>(mModel)->setUnits(mGaugeConfig.altDisplayUnits.displayUnits);
                    displayUnits = mGaugeConfig.altDisplayUnits.displayUnits;
                } else {
                    static_cast<AccessoryGaugeModel*>(mModel)->setUnits(mGaugeConfig.displayUnits);
                }

                val = SensorUtils::convert(val, displayUnits, units);

                ((AccessoryGaugeModel *)mModel)->setCurrentValue(val);
            }
        });
}
