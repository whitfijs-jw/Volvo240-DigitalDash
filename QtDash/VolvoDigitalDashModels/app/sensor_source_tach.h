#ifndef SENSOR_SOURCE_TACH_H
#define SENSOR_SOURCE_TACH_H

#include <sensor_source.h>
#include <tach_input.h>

class TachSource : public SensorSource {
    Q_OBJECT
public:
    enum class TachDataChannel {
        RPM_CHANNEL = 0,
        COUNT,
    };

    TachSource(QObject * parent, Config * config, QString name = "tach") :
        SensorSource(parent, config, name),
        mTachInput(config->getTachInputConfig()) {
    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return 1;
    }

    QVariant getValue(int channel) {
        (void) channel;
        return mTachInput.getRpm();
    }

    QString getUnits(int channel) {
        (void) channel;
        return "rpm";
    }

public slots:
    void updateAll() {
        emit dataReady(getValue(0), 0);
    }

    void update(int channel) {
        switch (channel) {
        case (int) TachDataChannel::RPM_CHANNEL:
            emit dataReady(mTachInput.getRpm(), channel);
            break;
        case (int) TachDataChannel::COUNT:
            emit dataReady(mTachInput.getTachPulseCount(), channel);
        }
    }

private:
    TachInput mTachInput;
};

#endif // SENSOR_SOURCE_TACH_H
