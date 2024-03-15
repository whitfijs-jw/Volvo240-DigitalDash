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
           QString canConfigPath = DEFAULT_CAN_CONFIG_PATH) :
        QObject(parent) {
        mConfig = new QSettings(configPath, QSettings::IniFormat);
        loadConfig();

        mGaugeConfig = new QSettings(gaugeConfigPath, QSettings::IniFormat);
        loadGaugeConfigs();

        mOdometerConfig = new QSettings(odoConfigPath, QSettings::IniFormat);
        loadOdometerConfigs();

        mCanConfig = new QSettings(canConfigPath, QSettings::IniFormat);
        loadCanFrameConfigs();
    }

    bool isCanEnabled() {
        return mEnableCan;
    }

    bool loadCanFrameConfigs() {
        // parse enable/disable
        mCanConfig->beginGroup(CAN_CONFIG_START);
        printKeys("can", mCanConfig);
        mEnableCan = mCanConfig->value(CAN_CONFIG_ENABLE, false).toBool();
        mCanConfig->endGroup();

        // dump keys to log
        mCanConfig->beginGroup(CAN_FRAME);
        printKeys("can", mCanConfig);
        mCanConfig->endGroup();

        // parse can frame data configs
        int size = mCanConfig->beginReadArray(CAN_FRAME);
        for (int i = 0; i < size; ++i) {
            mCanConfig->setArrayIndex(i);

            uint32_t frameId = mCanConfig->value(CAN_FRAME_ID, 0).toUInt();
            uint8_t offset = mCanConfig->value(CAN_FRAME_OFFSET, 0).toInt();
            uint8_t size = mCanConfig->value(CAN_FRAME_SIZE, 0).toInt();
            bool sign = mCanConfig->value(CAN_FRAME_SIGNED, false).toBool();
            QString units = mCanConfig->value(CAN_FRAME_UNITS, "").toString();
            QString name = mCanConfig->value(CAN_FRAME_NAME, "").toString();
            QString gauge = mCanConfig->value(CAN_FRAME_GAUGE, "none").toString();

            // create new can frame config
            CanFrameConfig config(frameId, offset, size, sign, units, name, gauge);

            qreal multiply = mCanConfig->value(CAN_FRAME_MULTIPLY, 1).toReal();
            qreal divide = mCanConfig->value(CAN_FRAME_DIVIDE, 1).toReal();
            qreal add = mCanConfig->value(CAN_FRAME_ADD, 0).toReal();

            if (multiply != 1) {
                config.addOperation(CanFrameConfig::OperationType::MULTIPLY, multiply);
            }

            if (divide != 1) {
                config.addOperation(CanFrameConfig::OperationType::DIVIDE, divide);
            }

            if (add != 0) {
                config.addOperation(CanFrameConfig::OperationType::ADD, add);
            }

            mCanFrameConfigs.append(config);
            printKeys("can: ", mCanConfig);
        }
        mCanConfig->endArray();

        return true;
    }

    bool loadOdometerConfigs() {

        mOdometerConfig->beginGroup("start");
        printKeys("odo", mOdometerConfig);
        mOdometerConfig->endGroup();

        mOdometerConfig->beginGroup(ODOMETER_GROUP);
        printKeys("odo", mOdometerConfig);
        mOdometerConfig->endGroup();

        int size = mOdometerConfig->beginReadArray(ODOMETER_GROUP);
        for (int i = 0; i < size; ++i) {
            SensorConfig::OdometerConfig conf;
            mOdometerConfig->setArrayIndex(i);

            QString odoUnits = mOdometerConfig->value(ODO_UNITS, Units::UNITS_MILE).toString();
            conf.units = Units::getDistanceUnits(odoUnits);
            conf.value = mOdometerConfig->value(ODO_VALUE, 0.0).toReal();
            conf.writeInterval = mOdometerConfig->value(ODO_WRITE_INTERVAL, 2000).toInt();
            conf.name = mOdometerConfig->value(ODO_NAME, "").toString();

            mOdoConfig.push_back(conf);
        }

        mOdometerConfig->endArray();
        return true;
    }

    bool writeOdometerConfig(QString name, SensorConfig::OdometerConfig conf) {
        //write to disk
        mOdometerConfig->beginWriteArray(ODOMETER_GROUP);
        for (int i = 0; i < mOdoConfig.size(); i++) {
            mOdometerConfig->setArrayIndex(i);

            if (mOdometerConfig->value(ODO_NAME, "").toString() == name) {
                mOdometerConfig->setValue(ODO_VALUE, conf.value);
                mOdometerConfig->sync();
            }
        }
        mOdometerConfig->endArray();
        return true;
    }

    /**
     * @brief Load gauge configs from the .ini file
     * @return true if successful
     */
    bool loadGaugeConfigs() {
        // accessory gauges
        // boost gauge
        GaugeConfig::GaugeConfig boost = loadGaugeConfig(BOOST_GAUGE_GROUP);
        if (boost.displayUnits.compare(Units::UNITS_PSI, Qt::CaseInsensitive) == 0) {
            boost.min = DEFAULT_BOOST_GAUGE_MIN_PSI;
            boost.max = DEFAULT_BOOST_GAUGE_MAX_PSI;
        } else {
            boost.min = DEFAULT_BOOST_GAUGE_MIN_BAR;
            boost.max = DEFAULT_BOOST_GAUGE_MAX_BAR;
        }
        mGaugeConfigs.insert(BOOST_GAUGE_GROUP, boost);

        // coolant temp
        GaugeConfig::GaugeConfig coolantTemp = loadGaugeConfig(COOLANT_TEMP_GAUGE_GROUP);
        if (coolantTemp.displayUnits.compare(Units::UNITS_F, Qt::CaseInsensitive) == 0) {
            coolantTemp.min = DEFAULT_COOLANT_TEMP_GAUGE_MIN_F;
            coolantTemp.max = DEFAULT_COOLANT_TEMP_GAUGE_MAX_F;
        } else {
            coolantTemp.min = DEFAULT_COOLANT_TEMP_GAUGE_MIN_C;
            coolantTemp.max = DEFAULT_COOLANT_TEMP_GAUGE_MAX_C;
        }
        mGaugeConfigs.insert(COOLANT_TEMP_GAUGE_GROUP, coolantTemp);

        // fuel level
        GaugeConfig::GaugeConfig fuelLevel = loadGaugeConfig(FUEL_GAUGE_GROUP);
        fuelLevel.min = 0.0;
        fuelLevel.max = 100.0;
        mGaugeConfigs.insert(FUEL_GAUGE_GROUP, fuelLevel);

        // oil pressure
        GaugeConfig::GaugeConfig oilPressure = loadGaugeConfig(OIL_PRESSURE_GAUGE_GROUP);
        if (oilPressure.displayUnits.compare(Units::UNITS_PSI, Qt::CaseInsensitive) == 0) {
            oilPressure.min = DEFAULT_OIL_PRESSURE_GAUGE_MIN_PSI;
            oilPressure.max = DEFAULT_OIL_PRESSURE_GAUGE_MAX_PSI;
        } else {
            oilPressure.min = DEFAULT_OIL_PRESSURE_GAUGE_MIN_BAR;
            oilPressure.max = DEFAULT_OIL_PRESSURE_GAUGE_MAX_BAR;
        }
        mGaugeConfigs.insert(OIL_PRESSURE_GAUGE_GROUP, oilPressure);

        // oil temperature
        GaugeConfig::GaugeConfig oilTemp = loadGaugeConfig(OIL_TEMPERATURE_GAUGE_GROUP);
        if (oilTemp.displayUnits.compare(Units::UNITS_F, Qt::CaseInsensitive) == 0) {
            oilTemp.min = DEFAULT_OIL_TEMP_GAUGE_MIN_F;
            oilTemp.max = DEFAULT_OIL_TEMP_GAUGE_MAX_F;
        } else {
            oilTemp.min = DEFAULT_OIL_TEMP_GAUGE_MIN_C;
            oilTemp.max = DEFAULT_OIL_TEMP_GAUGE_MAX_C;
        }
        mGaugeConfigs.insert(OIL_TEMPERATURE_GAUGE_GROUP, oilTemp);

        //voltmeter
        GaugeConfig::GaugeConfig voltmeter = loadGaugeConfig(VOLTMETER_GAUGE_GROUP);
        voltmeter.min = DEFAULT_VOLTMETER_GAUGE_MIN;
        voltmeter.max = DEFAULT_VOLTMETER_GAUGE_MAX;
        mGaugeConfigs.insert(VOLTMETER_GAUGE_GROUP, voltmeter);

        // speedo
        mSpeedoGaugeConfig.gaugeConfig = loadGaugeConfig(SPEEDOMETER_GAUGE_GROUP);
        if (mSpeedoGaugeConfig.gaugeConfig.displayUnits.compare(Units::UNITS_MPH, Qt::CaseInsensitive) == 0) {
            mSpeedoGaugeConfig.gaugeConfig.min = 0.0;
            mSpeedoGaugeConfig.gaugeConfig.max =
                mSpeedoGaugeConfig.gaugeConfig.max == 0 ?
                    DEFAULT_SPEEDO_GAUGE_MAX_MPH :
                    mSpeedoGaugeConfig.gaugeConfig.max;
            mSpeedoGaugeConfig.gaugeConfig.highAlarm = mSpeedoGaugeConfig.gaugeConfig.max;
            mSpeedoGaugeConfig.gaugeConfig.lowAlarm = mSpeedoGaugeConfig.gaugeConfig.min;
        } else {
            mSpeedoGaugeConfig.gaugeConfig.min = 0.0;
            mSpeedoGaugeConfig.gaugeConfig.max =
                mSpeedoGaugeConfig.gaugeConfig.max == 0 ?
                    DEFAULT_SPEEDO_GAUGE_MAX_KPH :
                    mSpeedoGaugeConfig.gaugeConfig.max;
            mSpeedoGaugeConfig.gaugeConfig.highAlarm = mSpeedoGaugeConfig.gaugeConfig.max;
            mSpeedoGaugeConfig.gaugeConfig.lowAlarm = mSpeedoGaugeConfig.gaugeConfig.min;
        }
        mGaugeConfig->beginGroup(SPEEDOMETER_GAUGE_GROUP);
        mSpeedoGaugeConfig.topSource = mGaugeConfig->value(TOP_VALUE_SOURCE).toString();
        mSpeedoGaugeConfig.topUnits = mGaugeConfig->value(TOP_VALUE_UNITS).toString();

        printKeys("Speedometer: ", mGaugeConfig);

        mGaugeConfig->endGroup();

        //tacho
        mGaugeConfig->beginGroup(TACHOMETER_GAUGE_GROUP);
        mTachGaugeConfig.maxRpm = mGaugeConfig->value(MAX_RPM).toInt();
        mTachGaugeConfig.redline = mGaugeConfig->value(REDLINE).toInt();

        printKeys("Tachometer: ", mGaugeConfig);

        mGaugeConfig->endGroup();

        return true;
    }

    /**
     * @brief Load individual gauge config
     * @param groupName: Gauge group name
     * @return gauge config
     */
    GaugeConfig::GaugeConfig loadGaugeConfig(QString groupName) {
        mGaugeConfig->beginGroup(groupName);

        GaugeConfig::GaugeConfig conf;

        conf.min = mGaugeConfig->value(MIN_VALUE, "").toReal();
        conf.max = mGaugeConfig->value(MAX_VALUE, "").toReal();
        conf.highAlarm = mGaugeConfig->value(HIGH_ALARM, "").toReal();
        conf.lowAlarm = mGaugeConfig->value(LOW_ALARM, "").toReal();
        conf.displayUnits = mGaugeConfig->value(GAUGE_UNITS, "").toString();

        printKeys(groupName, mGaugeConfig);

        mGaugeConfig->endGroup();

        return conf;
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
            if (key == V_SUPPLY_KEY) {
                mSensorSupplyVoltage = mConfig->value(key, DEFAULT_V_SUPPLY).toReal();
            } else {
                mSensorChannelConfig.insert(key, mConfig->value(key, -1).toInt());
            }
        }

        printKeys("Sensor Channels ", mConfig);

        mConfig->endGroup();

        // Load dash light configuration
        mConfig->beginGroup(DASH_LIGHT_GROUP);

        for (auto key : mConfig->childKeys()) {
            mDashLightConfig.insert(key, mConfig->value(key, -1).toInt());
        }

        printKeys("Dash Light Config ", mConfig);

        mConfig->endGroup();

        // user input group
        mConfig->beginGroup(USER_INPUT_GROUP);

        for (QString key : mConfig->childKeys()) {
            if (QString::compare(key, USER_INPUT1_MAP) == 0) {
                mUserInputConfig.insert(0, mKeyMap.value(mConfig->value(key, "Key_Left").toString(), USER_INPUT_DEFAULT_KEY));
            } else if (QString::compare(key, USER_INPUT2_MAP) == 0) {
                mUserInputConfig.insert(1, mKeyMap.value(mConfig->value(key, "Key_A").toString(), USER_INPUT_DEFAULT_KEY));
            } else if (QString::compare(key, USER_INPUT3_MAP) == 0) {
                mUserInputConfig.insert(2, mKeyMap.value(mConfig->value(key, "Key_B").toString(), USER_INPUT_DEFAULT_KEY));
            } else if (QString::compare(key, USER_INPUT4_MAP) == 0) {
                mUserInputConfig.insert(3, mKeyMap.value(mConfig->value(key, "Key_Right").toString(), USER_INPUT_DEFAULT_KEY));
            } else if (QString::compare(key, USER_INPUT_LONG_PRESS_DURATION) == 0) {
                mUserInputPinConfig.insert(key, mConfig->value(key, DEFAULT_LONG_PRESS_DURATION_MSEC).toInt());
            } else {
                mUserInputPinConfig.insert(key, mConfig->value(key).toInt());
            }
        }

        printKeys("User Inputs: ", mConfig);
        mConfig->endGroup();

        //load map sensor config
        mConfig->beginGroup(MAP_SENSOR_GROUP);

        for (auto key : mConfig->childKeys()) {
            if (key == PRESSURE_AT_0V) {
                mMapSensorConfig.p0V = mConfig->value(key, -1).toReal();
            } else if (key == PRESSURE_AT_5V) {
                mMapSensorConfig.p5V = mConfig->value(key, -1).toReal();
            } else if (key == PRESSURE_ATM) {
                mMapSensorConfig.pAtm = mConfig->value(key, -1).toReal();
            } else if (key == PRESSURE_UNITS) {
                // default to kPa
                QString units = mConfig->value(key, Units::UNITS_KPA).toString();
                mMapSensorConfig.units = Units::getPressureUnits(units);
            }
        }

        printKeys("Map Sensor ", mConfig);

        mConfig->endGroup();

        // Temperature sensor config
        int size = mConfig->beginReadArray(TEMP_SENSOR_GROUP);
        for (int i = 0; i < size; ++i) {
            SensorConfig::TempSensorConfig conf;
            mConfig->setArrayIndex(i);

            conf.rBalance = mConfig->value(TEMP_R_BALANCE, 1000).toReal();
            conf.t1 = mConfig->value(T1_TEMP, -1).toReal();
            conf.t2 = mConfig->value(T2_TEMP, -1).toReal();
            conf.t3 = mConfig->value(T3_TEMP, -1).toReal();
            conf.r1 = mConfig->value(T1_RES, -1).toReal();
            conf.r2 = mConfig->value(T2_RES, -1).toReal();
            conf.r3 = mConfig->value(T3_RES, -1).toReal();

            QString units = mConfig->value(TEMP_UNITS, Units::UNITS_K).toString();
            conf.units = Units::getTempUnits(units);

            QString type = mConfig->value(TEMP_TYPE, TEMP_TYPE_COOLANT).toString();
            if (type.compare(TEMP_TYPE_COOLANT, Qt::CaseInsensitive) == 0) {
                conf.type = SensorConfig::TemperatureSensorType::COOLANT;
            } else if (type.compare(TEMP_TYPE_OIL, Qt::CaseInsensitive) == 0) {
                conf.type = SensorConfig::TemperatureSensorType::OIL;
            } else if (type.compare(TEMP_TYPE_AMBIENT, Qt::CaseInsensitive) == 0) {
                conf.type = SensorConfig::TemperatureSensorType::AMBIENT;
            } else {
                qDebug() << "Unrecognized temperature sensor type, assuming coolant.  Fix config.ini file if not correct";
                conf.type = SensorConfig::TemperatureSensorType::COOLANT;
            }

            mTempSensorConfigs.append(conf);

            printKeys("Temp Sensor ", mConfig);
        }
        mConfig->endArray();

        //tach input config
        mConfig->beginGroup(TACH_INPUT_GROUP);

        mTachConfig.pulsesPerRot = mConfig->value(TACH_PULSES_PER_ROTATION, 2).toInt(); // default to 4 cylinder
        mTachConfig.maxRpm = mConfig->value(TACH_MAX_RPM, 9000).toInt(); // default rpm is 9000 (a bit aspirational)
        mTachConfig.avgNumSamples = mConfig->value(TACH_AVG_NUM_SAMPLES, 4).toInt(); // default is to average over last 4 tach pulse spacing

        printKeys("Tach Input ", mConfig);

        mConfig->endGroup();

        size = 0;
        size = mConfig->beginReadArray(RESISTIVE_SENSOR_GROUP);
        for (int i = 0; i < size; ++i) {
            mConfig->setArrayIndex(i);
            SensorConfig::ResistiveSensorConfig rSensorConf;
            // sensor type/name
            rSensorConf.type = mConfig->value(RES_SENSOR_TYPE, "").toString();

            // sensor fit type
            QList fit = mConfig->value(RES_SENSOR_FIT_TYPE, "").toList();
            if (fit.at(0).toString() == RES_SENSOR_FIT_TYPE_POLYNOMIAL && fit.length() == 2) {
                rSensorConf.fitType = SensorConfig::ResistiveSensorType::POLYNOMIAL;
                rSensorConf.order = fit.at(1).toInt();
            } else {
                rSensorConf.fitType = SensorConfig::ResistiveSensorType::INTERPOLATION;
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

            // y value units
            rSensorConf.units = mConfig->value(RES_SENSOR_UNITS, "").toString();

            // lag coefficient
            rSensorConf.lag = mConfig->value(RES_SENSOR_LAG, 1.0).toReal();

            mResistiveSensorConfig.insert(rSensorConf.type, rSensorConf);
            printKeys("Resistive Sensor: ", mConfig);


        }
        mConfig->endArray();

        size = 0;
        size = mConfig->beginReadArray(ANALOG_INPUT_12V_GROUP);
        for (int i = 0; i < size; ++i) {
            mConfig->setArrayIndex(i);

            Analog12VInput::Analog12VInputConfig conf;

            conf.type = mConfig->value(ANALOG_INPUT_12V_NAME, "").toString();
            conf.optoR1 = mConfig->value(ANALOG_INPUT_12V_OPTO_R1, 1).toReal();
            conf.optoR2 = mConfig->value(ANALOG_INPUT_12V_OPTO_R2, 1).toReal();
            conf.inputR1 = mConfig->value(ANALOG_INPUT_12V_INPUT_R1, 1).toReal();
            conf.inputR2 = mConfig->value(ANALOG_INPUT_12V_INPUT_R2, 1).toReal();
            conf.gainK3 = mConfig->value(ANALOG_INPUT_12V_OPTO_GAIN_K3, 1).toReal();
            conf.offset = mConfig->value(ANALOG_INPUT_12V_OFFSET, 0).toReal();

            // resistance values
            QList r = mConfig->value(ANALOG_INPUT_12V_X_VALUES, "").toList();
            for (QVariant val : r) {
                conf.x.push_back(val.toReal());
            }

            // y values (fuel level, pressure, etc)
            QList y = mConfig->value(ANALOG_INPUT_12V_Y_VALUES, "").toList();
            for (QVariant val : y) {
                conf.y.push_back(val.toReal());
            }
            if (conf.x.length() > 0) {
                conf.order = 1;
            } else {
                conf.order = 0;
            }

            mAnalog12VInputConfig.insert(conf.type, conf);
            printKeys("Analog 12V input: ", mConfig);
        }
        mConfig->endArray();


        // VSS Input Configuration
        mConfig->beginGroup(VSS_INPUT_GROUP);

        mVssInputConfig.pulsePerRot = mConfig->value(VSS_PULSES_PER_ROTATION, 12).toInt();
        mVssInputConfig.tireDiameter = mConfig->value(VSS_TIRE_DIAMETER, 24.9).toReal();
        QString diameterUnits =  mConfig->value(VSS_TIRE_DIAMETER_UNITS, "inch").toString().toLower();
        mVssInputConfig.tireDiameterUnits = Units::getDistanceUnits(diameterUnits);
        mVssInputConfig.pulsePerUnitDistance = mConfig->value(VSS_PULSES_PER_DISTANCE, 0).toInt();
        QString distanceUnits = mConfig->value(VSS_DISTANCE_UNITS, "mile").toString().toLower();
        mVssInputConfig.distanceUnits = Units::getDistanceUnits(distanceUnits);
        mVssInputConfig.maxSpeed = mConfig->value(VSS_MAX_SPEED, 160).toInt();
        mVssInputConfig.useGps = mConfig->value(VSS_USE_GPS, false).toBool();

        printKeys("VSS Input: ", mConfig);

        mConfig->endGroup();

        mConfig->beginGroup(BACKLIGHT_GROUP);
        mBacklightConfig.minDutyCycle = mConfig->value(BACKLIGHT_MIN_DUTY_CYCLE, 0.2).toReal();
        mBacklightConfig.maxDutyCycle = mConfig->value(BACKLIGHT_MAX_DUTY_CYCLE, 1.0).toReal();
        mBacklightConfig.lightsOffDutyCycle = mConfig->value(BACKLIGHT_LIGHTS_OFF_DUTY_CYCLE, 1.0).toReal();
        mBacklightConfig.lightsOnDutyCycle = mConfig->value(BACKLIGHT_LIGHTS_ON_DUTY_CYCLE, 0.6).toReal();
        mBacklightConfig.minDimmerRatio = mConfig->value(BACKLIGHT_MIN_DIMMER_RATIO, 0.82).toReal();
        mBacklightConfig.maxDimmerRatio = mConfig->value(BACKLIGHT_MAX_DIMMER_RATIO, 0.93).toReal();
        mBacklightConfig.useDimmer = mConfig->value(BACKLIGHT_USE_DIMMER, true).toBool();
        mBacklightConfig.activeLow = mConfig->value(BACKLIGHT_ACTIVE_LOW, false).toBool();

        printKeys("Backlight Config: ", mConfig);

        mConfig->endGroup();

        return keys.size() > 0;
    }

    /**
     * @brief Print all child keys for the current config subgroup
     * @param setting: Group name to output to log
     */
    void printKeys(QString setting, QSettings * config) {
        for (auto key : config->childKeys()) {
            qDebug() << setting << key << ": " << config->value(key, "N/A").toStringList();
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
    SensorConfig::MapSensorConfig getMapSensorConfig() {
        return mMapSensorConfig;
    }

    /**
     * @brief Get temp sensor configurations
     * @return QList of temperature sensor configurations
     */
    QList<SensorConfig::TempSensorConfig> * getTempSensorConfigs() {
        return &mTempSensorConfigs;
    }

    /**
     * @brief Get Tach Input configuration
     * @return tach input configuration
     */
    SensorConfig::TachInputConfig getTachInputConfig() {
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
    SensorConfig::ResistiveSensorConfig getResistiveSensorConfig(QString name) {
        SensorConfig::ResistiveSensorConfig empty;
        return mResistiveSensorConfig.value(name, empty);
    }

    /**
     * @brief Get 12V analog input config
     * @param name: 12 analog input name
     * @return input config
     */
    Analog12VInput::Analog12VInputConfig getAnalog12VInputConfig(QString name) {
        Analog12VInput::Analog12VInputConfig empty;
        return mAnalog12VInputConfig.value(name, empty);
    }

    /**
     * @brief Get vehicle speed sensor config
     * @return
     */
    SensorConfig::VssInputConfig getVssConfig() {
        return mVssInputConfig;
    }

    /**
     * @brief Get gauge config
     * @param name: gauge name
     * @return Gauge config
     */
    GaugeConfig::GaugeConfig getGaugeConfig(QString name) {
        GaugeConfig::GaugeConfig empty;
        return mGaugeConfigs.value(name, empty);
    }

    /**
     * @brief Get speedo gauge config
     * @return Speedo gauge config
     */
    GaugeConfig::SpeedoConfig getSpeedoConfig() {
        return mSpeedoGaugeConfig;
    }

    /**
     * @brief Get tachometer gauge config
     * @return Tachometer gauge config
     */
    GaugeConfig::TachoConfig getTachGaugeConfig() {
        return mTachGaugeConfig;
    }

    SensorConfig::OdometerConfig getOdometerConfig(QString name) {
        for (auto conf : mOdoConfig) {
            if (conf.name == name) {
                return conf;
            }
        }
        return {Units::DistanceUnits::MILE, 0, 0, ""};
    }

    BacklightControlConfig_t getBackLightConfig() {
        return mBacklightConfig;
    }

    QList<CanFrameConfig> getCanFrameConfigs() {
        return mCanFrameConfigs;
    }

    CanFrameConfig getCanFrameConfig(QString name) {
        for (CanFrameConfig conf : mCanFrameConfigs) {
            if (conf.getName() == name) {
                return conf;
            }
        }
        // return empty config
        CanFrameConfig conf(0x00, 0x00, 0x00, false, "", "");
        return conf;
    }

    QMap<int, Qt::Key> geUserInputConfig() {
        return mUserInputConfig;
    }

    QMap<QString, int> getUserInputPinConfig() {
        return mUserInputPinConfig;
    }

    qreal getSensorSupplyVoltage() {
        return mSensorSupplyVoltage;
    }

signals:

public slots:

private:
    QSettings * mConfig = nullptr;  //!< QSettings for reading config.ini file
    QMap<QString, int> mSensorChannelConfig; //!< sensor channel configuration
    qreal mSensorSupplyVoltage = DEFAULT_V_SUPPLY;
    QMap<QString, int> mDashLightConfig; //!< dash light gpio configuration
    QMap<int, Qt::Key> mUserInputConfig;
    QMap<QString, int> mUserInputPinConfig;
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

    QSettings * mOdometerConfig = nullptr;
    QList<SensorConfig::OdometerConfig> mOdoConfig;

    BacklightControlConfig_t mBacklightConfig;

    QSettings * mCanConfig;
    bool mEnableCan = false;
    QList<CanFrameConfig> mCanFrameConfigs;

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

    /**
     * @brief Initialize User Input Keymap -- this is gross
     * @return User Input Key map
     */
    static QMap<QString, Qt::Key> initKeyMap() {
        QMap<QString, Qt::Key> map;

        map.insert("Key_Left", Qt::Key::Key_Left);
        map.insert("Key_Right", Qt::Key::Key_Right);
        map.insert("Key_Up", Qt::Key::Key_Up);
        map.insert("Key_Down", Qt::Key::Key_Down);
        map.insert("Key_A", Qt::Key::Key_A);
        map.insert("Key_B", Qt::Key::Key_B);
        map.insert("Key_C", Qt::Key::Key_C);
        map.insert("Key_D", Qt::Key::Key_D);
        map.insert("Key_1", Qt::Key::Key_1);
        map.insert("Key_2", Qt::Key::Key_2);
        map.insert("Key_3", Qt::Key::Key_3);
        map.insert("Key_4", Qt::Key::Key_4);

        return map;
    }

    QMap<QString, Qt::Key> mKeyMap = initKeyMap();

};

#endif // CONFIG_H
