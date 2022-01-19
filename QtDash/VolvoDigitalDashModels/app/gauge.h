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

class Gauge : public QObject {
    Q_OBJECT
public:
    Gauge(QObject * parent, Config * config, QList<Sensor *> sensors,
          QAbstractListModel * model, QString modelName, QQmlContext * context) :
          QObject(parent), mConfig(config), mSensors(sensors), mModel(model) {

        context->setContextProperty(modelName, mModel);
    }

    virtual bool init() = 0;

signals:

public slots:
    virtual void update(QVariant data, int channel) = 0;

protected:
    Config * mConfig;
    QList<Sensor *> mSensors;
    QAbstractListModel * mModel;
};

#endif // GAUGE_H
