#ifndef GAUGE_SPEEDO_H
#define GAUGE_SPEEDO_H

#include <gauge.h>
#include <speedometer_model.h>
#include <sensor_source_gps.h>

class Speedometer : public Gauge {
public:
    Speedometer(QObject * parent, Config * config, SensorSource * source,
                SpeedometerModel * model) : Gauge(parent, config, source, model) {
    }

    bool init() {
        mSource->init();


        // check config?

        QObject::connect(mSource, SIGNAL(SensorSource::dataReady),
                         this, SLOT(Gauge::update));

        QObject::connect(mSource, SIGNAL(SensorSource::dataReady(QVariant, int)),
                         this, SLOT(Gauge::update(QVariant, int)));
    }

public slots:
    void update(QList<QVariant> data) {

    }

    void update(QVariant data, int channel) {
        if (mSource->getName() == "gps") {
            switch (channel) {
                case (int)GpsSource::GpsDataChannel::HEADING_CARDINAL:
                break;
            case (int)GpsSource::GpsDataChannel::HEADING_DEGREES:
                break;
            case (int)GpsSource::GpsDataChannel::SPEED_METERS_PER_SEC:
                break;
            case (int)GpsSource::GpsDataChannel::SPEED_MILES_PER_HOUR:
                ((SpeedometerModel *)mModel)->setCurrentValue(data.toReal());
                break;
            case (int)GpsSource::GpsDataChannel::SPEED_KILOMETERS_PER_HOUR:
                break;
            }
        }
    }

};

#endif // GAUGE_SPEEDO_H
