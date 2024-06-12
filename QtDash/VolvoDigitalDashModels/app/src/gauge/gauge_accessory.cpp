#include <gauge_accessory.h>

AccessoryGauge::AccessoryGauge(QObject *parent, Config *config,
                               QList<Sensor *> sensors, AccessoryGaugeModel *model,
                               QString modelName, QQmlContext *context) :
    Gauge(parent, config, sensors, model, modelName, context) {

    // pull configs
    GaugeConfig::GaugeConfig gaugeConfig;
    if (modelName == AccessoryGaugeModel::BOOST_GAUGE_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::BOOST_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::COOLANT_TEMP_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::COOLANT_TEMP_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::OIL_PRESSURE_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::OIL_PRESSURE_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::OIL_TEMPERATURE_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::OIL_TEMPERATURE_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::VOLT_METER_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::VOLTMETER_GAUGE_GROUP);
    } else if (modelName == AccessoryGaugeModel::FUEL_LEVEL_MODEL_NAME) {
        gaugeConfig = config->getGaugeConfig(Config::FUEL_GAUGE_GROUP);
    }

    ((AccessoryGaugeModel *)mModel)->setMinValue(gaugeConfig.min);
    ((AccessoryGaugeModel *)mModel)->setMaxValue(gaugeConfig.max);
    ((AccessoryGaugeModel *)mModel)->setHighAlarm(gaugeConfig.highAlarm);
    ((AccessoryGaugeModel *)mModel)->setLowAlarm(gaugeConfig.lowAlarm);
    ((AccessoryGaugeModel *)mModel)->setUnits(gaugeConfig.displayUnits);

    // connect the sensor output to the model value
    QObject::connect(
        sensors.at(0), &Sensor::sensorDataReady,
        [=](QVariant data) {
            // get raw value
            qreal val = data.toReal();
            Sensor * sensor = sensors.at(0);

            // get units
            QString units = sensor->getUnits();
            QString displayUnits = gaugeConfig.displayUnits;

            val = SensorUtils::convert(val, displayUnits, units);

            ((AccessoryGaugeModel *)mModel)->setCurrentValue(val);
        });
}
