#ifndef GAUGE_TACH_H
#define GAUGE_TACH_H

#include <gauge.h>
#include <tachometer_model.h>

class TachometerGauge : public Gauge {
public:
    TachometerGauge(QObject * parent, Config * config, QList<Sensor *> sensors,
                   TachometerModel * model, QString modelName, QQmlContext * context) :
    Gauge(parent, config, sensors, model, modelName, context) {

        // get config
        Config::TachoConfig_t gaugeConfig = mConfig->getTachGaugeConfig();

        ((TachometerModel *)mModel)->setMaxRpm(gaugeConfig.maxRpm);
        ((TachometerModel *)mModel)->setRedLine(gaugeConfig.redline);

        QObject::connect(
                    sensors.at(0), &Sensor::sensorDataReady,
                    [=](QVariant data) {
            ((TachometerModel *)mModel)->setRpm(data.toInt());
        });
    }
};

#endif // GAUGE_TACH_H
