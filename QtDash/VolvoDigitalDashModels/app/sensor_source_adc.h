#ifndef SENSOR_SOURCE_ADC_H
#define SENSOR_SOURCE_ADC_H

#include <sensor_source.h>
#include <adc.h>

class AdcSource : public SensorSource {
    Q_OBJECT
public:
    AdcSource(QObject * parent, Config * config, QString name = "adc") :
        SensorSource(parent, config, name) {
    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return mAdc.getNumChannels();
    }

    QString getUnits(int channel) {
        (void)channel;
        return "volts";
    }

public slots:
    void updateAll() {
        for (int i = 0; i < mAdc.getNumChannels(); i++) {
            update(i);
        }

    }

    void update(int channel) {
        qreal volts = mAdc.readValue(channel);
        emit dataReady(volts, channel);
    }

private:
    Adc mAdc;
};

#endif // SENSOR_SOURCE_ADC_H
