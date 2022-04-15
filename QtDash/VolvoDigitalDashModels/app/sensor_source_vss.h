#ifndef SENSOR_SOURCE_VSS_H
#define SENSOR_SOURCE_VSS_H

#include <sensor_source.h>
#include <vss_input.h>

/**
 * @brief VSS (vehicle speed sensor) source class
 */
class VssSource : public SensorSource {
    Q_OBJECT
public:
    /**
     * @brief The VssDataChannel enum
     */
    enum class VssDataChannel {
        MPH = 0, //!< miles per hour
        KPH, //!< kilometers per hour
        PULSE_COUNT, //!< total number of pulses
    };

    /**
     * @brief VssSource constructor
     * @param parent: parent qobject
     * @param config: VSS config
     * @param name: source name
     */
    VssSource(QObject * parent, Config * config, QString name = "vss") :
        SensorSource(parent, config, name),
        mVssInput(config->getVssConfig()) {
    }

    /**
     * @brief init
     * @return true on successful initialization
     */
    bool init() {
        return true;
    }

    /**
     * @brief Get number of output channel
     * @return: number of channel
     */
    int getNumChannels() {
        return 2;
    }

    /**
     * @brief Get channel units (for display?)
     * @param channel: source channel
     * @return: unit string
     */
    QString getUnits(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            return "mph";
            break;
        case (int) VssDataChannel::KPH:
            return "kph";
            break;
        case (int) VssDataChannel::PULSE_COUNT:
            // pulse
            return "";
        default:
            return "";
        }
    }

public slots:
    /**
     * @brief Update all channels and emit results
     */
    void updateAll() {
        for (int i = 0; i < getNumChannels(); i++) {
            emit dataReady(getValue(i), i);
        }
    }

    /**
     * @brief Update source
     * @param channel: channel to update
     */
    void update(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            emit dataReady(mVssInput.getMph(), channel);
            break;
        case (int) VssDataChannel::KPH:
            emit dataReady(mVssInput.getKph(), channel);
            break;
        case (int) VssDataChannel::PULSE_COUNT:
            emit dataReady(mVssInput.getPulseCount(), channel);
        }
    }

private:
    VssInput mVssInput; //!< VSS input

    /**
     * @brief getValue
     * @param channel: source channel
     * @return channel output value
     */
    QVariant getValue(int channel) {
        switch (channel) {
        case (int) VssDataChannel::MPH:
            return mVssInput.getMph();
        case (int) VssDataChannel::KPH:
            return mVssInput.getKph();
        case (int) VssDataChannel::PULSE_COUNT:
            emit dataReady(mVssInput.getPulseCount(), channel);
        default:
            return 0;
        }
    }
};

#endif // SENSOR_SOURCE_VSS_H
