#ifndef SENSOR_SOURCE_ADC_H
#define SENSOR_SOURCE_ADC_H

#include <sensor_source.h>
#include <adc.h>

class AdcSource : public SensorSource {
public:
    AdcSource(QObject * parent, Config * config, QString name = "adc") :
        SensorSource(parent, config, name) {
    }

    bool init() {

    }

    int getNumChannels() {
        return mAdc.getNumChannels();
    }

    QVariant getValue(int channel) {
        return mAdc.readValue(channel);
    }

    QString getUnits(int channel) {
        return "volts";
    }

public slots:
    void update() {
        QList<QVariant> vals;
        for (int i = 0; i < mAdc.getNumChannels(); i++) {
            vals.push_back(mAdc.readValue(i));
        }
        emit dataReady(vals);
    }

    void update(int channel) {
        emit dataReady(mAdc.readValue(channel), channel);
    }

private:
    Adc mAdc;
};

#endif // SENSOR_SOURCE_ADC_H
