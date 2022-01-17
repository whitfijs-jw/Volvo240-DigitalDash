#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <iostream>

/**
 * @brief Dash config class
 *
 * Configuration is read from a config.ini file.
 * These configurations are used to initialize
 * the sensor, tach, speedo, and dash light inputs
 * from the Dash hardware.
 */
class Config : public QObject {
Q_OBJECT
public:
    // expected groups
    static constexpr char SENSOR_CHANNEL_GROUP[] = "sensor_channels";
    static constexpr char DASH_LIGHT_GROUP[] = "dash_lights";
    static constexpr char MAP_SENSOR_GROUP[] = "map_sensor";
    static constexpr char TEMP_SENSOR_GROUP[] = "temp_sensor";
    static constexpr char TACH_INPUT_GROUP[] = "tach_input";
    static constexpr char RESISTIVE_SENSOR_GROUP[] = "resistive_sensor";

    // units for sensors
    static constexpr char UNITS_KPA[] = "kpa";
    static constexpr char UNITS_PSI[] = "psi";
    static constexpr char UNITS_BAR[] = "bar";
    static constexpr char UNITS_F[] = "F";
    static constexpr char UNITS_C[] = "C";
    static constexpr char UNITS_K[] = "K";
    static constexpr char UNITS_PCT[] = "%";

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

    static constexpr char TEMP_TYPE_COOLANT[] = "coolant";
    static constexpr char TEMP_TYPE_OIL[] = "oil";
    static constexpr char TEMP_TYPE_AMBIENT[] = "ambient";

    static constexpr qreal INVALID_TEMP = -459.67; // value if temp could not be read

    //expected keys for tach input
    static constexpr char TACH_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char TACH_MAX_RPM[] = "max_rpm";
    static constexpr char TACH_AVG_NUM_SAMPLES[] = "avg_num_samples";

    //expected keys for resistive sensors
    static constexpr char RES_SENSOR_TYPE[] = "type";
    static constexpr char RES_SENSOR_FIT_TYPE[] = "fit";
    static constexpr char RES_SENSOR_R_VALUES[] = "r";
    static constexpr char RES_SENSOR_Y_VALUES[] = "y";
    static constexpr char RES_SENSOR_UNITS[] = "units";
    static constexpr char RES_SENSOR_R_BALANCE[] = "r_balance";

    static constexpr char RES_SENSOR_TYPE_FUEL_LEVEL[] = "fuel_level";
    static constexpr char RES_SENSOR_TYPE_OIL_PRESSURE[] = "oil_pressure";

    static constexpr char RES_SENSOR_FIT_TYPE_POLYNOMIAL[] = "polynomial";
    static constexpr char RES_SENSOR_FIT_TYPE_INTERPOLATION[] = "interp";

    /**
     * @brief The PressureUnits enum
     */
    enum class PressureUnits {
        KPA = 0, //!< Kilopascals
        PSI, //!< pounds per square inch
        BAR, //!< Bar
    };

    /**
     * @brief The TemperatureUnits enum
     */
    enum class TemperatureUnits {
        KELVIN = 0, //!< Kelvin
        CELSIUS, //!< Celsius
        FAHRENHEIT, //!< Fahrenheit
    };

    /**
     * @brief TemperatureSensorType enum
     */
    enum class TemperatureSensorType {
        COOLANT = 0, //!< Coolant temp sensor
        OIL, //!< Oil temp sensor
        AMBIENT, //!< Outside/Ambient temp sensor
    };

    enum class ResistiveSensorType {
        INTERPOLATION = 0,
        POLYNOMIAL,
    };

    typedef struct ResistiveSensorConfig {
        QString type;
        ResistiveSensorType fitType;
        QList<qreal> x;
        QList<qreal> y;
        QList<qreal> coeff; // polynomial only
        int order; //polynomial only
        qreal rBalance;
        QString units;
    } ResistiveSensorConfig_t;

    /**
     * @struct MapSensorConfig
     */
    typedef struct MapSensorConfig {
        qreal p0V; //!< pressure when sensor reads 0V
        qreal p5V; //!< pressure when sensor reads 5V
        PressureUnits units; //!< units of calibration pressures

        /**
         * @brief Check if calibration is valid
         * @return true if valid
         */
        bool isValid() {
            // we're assuming absolute pressure.
            return (p0V >= 0) && (p5V != p0V);
        }
    } MapSensorConfig_t;

    /**
     * @struct TempSensorConfig
     */
    typedef struct TempSensorConfig {
        qreal rBalance; //!< balance resistor (everything should be high side)
        qreal vSupply; //!< Voltage supply (should be 5V on Dash Hardware)
        qreal t1; //!< Steinhart-Hart T1 (first calibration temperature)
        qreal t2; //!< Steinhart-Hart T2
        qreal t3; //!< Steinhart-Hart T3
        qreal r1; //!< NTC resistance at T1
        qreal r2; //!< NTC resistance at T2
        qreal r3; //!< NTC resistance at T3
        TemperatureUnits units; //!< units of calibration temperature
        TemperatureSensorType type; //!< Temp Sensor type -- coolant, oil, outside/ambient...

        /**
         * @brief Check if configuration is valid
         * @return true if valid
         */
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

    /**
     * @struct TachInputConfig
     */
    typedef struct TachInputConfig {
        int pulsesPerRot; //!< tach pulses per rotation
        int maxRpm; //!< max valid rpm
        int avgNumSamples; //!< number of samples to average over
    }TachInputConfig_t;

    /**
     * @brief Constructor
     * @param parent: Parent QObject
     * @param configPath: path to config.ini file (default is /opt/config.ini)
     */
    Config(QObject * parent, QString configPath = "/opt/config.ini") :
        QObject(parent) {
        mConfig = new QSettings(configPath, QSettings::IniFormat);
        loadConfig();
    }

    /**
     * @brief Load config from config.ini file
     * @return true on successful completion
     */
    bool loadConfig() {
        QStringList keys = mConfig->allKeys();

        // Load sensor configuration
        mConfig->beginGroup(SENSOR_CHANNEL_GROUP);

        for (auto key : mConfig->childKeys()) {
            mSensorChannelConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        printKeys("Sensor Channels ");

        mConfig->endGroup();

        // Load dash light configuration
        mConfig->beginGroup(DASH_LIGHT_GROUP);

        for (auto key : mConfig->childKeys()) {
            mDashLightConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        printKeys("Dash Light Config ");

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
        }

        printKeys("Map Sensor ");

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

            printKeys("Temp Sensor ");
        }
        mConfig->endArray();

        //tach input config
        mConfig->beginGroup(TACH_INPUT_GROUP);

        mTachConfig.pulsesPerRot = mConfig->value(TACH_PULSES_PER_ROTATION, 2).toInt(); // default to 4 cylinder
        mTachConfig.maxRpm = mConfig->value(TACH_MAX_RPM, 9000).toInt(); // default rpm is 9000 (a bit aspirational)
        mTachConfig.avgNumSamples = mConfig->value(TACH_AVG_NUM_SAMPLES, 4).toInt(); // default is to average over last 4 tach pulse spacing

        printKeys("Tach Input ");

        mConfig->endGroup();

        int resSize = mConfig->beginReadArray(RESISTIVE_SENSOR_GROUP);
        for (int i = 0; i < resSize; ++i) {
            mConfig->setArrayIndex(i);
            ResistiveSensorConfig_t rSensorConf;
            // sensor type/name
            rSensorConf.type = mConfig->value(RES_SENSOR_TYPE, "").toString();

            // sensor fit type
            QList fit = mConfig->value(RES_SENSOR_FIT_TYPE, "").toList();
            if (fit.at(0).toString() == RES_SENSOR_FIT_TYPE_POLYNOMIAL && fit.length() == 2) {
                rSensorConf.fitType = ResistiveSensorType::POLYNOMIAL;
                rSensorConf.order = fit.at(1).toInt();
            } else {
                rSensorConf.fitType = ResistiveSensorType::INTERPOLATION;
                rSensorConf.order = -1;
            }

            // balance/pullup/high side whatever resistor
            rSensorConf.rBalance = mConfig->value(RES_SENSOR_R_BALANCE, "1000.0").toReal();

            // resistance values
            QList r = mConfig->value(RES_SENSOR_R_VALUES, "").toList();
            for (QVariant val : r) {
                rSensorConf.x.push_back(val.toReal());
            }

            // y values (fuel level, pressure, etc)
            QList y = mConfig->value(RES_SENSOR_Y_VALUES, "").toList();
            for (QVariant val : y) {
                rSensorConf.y.push_back(val.toReal());
            }

            rSensorConf.units = mConfig->value(RES_SENSOR_UNITS, "").toString();

            mResistiveSensorConfig.push_back(rSensorConf);
            printKeys("Resistive Sensor: ");
        }
        mConfig->endArray();

        return keys.size() > 0;
    }

    /**
     * @brief Print all child keys for the current config subgroup
     * @param setting: Group name to output to log
     */
    void printKeys(QString setting) {
        for (auto key : mConfig->childKeys()) {
            qDebug() << setting << key << ": " << mConfig->value(key, "N/A").toStringList();
        }
    }

    /**
     * @brief Get dash light configuration
     * @return Dash light gpio configuration
     */
    QMap<QString, int> getDashLightConfig() {
        return mDashLightConfig;
    }

    /**
     * @brief Get Sensor channel configuration
     * @return Sensor channel configuration
     */
    QMap<QString, int> getSensorConfig() {
        return mSensorChannelConfig;
    }

    /**
     * @brief Get MAP sensor configuration
     * @return MAP sensor configuration
     */
    MapSensorConfig getMapSensorConfig() {
        return mMapSensorConfig;
    }

    /**
     * @brief Get temp sensor configurations
     * @return QList of temperature sensor configurations
     */
    QList<TempSensorConfig_t> * getTempSensorConfigs() {
        return &mTempSensorConfigs;
    }

    /**
     * @brief Get Tach Input configuration
     * @return tach input configuration
     */
    TachInputConfig_t getTachInputConfig() {
        return mTachConfig;
    }

    /**
     * @brief Check if sensor channel config is valid
     * @return: sensor channel config
     */
    bool isSensorConfigValid() {
        return isMapConfigValid(&mSensorChannelConfig);
    }

    /**
     * @brief Check if the dash light config is valid
     * @return true if config is valid
     */
    bool isDashLightConfigValid() {
        return isMapConfigValid(&mDashLightConfig);
    }

    QList<ResistiveSensorConfig_t> getResistiveSensorConfig() {
        return mResistiveSensorConfig;
    }

signals:

public slots:

private:
    QSettings * mConfig = nullptr;  //!< QSettings for reading config.ini file
    QMap<QString, int> mSensorChannelConfig; //!< sensor channel configuration
    QMap<QString, int> mDashLightConfig; //!< dash light gpio configuration
    MapSensorConfig_t mMapSensorConfig; //!< MAP sensor configuration
    QList<TempSensorConfig_t> mTempSensorConfigs; //!< Temp sensor configurations
    TachInputConfig_t mTachConfig; //!< Tach signal input configuration
    QList<ResistiveSensorConfig_t> mResistiveSensorConfig;

    /**
     * @brief Check that values are valid in a map
     * @param map: map to check
     * @return: true is map config values are valid
     */
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
