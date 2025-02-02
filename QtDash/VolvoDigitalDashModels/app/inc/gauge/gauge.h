#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QQmlContext>
#include <QAbstractListModel>

#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <tachometer_model.h>
#include <temp_and_fuel_gauge_model.h>

#include <config.h>
#include <sensor.h>
#include <sensor_utils.h>

/**
 * @brief The Gauge class initializes the gauge model and
 * routes data from the given sensors to the gauge model's
 * properties
 */
class Gauge : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Gauge constructor
     * @param parent: Parent QObject
     * @param config: Dash config
     * @param sensors: Sensors used by the gauge
     * @param model: Gauge model
     * @param modelName: Gauge model name (used to register model with Qml Context)
     * @param context: QML context in which the gauge will be registered
     */
    Gauge(QObject * parent, Config * config, QList<const Sensor *> sensors,
          QAbstractListModel * model, QString modelName, QQmlContext * context) :
          QObject(parent), mConfig(config), mSensors(sensors), mModel(model) {

        // register the gauge model in the QML Context
        context->setContextProperty(modelName, mModel);
    }

protected:
    Config * mConfig; //!< Dash config
    QList<const Sensor *> mSensors; //!< sensor list
    QAbstractListModel * mModel; //!< gauge model
};

#endif // GAUGE_H
