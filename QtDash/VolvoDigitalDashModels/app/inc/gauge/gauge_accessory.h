#ifndef GAUGE_ACCESSORY_H
#define GAUGE_ACCESSORY_H

#include <gauge.h>
#include <accessory_gauge_model.h>
#include <sensor_utils.h>

/**
 * @brief The AccessoryGauge class
 */
class AccessoryGauge : public Gauge {
public:
    /**
     * @brief AccessoryGauge constructor
     * @param parent: parent object
     * @param config: dash config
     * @param sensors: list of sensors
     * @param model: accessory gauge QML model
     * @param modelName: model name
     * @param context: QML context to register model
     */
    AccessoryGauge(QObject * parent, Config * config,
                   QList<Sensor *> sensors, AccessoryGaugeModel * model,
                   QString modelName, QQmlContext * context);

public slots:

private:
    GaugeConfig::GaugeConfig mGaugeConfig;
};

#endif // GAUGE_ACCESSORY_H
