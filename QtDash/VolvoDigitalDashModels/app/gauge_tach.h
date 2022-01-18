#ifndef GAUGE_TACH_H
#define GAUGE_TACH_H

#include <gauge.h>
#include <tachometer_model.h>
#include <sensor_source_tach.h>

class Tachometer : public Gauge {
public:
    Tachometer(QObject * parent, Config * config,
               TachSource * source, TachometerModel * model) :
               Gauge(parent, config, source, model) {

    }

    bool init() {
        mSource->init();
        QObject::connect(mSource, SIGNAL(SensorSource::dataReady),
                         this, SLOT(Gauge::update));

        return true;
    }

public slots:
    void update(QList<QVariant> data) {
        if (data.length() > 0) {
            int rpm = data.at(0).toInt();
            updateRpm(rpm);
        }
    }

    void update(QVariant data, int channel) {
        if (channel == (int)TachSource::TachDataChannel::RPM_CHANNEL) {
            updateRpm(data.toInt());
        }
    }

private:
    void updateRpm(int rpm) {
        ((TachometerModel)mModel).setRpm(rpm);
    }
};

#endif // GAUGE_TACH_H
