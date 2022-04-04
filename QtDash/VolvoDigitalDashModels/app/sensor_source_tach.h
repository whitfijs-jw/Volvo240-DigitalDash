#ifndef SENSOR_SOURCE_TACH_H
#define SENSOR_SOURCE_TACH_H

#include <sensor_source.h>
#include <tach_input.h>

/**
 * @brief The TachSource class
 */
class TachSource : public SensorSource {
    Q_OBJECT
public:
    /**
     * @brief The TachDataChannel enum
     */
    enum class TachDataChannel {
        RPM_CHANNEL = 0, //!< RPM channel
        COUNT, //!< pulse count channel
    };

    /**
     * @brief TachSource constructor
     * @param parent: parent object
     * @param config: dash config
     * @param name: source name
     */
    TachSource(QObject * parent, Config * config, QString name = "tach") :
        SensorSource(parent, config, name),
        mTachInput(config->getTachInputConfig()) {
    }

    /**
     * @brief init
     * @return true if successful
     */
    bool init() {
        return true;
    }

    /**
     * @brief get number of tach source channels
     * @return number of tach source channels
     */
    int getNumChannels() {
        return 2;
    }

    /**
     * @brief Get channel units
     * @param channel: tach source channel
     * @return channel units
     */
    QString getUnits(int channel) {
        switch (channel) {
        case (int)TachDataChannel::RPM_CHANNEL:
            return "rpm";
        case (int) TachDataChannel::COUNT:
            return "count";
        default:
            return "error";
        }
    }

public slots:
    /**
     * @brief update all channel and emit dataReady
     */
    void updateAll() {
        for (int i = 0; i < getNumChannels(); i++) {
            emit dataReady(getValue(i), i);
        }
    }

    /**
     * @brief update single channel
     * @param channel: channel to update
     */
    void update(int channel) {
        switch (channel) {
        case (int) TachDataChannel::RPM_CHANNEL:
            emit dataReady(mTachInput.getRpm(), channel);
            break;
        case (int) TachDataChannel::COUNT:
            emit dataReady(mTachInput.getPulseCount(), channel);
        }
    }

private:
    TachInput mTachInput; //!< internal tach input

    /**
     * @brief get value
     * @param channel
     * @return
     */
    QVariant getValue(int channel) {
        (void) channel;
        return mTachInput.getRpm();
    }
};

#endif // SENSOR_SOURCE_TACH_H
