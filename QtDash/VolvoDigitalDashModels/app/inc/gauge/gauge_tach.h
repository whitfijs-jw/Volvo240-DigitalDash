#ifndef GAUGE_TACH_H
#define GAUGE_TACH_H

#include <gauge.h>
#include <tachometer_model.h>

/**
 * @brief The TachometerGauge class
 */
class TachometerGauge : public Gauge {
public:
    /**
     * @brief TachometerGauge constructor
     * @param parent: parent object
     * @param config: dash config
     * @param sensors: list of sensor inputs
     * @param model: Tachometer QML model
     * @param modelName: model name
     * @param context: QML context to register model
     */
    TachometerGauge(QObject * parent, Config * config, QList<const Sensor *> sensors,
                   TachometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {

        // get config
        GaugeConfig::TachoConfig gaugeConfig = mConfig->getTachGaugeConfig();

        // setup model
        auto tachModel = static_cast<TachometerModel*>(mModel);
        tachModel->setMaxRpm(gaugeConfig.maxRpm);
        tachModel->setRedLine(gaugeConfig.redline);

        QObject::connect(
                    sensors.at(0),
                    &Sensor::sensorDataReady,
                    [&gaugeModel = mModel](const QVariant& data) {
            static_cast<TachometerModel*>(gaugeModel)->setRpm(data.toInt());
        });
    }
};

#endif // GAUGE_TACH_H
