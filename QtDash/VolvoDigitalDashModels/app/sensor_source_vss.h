#ifndef SENSOR_SOURCE_VSS_H
#define SENSOR_SOURCE_VSS_H

#include <sensor_source.h>
#include <vss_input.h>

class VssSource : public SensorSource {
    Q_OBJECT
public:
    enum class VssDataChannel {
        MPH = 0,
        KPH,
    };

    VssSource(QObject * parent, Config * config, QString name = "vss") :
        SensorSource(parent, config, name),
        mVssInput(config->getVssConfig()) {
    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return 2;
    }

    QString getUnits(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            return "mph";
            break;
        case (int) VssDataChannel::KPH:
            return "kph";
            break;
        default:
            return "";
        }
    }

public slots:
    void updateAll() {
        for (int i = 0; i < getNumChannels(); i++) {
            emit dataReady(getValue(i), i);
        }
    }

    void update(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            emit dataReady(mVssInput.getMph(), channel);
            break;
        case (int) VssDataChannel::KPH:
            emit dataReady(mVssInput.getKph(), channel);
            break;
        }
    }

private:
    VssInput mVssInput;

    QVariant getValue(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            return mVssInput.getMph();
        case (int) VssDataChannel::KPH:
            return mVssInput.getKph();
        default:
            return 0;
        }
    }
};

#endif // SENSOR_SOURCE_VSS_H
