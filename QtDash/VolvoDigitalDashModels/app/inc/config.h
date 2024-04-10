#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <iostream>

#include <can_frame_config.h>
#include <units.h>

#include <analog_12v_input.h>
#include <sensor_configs.h>
#include <gauge_configs.h>

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
    static constexpr char ANALOG_INPUT_12V_GROUP[] = "12v_analog";
    static constexpr char VSS_INPUT_GROUP[] = "vss_input";
    static constexpr char ODOMETER_GROUP[] = "odometer";
    static constexpr char BACKLIGHT_GROUP[] = "backlight";
    static constexpr char USER_INPUT_GROUP[] = "user_inputs";

    // expected sensor keys
    static constexpr char COOLANT_TEMP_KEY[] = "coolant_temp";
    static constexpr char FUEL_LEVEL_KEY[] = "fuel_level";
    static constexpr char OIL_PRESSURE_KEY[] = "oil_pressure";
    static constexpr char OIL_TEMP_KEY[] = "oil_temp";
    static constexpr char MAP_SENSOR_KEY[] = "map_sensor";
    static constexpr char AMBIENT_TEMP_KEY[] =  "ambient_temp";
    static constexpr char DIMMER_VOLTAGE_KEY[] =  "dimmer_voltage";
    static constexpr char FUSE8_12V_KEY[] = "fuse8_12v";
    static constexpr char REFERENCE_MEASUREMENT[] = "reference";
    static constexpr char V_SUPPLY_KEY[] = "v_supply";
    static constexpr qreal DEFAULT_V_SUPPLY = 5.0;

    // expected dash light keys
    static constexpr char ACTIVE_LOW[] = "active_low";
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

    // expected user input keys
    static constexpr char USER_INPUT1[] = "input_1";
    static constexpr char USER_INPUT2[] = "input_2";
    static constexpr char USER_INPUT3[] = "input_3";
    static constexpr char USER_INPUT4[] = "input_4";
    static constexpr char USER_INPUT1_MAP[] = "input_1_map";
    static constexpr char USER_INPUT2_MAP[] = "input_2_map";
    static constexpr char USER_INPUT3_MAP[] = "input_3_map";
    static constexpr char USER_INPUT4_MAP[] = "input_4_map";
    static constexpr Qt::Key USER_INPUT_DEFAULT_KEY = Qt::Key::Key_A;
    static constexpr char USER_INPUT_LONG_PRESS_DURATION[] = "long_press_msec";
    static constexpr int DEFAULT_LONG_PRESS_DURATION_MSEC = 3000;

    //expected map sensor keys
    static constexpr char PRESSURE_AT_0V[] = "p_0v";
    static constexpr char PRESSURE_AT_5V[] = "p_5v";
    static constexpr char PRESSURE_ATM[] = "p_atm";
    static constexpr char PRESSURE_UNITS[] = "units";

    //expected temperature sensor keys
    static constexpr char TEMP_TYPE[] = "type";
    static constexpr char TEMP_R_BALANCE[] = "r_balance";
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

    //expected keys for tach input
    static constexpr char TACH_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char TACH_MAX_RPM[] = "max_rpm";
    static constexpr char TACH_AVG_NUM_SAMPLES[] = "avg_num_samples";

    //expected keys for vss input
    static constexpr char VSS_PULSES_PER_ROTATION[] = "pulse_per_rot";
    static constexpr char VSS_TIRE_DIAMETER[] = "tire_diameter";
    static constexpr char VSS_TIRE_DIAMETER_UNITS[] = "diameter_units";
    static constexpr char VSS_PULSES_PER_DISTANCE[] = "pulse_per_unit_distance";
    static constexpr char VSS_DISTANCE_UNITS[] = "distance_units";
    static constexpr char VSS_MAX_SPEED[] = "max_speed";
    static constexpr char VSS_USE_GPS[] = "use_gps";

    //expected keys for resistive sensors
    static constexpr char RES_SENSOR_TYPE[] = "type";
    static constexpr char RES_SENSOR_FIT_TYPE[] = "fit";
    static constexpr char RES_SENSOR_R_VALUES[] = "r";
    static constexpr char RES_SENSOR_Y_VALUES[] = "y";
    static constexpr char RES_SENSOR_UNITS[] = "units";
    static constexpr char RES_SENSOR_R_BALANCE[] = "r_balance";
    static constexpr char RES_SENSOR_LAG[] = "lag";

    static constexpr char RES_SENSOR_TYPE_FUEL_LEVEL[] = "fuel_level";
    static constexpr char RES_SENSOR_TYPE_OIL_PRESSURE[] = "oil_pressure";

    static constexpr char RES_SENSOR_FIT_TYPE_POLYNOMIAL[] = "polynomial";
    static constexpr char RES_SENSOR_FIT_TYPE_INTERPOLATION[] = "interp";

    //expected keys for 12V analog signals
    static constexpr char ANALOG_INPUT_12V_NAME[] = "name";
    static constexpr char ANALOG_INPUT_12V_OPTO_R1[] = "opto_r1";
    static constexpr char ANALOG_INPUT_12V_OPTO_R2[] = "opto_r2";
    static constexpr char ANALOG_INPUT_12V_INPUT_R1[] = "input_r1";
    static constexpr char ANALOG_INPUT_12V_INPUT_R2[] = "input_r2";
    static constexpr char ANALOG_INPUT_12V_OPTO_GAIN_K3[] = "k3";
    static constexpr char ANALOG_INPUT_12V_OFFSET[] = "offset";
    static constexpr char ANALOG_INPUT_12V_X_VALUES[] = "x";
    static constexpr char ANALOG_INPUT_12V_Y_VALUES[] = "y";

    static constexpr char ANALOG_INPUT_12V_VOLTMETER[] = "voltmeter";
    static constexpr char ANALOG_INPUT_12V_RHEOSTAT[] = "rheostat";

    //expected odometer keys
    static constexpr char ODO_NAME[] = "name";
    static constexpr char ODO_UNITS[] = "units";
    static constexpr char ODO_VALUE[] = "value";
    static constexpr char ODO_WRITE_INTERVAL[] = "interval";

    static constexpr char ODO_NAME_ODOMETER[] = "odometer";
    static constexpr char ODO_NAME_TRIPA[] = "tripA";
    static constexpr char ODO_NAME_TRIPB[] = "tripB";

    static constexpr char BACKLIGHT_MAX_DUTY_CYCLE[] = "max_duty_cycle";
    static constexpr char BACKLIGHT_MIN_DUTY_CYCLE[] = "min_duty_cycle";
    static constexpr char BACKLIGHT_LIGHTS_OFF_DUTY_CYCLE[] = "lights_off_duty_cycle";
    static constexpr char BACKLIGHT_LIGHTS_ON_DUTY_CYCLE[] = "lights_on_duty_cycle";
    static constexpr char BACKLIGHT_MIN_DIMMER_RATIO[] = "min_dimmer_ratio";
    static constexpr char BACKLIGHT_MAX_DIMMER_RATIO[] = "max_dimmer_ratio";
    static constexpr char BACKLIGHT_USE_DIMMER[] = "use_dimmer";
    static constexpr char BACKLIGHT_ACTIVE_LOW[] = "active_low";

    //gauge config groups
    // boost gauge configs
    static constexpr char BOOST_GAUGE_GROUP[] = "boost";
    static constexpr qreal DEFAULT_BOOST_GAUGE_MIN_PSI = -20;
    static constexpr qreal DEFAULT_BOOST_GAUGE_MAX_PSI = 30;

    static constexpr qreal DEFAULT_BOOST_GAUGE_MIN_BAR = -1.0;
    static constexpr qreal DEFAULT_BOOST_GAUGE_MAX_BAR = 1.5;
    //coolant temp gauge configs
    static constexpr char COOLANT_TEMP_GAUGE_GROUP[] = "coolant_temp";
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MIN_F = 120.0;
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MAX_F = 250.0;

    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MIN_C = 50.0;
    static constexpr qreal DEFAULT_COOLANT_TEMP_GAUGE_MAX_C = 120.0;

    static constexpr char FUEL_GAUGE_GROUP[] = "fuel_level";
    // oil presssure gauge configs
    static constexpr char OIL_PRESSURE_GAUGE_GROUP[] = "oil_pressure";
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MIN_PSI = 0.0;
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MAX_PSI = 80.0;

    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MIN_BAR = 0.0;
    static constexpr qreal DEFAULT_OIL_PRESSURE_GAUGE_MAX_BAR = 5.0;
    //oil temperature gauge configs
    static constexpr char OIL_TEMPERATURE_GAUGE_GROUP[] = "oil_temperature";
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MIN_F = 120.0;
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MAX_F = 300.0;

    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MIN_C = 50.0;
    static constexpr qreal DEFAULT_OIL_TEMP_GAUGE_MAX_C = 150.0;
    // voltmeter
    static constexpr char VOLTMETER_GAUGE_GROUP[] = "voltmeter";
    static constexpr qreal DEFAULT_VOLTMETER_GAUGE_MIN = 10.0;
    static constexpr qreal DEFAULT_VOLTMETER_GAUGE_MAX = 16.0;
    //speedometer gauge configs
    static constexpr char SPEEDOMETER_GAUGE_GROUP[] = "speedo";
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MIN_MPH = 0.0;
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MAX_MPH = 120.0;

    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MIN_KPH = 0.0;
    static constexpr qreal DEFAULT_SPEEDO_GAUGE_MAX_KPH = 220.0;

    static constexpr char TACHOMETER_GAUGE_GROUP[] = "tacho";
    static constexpr qreal DEFAULT_TACH_GAUGE_MAX = 7000.0;
    static constexpr qreal DEFAULT_TACH_GAUGE_REDLINE = 6000.0;


    // gauge config keys
    static constexpr char MIN_VALUE[] = "min";
    static constexpr char MAX_VALUE[] = "max";
    static constexpr char HIGH_ALARM[] = "high_alarm";
    static constexpr char LOW_ALARM[] = "low_alarm";
    static constexpr char GAUGE_UNITS[] = "units";
    static constexpr char TOP_VALUE_SOURCE[] = "top_value_source";
    static constexpr char TOP_VALUE_UNITS[] = "top_value_units";
    static constexpr char MAX_RPM[] = "max_rpm";
    static constexpr char REDLINE[] = "redline";

    //can config keys
    static constexpr char CAN_CONFIG_START[] = "start";
    static constexpr char CAN_CONFIG_ENABLE[] = "use";
    static constexpr char CAN_FRAME[] = "can_frame";
    static constexpr char CAN_FRAME_ID[] = "frame_id";
    static constexpr char CAN_FRAME_OFFSET[] = "offset";
    static constexpr char CAN_FRAME_SIZE[] = "data_size";
    static constexpr char CAN_FRAME_SIGNED[] = "signed";
    static constexpr char CAN_FRAME_NAME[] = "name";
    static constexpr char CAN_FRAME_UNITS[] = "units";
    static constexpr char CAN_FRAME_MULTIPLY[] = "multiply";
    static constexpr char CAN_FRAME_DIVIDE[] = "divide";
    static constexpr char CAN_FRAME_ADD[] = "add";
    static constexpr char CAN_FRAME_GAUGE[] = "gauge";

    /**
     * @struct BacklightControlConfig
     */
    typedef struct BacklightControlConfig {
        qreal minDutyCycle;
        qreal maxDutyCycle;
        qreal lightsOffDutyCycle;
        qreal lightsOnDutyCycle;
        qreal minDimmerRatio;
        qreal maxDimmerRatio;
        bool useDimmer;
        bool activeLow;
    } BacklightControlConfig_t;

    static constexpr char DEFAULT_CONFIG_PATH[] = "/opt/config.ini"; //!< deafult config location
    static constexpr char DEFAULT_GAUGE_CONFIG_PATH[] = "/opt/config_gauges.ini"; //!< default gauge config location
    static constexpr char DEFAULT_ODO_CONFIG_PATH[] = "/opt/config_odo.ini"; //!< default odometer config location
    static constexpr char DEFAULT_CAN_CONFIG_PATH[] = "/opt/config_can.ini"; //!< default CAN frame config location

    /**
     * @brief Constructor
     * @param parent: Parent QObject
     * @param configPath: path to config.ini file (default is /opt/config.ini)
     */
    Config(QObject * parent,
           QString configPath = DEFAULT_CONFIG_PATH,
           QString gaugeConfigPath = DEFAULT_GAUGE_CONFIG_PATH,
           QString odoConfigPath = DEFAULT_ODO_CONFIG_PATH,
           QString canConfigPath = DEFAULT_CAN_CONFIG_PATH);

    bool isCanEnabled() const {
        return mEnableCan;
    }

    /**
     * @brief Load CAN frame configs
     * @return true if successful
     */
    bool loadCanFrameConfigs();

    /**
     * @brief Load odometer configs
     * @return true if successful
     */
    bool loadOdometerConfigs();

    /**
     * @brief Write odometer config
     * @param name config name
     * @param conf Odometer configuration
     * @return true if successful
     */
    bool writeOdometerConfig(QString name, SensorConfig::OdometerConfig conf);

    /**
     * @brief Load gauge configs from the .ini file
     * @return true if successful
     */
    bool loadGaugeConfigs();

    /**
     * @brief Load individual gauge config
     * @param groupName: Gauge group name
     * @return gauge config
     */
    GaugeConfig::GaugeConfig loadGaugeConfig(QString groupName);

    /**
     * @brief Load config from config.ini file
     * @return true on successful completion
     */
    bool loadConfig();

    /**
     * @brief Print all child keys for the current config subgroup
     * @param setting: Group name to output to log
     */
    void printKeys(QString setting, QSettings * config) const {
        for (auto key : config->childKeys()) {
            qDebug() << setting << key << ": " << config->value(key, "N/A").toStringList();
        }
    }

    /**
     * @brief Get dash light configuration
     * @return Dash light gpio configuration
     */
    QMap<QString, int> getDashLightConfig() const {
        return mDashLightConfig;
    }

    /**
     * @brief Get Sensor channel configuration
     * @return Sensor channel configuration
     */
    QMap<QString, int> getSensorConfig() const {
        return mSensorChannelConfig;
    }

    /**
     * @brief Get MAP sensor configuration
     * @return MAP sensor configuration
     */
    SensorConfig::MapSensorConfig getMapSensorConfig() const{
        return mMapSensorConfig;
    }

    /**
     * @brief Get temp sensor configurations
     * @return QList of temperature sensor configurations
     */
    QList<SensorConfig::TempSensorConfig> * getTempSensorConfigs(){
        return &mTempSensorConfigs;
    }

    /**
     * @brief Get Tach Input configuration
     * @return tach input configuration
     */
    SensorConfig::TachInputConfig getTachInputConfig() const {
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

    /**
     * @brief Get resistive sensor config
     * @param name: resistive sensor name
     * @return Sensor Config
     */
    SensorConfig::ResistiveSensorConfig getResistiveSensorConfig(QString name) const {
        SensorConfig::ResistiveSensorConfig empty;
        return mResistiveSensorConfig.value(name, empty);
    }

    /**
     * @brief Get 12V analog input config
     * @param name: 12 analog input name
     * @return input config
     */
    Analog12VInput::Analog12VInputConfig getAnalog12VInputConfig(QString name) const {
        Analog12VInput::Analog12VInputConfig empty;
        return mAnalog12VInputConfig.value(name, empty);
    }

    /**
     * @brief Get vehicle speed sensor config
     * @return
     */
    SensorConfig::VssInputConfig getVssConfig() const {
        return mVssInputConfig;
    }

    /**
     * @brief Get gauge config
     * @param name: gauge name
     * @return Gauge config
     */
    GaugeConfig::GaugeConfig getGaugeConfig(QString name) const {
        GaugeConfig::GaugeConfig empty;
        return mGaugeConfigs.value(name, empty);
    }

    /**
     * @brief Get speedo gauge config
     * @return Speedo gauge config
     */
    GaugeConfig::SpeedoConfig getSpeedoConfig() const {
        return mSpeedoGaugeConfig;
    }

    /**
     * @brief Get tachometer gauge config
     * @return Tachometer gauge config
     */
    GaugeConfig::TachoConfig getTachGaugeConfig() const {
        return mTachGaugeConfig;
    }

    SensorConfig::OdometerConfig getOdometerConfig(QString name) const {
        for (auto conf : mOdoConfig) {
            if (conf.name == name) {
                return conf;
            }
        }
        return {Units::DistanceUnits::MILE, 0, 0, ""};
    }

    BacklightControlConfig_t getBackLightConfig() const {
        return mBacklightConfig;
    }

    QList<CanFrameConfig> getCanFrameConfigs() const {
        return mCanFrameConfigs;
    }

    CanFrameConfig getCanFrameConfig(QString name) const {
        for (CanFrameConfig conf : mCanFrameConfigs) {
            if (conf.getName() == name) {
                return conf;
            }
        }
        // return empty config
        CanFrameConfig conf(0x00, 0x00, 0x00, false, "", "");
        return conf;
    }

    QMap<int, Qt::Key> geUserInputConfig() const {
        return mUserInputConfig;
    }

    QMap<QString, int> getUserInputPinConfig() const {
        return mUserInputPinConfig;
    }

    qreal getSensorSupplyVoltage() const {
        return mSensorSupplyVoltage;
    }

signals:

public slots:

private:
    QSettings * mConfig = nullptr;  //!< QSettings for reading config.ini file
    QMap<QString, int> mSensorChannelConfig; //!< sensor channel configuration
    qreal mSensorSupplyVoltage = DEFAULT_V_SUPPLY;
    QMap<QString, int> mDashLightConfig; //!< dash light gpio configuration
    QMap<int, Qt::Key> mUserInputConfig; //!< user input configuration
    QMap<QString, int> mUserInputPinConfig; //!< user input pin configuration
    SensorConfig::MapSensorConfig mMapSensorConfig; //!< MAP sensor configuration
    QList<SensorConfig::TempSensorConfig> mTempSensorConfigs; //!< Temp sensor configurations
    SensorConfig::TachInputConfig mTachConfig; //!< Tach signal input configuration
    QMap<QString, SensorConfig::ResistiveSensorConfig> mResistiveSensorConfig; //!< Resistive sensor configs
    QMap<QString, Analog12VInput::Analog12VInputConfig> mAnalog12VInputConfig; //!< 12V analog configs

    QSettings * mGaugeConfig = nullptr; //!< Gauge config QSettings
    QMap<QString, GaugeConfig::GaugeConfig> mGaugeConfigs; //!< map of gauge configs
    GaugeConfig::SpeedoConfig mSpeedoGaugeConfig; //!< speedo gauge config
    GaugeConfig::TachoConfig mTachGaugeConfig; //!< tacho gauge config
    SensorConfig::VssInputConfig mVssInputConfig; //!< vehicle speed sensor config

    QSettings * mOdometerConfig = nullptr; //!< odometer configration QSettings
    QList<SensorConfig::OdometerConfig> mOdoConfig; //!< odometer config

    BacklightControlConfig_t mBacklightConfig; //!< backlight configuration

    QSettings * mCanConfig; //!< can config Qsettings
    bool mEnableCan = false; //!< is Can enabled
    QList<CanFrameConfig> mCanFrameConfigs; //!< CAN frame configss

    /**
     * @brief Check that values are valid in a map
     * @param map: map to check
     * @return: true is map config values are valid
     */
    bool isMapConfigValid(QMap<QString, int> *map);

    /**
     * @brief Initialize User Input Keymap -- this is gross
     * @return User Input Key map
     */
    static QMap<QString, Qt::Key> initKeyMap();

    QMap<QString, Qt::Key> mKeyMap = initKeyMap();

};

#endif // CONFIG_H
