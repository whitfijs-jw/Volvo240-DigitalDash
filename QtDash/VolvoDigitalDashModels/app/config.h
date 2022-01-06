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
    static constexpr char MAP_SENSOR_GROUP[] = "map_sensor";

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

    //expected map sensor keys
    static constexpr char PRESSURE_AT_0V[] = "p_0v";
    static constexpr char PRESSURE_AT_5V[] = "p_5v";
    static constexpr char PRESSURE_UNITS[] = "units";

    static constexpr char UNITS_KPA[] = "kPa";
    static constexpr char UNITS_PSI[] = "psi";
    static constexpr char UNITS_BAR[] = "bar";

    enum class PressureUnits {
        KPA = 0,
        PSI,
        BAR
    };

    typedef struct MapSensorConfig {
        qreal p0V;
        qreal p5V;
        PressureUnits units;
    } MapSensorConfig_t;

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

        //load map sensor config
        mConfig->beginGroup(MAP_SENSOR_GROUP);

        for (auto key : mConfig->childKeys()) {
            if (key == PRESSURE_AT_0V) {
                mMapSensorConfig.p0V = mConfig->value(key, -1).toReal();
            } else if (key == PRESSURE_AT_5V) {
                mMapSensorConfig.p5V = mConfig->value(key, -1).toReal();
            } else if (key == PRESSURE_UNITS) {
                // default to kPa
                auto units = mConfig->value(key, UNITS_KPA);
                if (units == UNITS_KPA) {
                    mMapSensorConfig.units = PressureUnits::KPA;
                } else if (units == UNITS_PSI) {
                    mMapSensorConfig.units = PressureUnits::PSI;
                } else if (units == UNITS_BAR) {
                    mMapSensorConfig.units = PressureUnits::BAR;
                }
            }

            std::cout << "Map Sensor " << key.toStdString() << ": " << mConfig->value(key, "N/A").toString().toStdString() << std::endl;
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

    MapSensorConfig * getMapSensorConfig() {
        return &mMapSensorConfig;
    }

signals:

public slots:

private:
    QSettings * mConfig = nullptr;
    QMap<QString, int> mSensorChannelConfig;
    QMap<QString, int> mDashLightConfig;
    MapSensorConfig mMapSensorConfig;
};

#endif // CONFIG_H
