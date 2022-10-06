#ifndef SENSOR_SOURCE_CAN_H
#define SENSOR_SOURCE_CAN_H

#include <QtSerialBus>
#include <sensor_source.h>
#include <QString>
#include <can_frame_config.h>


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

    QMap<QString, int> mDefaultChannelMap {
        {"map", (int) CanDataChannel::MAP},
        {"rpm", (int) CanDataChannel::RPM},
        {"clt", (int) CanDataChannel::COOLANT_TEMP},
        {"tps", (int) CanDataChannel::THROTTLE_POS},
        {"pw1", (int) CanDataChannel::PULSE_WIDTH_1},
        {"pw2", (int) CanDataChannel::PULSE_WIDTH_2},
        {"mat", (int) CanDataChannel::MANIFOLD_AIR_TEMP},
        {"adv_deg", (int) CanDataChannel::IGNITION_ADV},
        {"afrtgt1", (int) CanDataChannel::AFR_TARGET},
        {"afr1", (int) CanDataChannel::AFR},
        {"egocor1", (int) CanDataChannel::EGO_CORRECTION},
        {"egt1", (int) CanDataChannel::EGT},
        {"pwseq1", (int) CanDataChannel::PULSE_WIDTH_SEQUENTIAL},
        {"batt", (int) CanDataChannel::BATTERY_VOLTAGE},
        {"sensors1", (int) CanDataChannel::SENSOR_INPUT_1},
        {"sensors2", (int) CanDataChannel::SENSOR_INPUT_2},
        {"knk_rtd", (int) CanDataChannel::KNOCK_RETARD},
        {"vss1", (int) CanDataChannel::VSS},
        {"tc_retard", (int) CanDataChannel::TRACTION_CONTROL_RETARD},
        {"launch_timing", (int) CanDataChannel::LAUNCH_CONTROL_TIMING},
    };

    CanSource(QObject * parent, Config * config, QString name = "can0") :
        SensorSource(parent, config, name) {
        mOtherChannels = getNumChannels();
        qDebug() << "Can Source init";
        for (CanFrameConfig conf : mConfig->getCanFrameConfigs()) {
            qDebug() << "Frame config found: " << conf.getName();
            if (mDefaultChannelMap.contains(conf.getName())) {
                // name exists within default mapping
                mCanMap.insert(mDefaultChannelMap.value(conf.getName()), conf.getName());
            } else {
                mCanMap.insert(mOtherChannels++, conf.getName());
            }
        }


        if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
            qDebug() << "found socketcan";
            QString errorString;

            const QList<QCanBusDeviceInfo> devices =
                    QCanBus::instance()->availableDevices(QStringLiteral("socketcan"), &errorString);
            if (!errorString.isEmpty()) qDebug() << errorString;
            foreach (QCanBusDeviceInfo info, devices) {
                qDebug() << info.name();
            }

            mDevice = QCanBus::instance()->createDevice(
                QStringLiteral("socketcan"), mName, &errorString);
            if (!mDevice) {
                qDebug() << "Error String: " << errorString;
            } else {
                qDebug() << "Attempting connection";
                mDevice->connectDevice();

                QObject::connect(mDevice, &QCanBusDevice::framesReceived,
                                 this, &SensorSource::updateAll);
            }

        }
    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return 20;
    }

    bool addCanFrameConfig(CanFrameConfig * frameConfig, CanDataChannel channel) {
        mCanMap.insert((int)channel, frameConfig->getName());
        return true;
    }

    QString getUnits(int channel) {
        if (mCanMap.contains(channel)) {
            // return value from frame config
            return mConfig->getCanFrameConfig(mCanMap.value(channel)).getUnits();
        } else {
            // default values
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
            default:
                return "";
            }
        }
    }

    QMap<int, QString> * getChannelConfigs() {
        return &mCanMap;
    }

    CanFrameConfig getChannelConfig(int channel) {
        if (mCanMap.contains(channel)) {
            // return value from frame config
            return mConfig->getCanFrameConfig(mCanMap.value(channel));
        }
    }


    void close() {
        emit stop();
    }

signals:
    void stop();

public slots:
    void updateAll() {
        while(mDevice->framesAvailable()) {
            QCanBusFrame frame = mDevice->readFrame();
//            /*** test frame start ***/
//            qDebug() << "Frame type: " << frame.frameType();
//            qDebug() << "*** Begin Frame ID: " << frame.frameId();
//            qDebug() << "Frame Data: " << frame.payload();
//            qDebug() << "*** End Frame ID: " << frame.frameId();

//            CanFrameConfig * tpsConfig = new CanFrameConfig(1512, 6, 2, false, "tps", "%");
//            tpsConfig->addOperation(CanFrameConfig::OperationType::DIVIDE, 10.0);

//            if (frame.frameId() == tpsConfig->getFrameId()) {
//                qreal tps = tpsConfig->getValue(frame.payload());
//                qDebug() << "TPS: " << tps;
//            }
//            /*** test frame end ***/

            for (int channel : mCanMap.keys()) {
                CanFrameConfig frameConfig = mConfig->getCanFrameConfig(mCanMap.value(channel));
                if (frameConfig.getFrameId() == frame.frameId()) {
                    qreal value = frameConfig.getValue(frame.payload());
                    emit dataReady(value, (int) channel);
                }
            }
        }
    }

    void update(int channel) override {
        (void)channel;
    }


private:
    QMap<int, QString> mCanMap;
    QCanBusDevice * mDevice;
    int mOtherChannels;
};

#endif // SENSOR_SOURCE_CAN_H
