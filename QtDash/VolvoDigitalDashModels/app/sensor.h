#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <sensor_source.h>
#include <config.h>

class Sensor : public QObject {
    Q_OBJECT
public:
    Sensor(QObject * parent, Config * config,
           SensorSource * source, int channel) :
    QObject(parent), mConfig(config), mSource(source),
    mChannel(channel) {
//        QObject::connect(
//                    mSource, &SensorSource::dataReady,
//                    [=](QVariant data, int channel){
//            this->transform(data, channel);
//        });

        QObject::connect(
                    mSource, &SensorSource::dataReady,
                    this, &Sensor::transform);
    }

    virtual void init() {

    }

    int getChannel() {
        return mChannel;
    }

signals:
    void sensorDataReady(QVariant data);
public slots:
    virtual void transform(QVariant data, int channel) {
        (void)
        emit sensorDataReady(data);
    }

protected:
    Config * mConfig;
    SensorSource * mSource;
    int mChannel;
};

#endif // SENSOR_H
