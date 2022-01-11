#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <iostream>

class Config : public QObject {
Q_OBJECT
public:
    // expected groups
    static constexpr char SENSOR_CHANNEL_GROUP[] = "sensor_channels";
    static constexpr char DASH_LIGHT_GROUP[] = "dash_lights";
    static constexpr char MAP_SENSOR_GROUP[] = "map_sensor";
    static constexpr char TEMP_SENSOR_GROUP[] = "temp_sensor";
    static constexpr char TACH_INPUT_GROUP[] = "tach_input";

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

    static constexpr char UNITS_KPA[] = "kpa";
    static constexpr char UNITS_PSI[] = "psi";
    static constexpr char UNITS_BAR[] = "bar";

    //expected temperature sensor keys
    static constexpr char TEMP_TYPE[] = "type";
    static constexpr char TEMP_R_BALANCE[] = "r_balance";
    static constexpr char TEMP_V_SUPPLY[] = "v_supply";
    static constexpr char T1_TEMP[] = "t1_temp";
    static constexpr char T1_RES[] = "t1_R";
    static constexpr char T2_TEMP[] = "t2_temp";
    static constexpr char T2_RES[] = "t2_R";
    static constexpr char T3_TEMP[] = "t3_temp";
    static constexpr char T3_RES[] = "t3_R";
    static constexpr char TEMP_UNITS[] = "units";

    static constexpr char UNITS_F[] = "F";
    static constexpr char UNITS_C[] = "C";
    static constexpr char UNITS_K[] = "K";

    static constexpr char TEMP_TYPE_COOLANT[] = "coolant";
    static constexpr char TEMP_TYPE_OIL[] = "oil";
    static constexpr char TEMP_TYPE_AMBIENT[] = "ambient";

    static constexpr qreal INVALID_TEMP = -459.67; // value if temp could not be read

    //expected keys for tach input
    static constexpr char TACH_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char TACH_MAX_RPM[] = "max_rpm";


    enum class PressureUnits {
        KPA = 0,
        PSI,
        BAR
    };

    enum class TemperatureUnits {
        KELVIN = 0,
        CELSIUS,
        FAHRENHEIT,
    };

    enum class TemperatureSensorType {
        COOLANT = 0,
        OIL,
        AMBIENT,
    };

    typedef struct MapSensorConfig {
        qreal p0V;
        qreal p5V;
        PressureUnits units;

        bool isValid() {
            // we're assuming absolute pressure.
            return (p0V >= 0) && (p5V != p0V);
        }
    } MapSensorConfig_t;

    typedef struct TempSensorConfig {
        qreal rBalance;
        qreal vSupply;
        qreal t1;
        qreal t2;
        qreal t3;
        qreal r1;
        qreal r2;
        qreal r3;
        TemperatureUnits units;
        TemperatureSensorType type;

        bool isValid() {
            return (t1 >= INVALID_TEMP) &&
                    (t2 >= INVALID_TEMP) &&
                    (t3 >= INVALID_TEMP) &&
                    (r1 > 0) &&
                    (r2 > 0) &&
                    (r3 > 0) &&
                    (vSupply > 0) &&
                    (rBalance > 0);

        }
    } TempSensorConfig_t;


    typedef struct TachInputConfig {
        int pulsesPerRot;
        int maxRpm;
    }TachInputConfig_t;

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
            qDebug() << key << ": " << mConfig->value(key, -1).toInt();
            mSensorChannelConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        mConfig->endGroup();

        // Load dash light configuration
        mConfig->beginGroup(DASH_LIGHT_GROUP);

        for (auto key : mConfig->childKeys()) {
            qDebug() << key << ": " << mConfig->value(key, -1).toInt();
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
                QString units = mConfig->value(key, UNITS_KPA).toString();
                if (units.toLower() == UNITS_KPA) {
                    mMapSensorConfig.units = PressureUnits::KPA;
                } else if (units.toLower() == UNITS_PSI) {
                    mMapSensorConfig.units = PressureUnits::PSI;
                } else if (units.toLower() == UNITS_BAR) {
                    mMapSensorConfig.units = PressureUnits::BAR;
                } else {
                    qDebug() << "Unrecognized pressure units, assuming kPa.  Fix config.ini file if not correct";
                    mMapSensorConfig.units = PressureUnits::KPA;
                }
            }

            qDebug() << "Map Sensor " << key << ": " << mConfig->value(key, "N/A").toString();
        }

        mConfig->endGroup();

        // Temperature sensor config
        int size = mConfig->beginReadArray(TEMP_SENSOR_GROUP);
        for (int i = 0; i < size; ++i) {
            TempSensorConfig_t conf;
            mConfig->setArrayIndex(i);

            conf.rBalance = mConfig->value(TEMP_R_BALANCE, 1000).toReal();
            conf.vSupply = mConfig->value(TEMP_V_SUPPLY, 5.0).toReal();
            conf.t1 = mConfig->value(T1_TEMP, -1).toReal();
            conf.t2 = mConfig->value(T2_TEMP, -1).toReal();
            conf.t3 = mConfig->value(T3_TEMP, -1).toReal();
            conf.r1 = mConfig->value(T1_RES, -1).toReal();
            conf.r2 = mConfig->value(T2_RES, -1).toReal();
            conf.r3 = mConfig->value(T3_RES, -1).toReal();

            auto units = mConfig->value(TEMP_UNITS, UNITS_K);
            if (units == UNITS_F) {
                conf.units = TemperatureUnits::FAHRENHEIT;
            } else if (units == UNITS_C) {
                conf.units = TemperatureUnits::CELSIUS;
            } else if (units == UNITS_K) {
                conf.units = TemperatureUnits::KELVIN;
            } else {
                qDebug() << "Unrecognized temperature units, assuming Kelvin (K).  Fix config.ini file if not correct";
                conf.units = TemperatureUnits::KELVIN;
            }

            auto type = mConfig->value(TEMP_TYPE, TEMP_TYPE_COOLANT);
            if (type == TEMP_TYPE_COOLANT) {
                conf.type = TemperatureSensorType::COOLANT;
            } else if (type == TEMP_TYPE_OIL) {
                conf.type = TemperatureSensorType::OIL;
            } else if (type == TEMP_TYPE_AMBIENT) {
                conf.type = TemperatureSensorType::AMBIENT;
            } else {
                qDebug() << "Unrecognized temperature sensor type, assuming coolant.  Fix config.ini file if not correct";
                conf.type = TemperatureSensorType::COOLANT;
            }

            mTempSensorConfigs.append(conf);

            for (auto key : mConfig->childKeys()) {
                qDebug() << "Temp Sensor " << key << ": " << mConfig->value(key, "N/A").toString();
            }
        }
        mConfig->endArray();

        //tach input config
        mConfig->beginGroup(TACH_INPUT_GROUP);

        mTachConfig.pulsesPerRot = mConfig->value(TACH_PULSES_PER_ROTATION, 2).toInt(); // default to 4 cylinder
        mTachConfig.maxRpm = mConfig->value(TACH_MAX_RPM, 9000).toInt(); // default rpm is 9000 (a bit aspirational)

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

    QList<TempSensorConfig_t> * getTempSensorConfigs() {
        return &mTempSensorConfigs;
    }

    TachInputConfig_t getTachInputConfig() {
        return mTachConfig;
    }

    bool isSensorConfigValid() {
        return isMapConfigValid(&mSensorChannelConfig);
    }

    bool isDashLightConfigValid() {
        return isMapConfigValid(&mDashLightConfig);
    }



signals:

public slots:

private:
    QSettings * mConfig = nullptr;
    QMap<QString, int> mSensorChannelConfig;
    QMap<QString, int> mDashLightConfig;
    MapSensorConfig_t mMapSensorConfig;
    QList<TempSensorConfig_t> mTempSensorConfigs;
    TachInputConfig_t mTachConfig;


    bool isMapConfigValid(QMap<QString, int> *map) {
        QSet<int> values;
        for (int val : map->values()) {
            // check that the value is valid
            if (val < 0) {
                return false;
            }

            // check that the value doesn't already exist
            if (values.contains(val)) {
                return false;
            }

            values.insert(val);
        }
        return true;
    }
};

#endif // CONFIG_H
