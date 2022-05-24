#ifndef SENSOR_SOURCE_CAN_H
#define SENSOR_SOURCE_CAN_H

#include <sensor_source.h>
#include <QString>
#include <QtSerialBus>


class CanSource : public SensorSource {
    Q_OBJECT
public:
    enum class CanDataChannel {
        MAP,
        RPM,
        COOLANT_TEMP,
        THROTTLE_POS,
        PULSE_WIDTH_1,
        PULSE_WIDTH_2,
        MANIFOLD_AIR_TEMP,
        IGNITION_ADV,
        AFR_TARGET,
        AFR,
        EGO_CORRECTION,
        EGT,
        PULSE_WIDTH_SEQUENTIAL,
        BATTERY_VOLTAGE,
        SENSOR_INPUT_1,
        SENSOR_INPUT_2,
        KNOCK_RETARD,
        VSS,
        TRACTION_CONTROL_RETARD,
        LAUNCH_CONTROL_TIMING,
    };

    CanSource(QObject * parent, Config * config, QString name = "can") :
        SensorSource(parent, config, name) {
    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return 20;
    }

    QString getUnits(int channel) {
        switch ((CanDataChannel)channel) {
        case CanDataChannel::MAP:
            return Config::UNITS_KPA;
        case CanDataChannel::RPM:
            return "rpm";
        case CanDataChannel::COOLANT_TEMP:
            return Config::UNITS_F;
        case CanDataChannel::THROTTLE_POS:
            return Config::UNITS_PCT;
        case CanDataChannel::PULSE_WIDTH_1:
            return "msec";
        case CanDataChannel::PULSE_WIDTH_2:
            return "msec";
        case CanDataChannel::MANIFOLD_AIR_TEMP:
            return Config::UNITS_F;
        case CanDataChannel::IGNITION_ADV:
            return "deg BTDC";
        case CanDataChannel::AFR_TARGET:
            return "AFR";
        case CanDataChannel::AFR:
            return "AFR";
        case CanDataChannel::EGO_CORRECTION:
            return Config::UNITS_PCT;
        case CanDataChannel::EGT:
            return Config::UNITS_F;
        case CanDataChannel::PULSE_WIDTH_SEQUENTIAL:
            return "msec";
        case CanDataChannel::BATTERY_VOLTAGE:
            return "V";
        case CanDataChannel::SENSOR_INPUT_1:
            return "";
        case CanDataChannel::SENSOR_INPUT_2:
            return "";
        case CanDataChannel::KNOCK_RETARD:
            return "deg";
        case CanDataChannel::VSS:
            return "1/msec";
        case CanDataChannel::TRACTION_CONTROL_RETARD:
            return "deg";
        case CanDataChannel::LAUNCH_CONTROL_TIMING:
            return "deg";
        }
    }

    void close() {
        emit stop();
    }

signals:
    void stop();

public slots:
    void updateAll() {
    }

    void update(int channel) {
    }
private:
};

#endif // SENSOR_SOURCE_CAN_H
