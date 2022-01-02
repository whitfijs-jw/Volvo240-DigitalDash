#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <iostream>

class Config : public QObject {
Q_OBJECT
public:
    // expected groups
    static constexpr char SENSOR_CHANNEL_GROUP[] = "sensor_channels";
    static constexpr char DASH_LIGHT_GROUP[] = "dash_lights";

    // expected sensor keys
    static constexpr char COOLANT_TEMP_KEY[] = "coolant_temp";
    static constexpr char FUEL_LEVEL_KEY[] = "fuel_level";
    static constexpr char OIL_PRESSURE_KEY[] = "oil_pressure";
    static constexpr char OIL_TEMP_KEY[] = "oil_temp";
    static constexpr char MAP_SENSOR_KEY[] = "map_sensor";
    static constexpr char AMBIENT_TEMP_KEY[] =  "ambient_temp";
    static constexpr char DIMMER_VOLTAGE_KEY[] =  "dimmer_voltage";
    static constexpr char FUSE8_12V_KEY[] = "fuse8_12v";

    // expected dash light keys
    static constexpr char OIL_PRESSURE_SW_KEY[] = "oil_pressure_sw";
    static constexpr char OD_LAMP_KEY[] = "od_lamp";
    static constexpr char HIGH_BEAM_KEY[] = "high_beam";
    static constexpr char BRAKE_FAILURE_KEY[] = "brake_failure";
    static constexpr char BULB_FAILURE_KEY[] = "bulb_failure";
    static constexpr char CHARGING_LIGHT_KEY[] = "charging";
    static constexpr char BLINKER_LEFT_KEY[] = "blinker_left";
    static constexpr char BLINKER_RIGHT_KEY[] = "blinker_right";
    static constexpr char OD_LAMP_AUTO[] = "od_lamp_auto";
    static constexpr char CHECK_ENGINE_KEY[] = "check_engine";
    static constexpr char PARKING_BRAKE_KEY[] = "parking_brake";
    static constexpr char CONN_32_PIN3[] = "conn_32_pin3";


    Config(QObject * parent, QString configPath = "/opt/config.ini") :
        QObject(parent) {
        mConfig = new QSettings(configPath, QSettings::IniFormat);
        loadConfig();
    }

    bool loadConfig() {
        QStringList keys = mConfig->allKeys();

        // Load sensor configuration
        mConfig->beginGroup(SENSOR_CHANNEL_GROUP);

        for (auto key : mConfig->childKeys()) {
            std::cout << key.toStdString() << ": " << mConfig->value(key, -1).toInt() << std::endl;
            mSensorChannelConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        mConfig->endGroup();

        // Load dash light configuration
        mConfig->beginGroup(DASH_LIGHT_GROUP);

        for (auto key : mConfig->childKeys()) {
            std::cout << key.toStdString() << ": " << mConfig->value(key, -1).toInt() << std::endl;
            mDashLightConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        mConfig->endGroup();

        return keys.size() > 0;
    }

    QMap<QString, int> * getDashLightConfig() {
        return &mDashLightConfig;
    }

    QMap<QString, int> * getSensorConfig() {
        return &mSensorChannelConfig;
    }

signals:

public slots:

private:
    QSettings * mConfig = nullptr;
    QMap<QString, int> mSensorChannelConfig;
    QMap<QString, int> mDashLightConfig;
};

#endif // CONFIG_H
