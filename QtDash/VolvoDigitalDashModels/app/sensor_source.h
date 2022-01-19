#ifndef SENSOR_SOURCE_H
#define SENSOR_SOURCE_H

#include <QObject>
#include <config.h>

class SensorSource : public QObject {
    Q_OBJECT
public:
    SensorSource(QObject * parent, Config * config, QString name) :
        QObject(parent), mConfig(config), mName(name) {

    }
    virtual bool init() = 0;
    virtual int getNumChannels() = 0;
    virtual QVariant getValue(int channel) = 0;
    virtual QString getUnits(int channel) = 0;
    virtual QString getName() {
        return mName;
    };

signals:
    void dataReady(QVariant data, int channel);

public slots:
    virtual void updateAll() = 0;
    virtual void update(int channel) = 0;

protected:
    Config * mConfig;
    QString mName;
};

#endif // SENSOR_SOURCE_H
