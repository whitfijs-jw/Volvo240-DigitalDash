#ifndef GAUGE_H
#define GAUGE_H

#include <QObject>
#include <QAbstractListModel>
#include <config.h>
#include <sensor_source.h>

class Gauge : public QObject {
    Q_OBJECT
public:
    Gauge(QObject * parent, Config * config,
          SensorSource * sensor, QAbstractListModel * model) :
          QObject(parent), mConfig(config), mSource(sensor), mModel(model) {

    }

    virtual bool init() = 0;

signals:

public slots:
    virtual void update(QList<QVariant> data) = 0;
    virtual void update(QVariant data, int channel) = 0;

protected:
    Config * mConfig;
    SensorSource * mSource;
    QAbstractListModel * mModel;
};

#endif // GAUGE_H
