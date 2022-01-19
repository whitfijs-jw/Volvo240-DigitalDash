#ifndef DASH_NEW_H
#define DASH_NEW_H

#include <QObject>
#include <QQmlContext>
#include <QMap>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>

#include <config.h>
#include <event_timers.h>

#include <sensor_source_adc.h>
#include <sensor_source_gps.h>

#include <sensor_map.h>
#include <sensor_ntc.h>
#include <sensor_voltmeter.h>
#include <sensor_resistive.h>
#include <sensor_speedo.h>

#include <gauge_accessory.h>
#include <gauge_speedo.h>

class DashNew : public QObject {
    Q_OBJECT
public:
    static constexpr char COOLANT_TEMP_MODEL_NAME[] = "coolantTempModel";
    static constexpr char FUEL_LEVEL_MODEL_NAME[] = "fuelLevelModel";
    static constexpr char OIL_PRESSURE_MODEL_NAME[] = "oilPModel";
    static constexpr char OIL_TEMPERATURE_MODEL_NAME[] = "oilTModel";
    static constexpr char BOOST_GAUGE_MODEL_NAME[] = "boostModel";
    static constexpr char VOLT_METER_MODEL_NAME[] = "voltMeterModel";
    static constexpr char TACH_MODEL_NAME[] = "rpmModel";
    static constexpr char SPEEDO_MODEL_NAME[] = "speedoModel";
    static constexpr char TEMP_FUEL_CLUSTER_MODEL_NAME[] = "tempFuelModel";

    /**
     * @brief Constructor
     * @param parent: parent qobject
     * @param context: qml context to link the gauge models to their respective c++ model
     */
    DashNew(QObject * parent, QQmlContext * context) :
        QObject(parent), mContext(context), mEventTiming(parent), mConfig(parent) {

    }

    void initSensorSources() {
        mAdcSource = new AdcSource(this->parent(), &mConfig);
        mGpsSource = new GpsSource(this->parent(), &mConfig);
    }

    void initSensors() {
        //map sensor
        mMapSensor = new Map_Sensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::MAP_SENSOR_KEY)
                    );

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mMapSensor->getChannel());
        });

        // coolant temp sensor
        mCoolantTempSensor = new NtcSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::COOLANT_TEMP_KEY),
                    Config::TemperatureSensorType::COOLANT);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mCoolantTempSensor->getChannel());
        });

        // ambient temp sensor
        mAmbientTempSensor = new NtcSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::AMBIENT_TEMP_KEY),
                    Config::TemperatureSensorType::AMBIENT);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mAmbientTempSensor->getChannel());
        });

        // oil temp sensor
        mOilTempSensor = new NtcSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::OIL_TEMP_KEY),
                    Config::TemperatureSensorType::OIL);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mOilTempSensor->getChannel());
        });

        // oil pressure sensor
        mOilPressureSensor = new ResistiveSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::OIL_PRESSURE_KEY),
                    mConfig.getResistiveSensorConfig(Config::RES_SENSOR_TYPE_OIL_PRESSURE)
                    );

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mOilPressureSensor->getChannel());
        });

        //fuel level sensor
        mFuelLevelSensor = new ResistiveSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::FUEL_LEVEL_KEY),
                    mConfig.getResistiveSensorConfig(Config::RES_SENSOR_TYPE_FUEL_LEVEL)
                    );

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mFuelLevelSensor->getChannel());
        });


        // voltmeter
        mVoltmeterSensor = new VoltmeterSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::FUSE8_12V_KEY),
                    mConfig.getAnalog12VInputConfig(Config::ANALOG_INPUT_12V_VOLTMETER)
                    );

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mVoltmeterSensor->getChannel());
        });

        // speedometer
        mSpeedoSensor = new SpeedometerSensor(
                    this->parent(), &mConfig, mGpsSource,
                    (int) GpsSource::GpsDataChannel::SPEED_MILES_PER_HOUR
                    );
    }

    void initAccessoryGauges() {
        // boost gauge
        QList<Sensor *> boostSensors = {mMapSensor};
        mBoostGauge = new AccessoryGauge(
                    this->parent(), &mConfig, boostSensors, &mBoostModel,
                    AccessoryGaugeModel::BOOST_GAUGE_MODEL_NAME,
                    mContext);

        // coolant temp gauge
        QList<Sensor *> coolantSensors = {mCoolantTempSensor};
        mCoolantTempGauge = new AccessoryGauge(
                    this->parent(), &mConfig, coolantSensors,
                    &mCoolantTempModel, AccessoryGaugeModel::COOLANT_TEMP_MODEL_NAME,
                    mContext);

        // oil temp gauge
        QList<Sensor *> oilTempSensors = {mOilTempSensor};
        mOilTempGauge = new AccessoryGauge(
                    this->parent(), &mConfig, oilTempSensors,
                    &mOilTemperatureModel, AccessoryGaugeModel::OIL_TEMPERATURE_MODEL_NAME,
                    mContext);

        // voltmeter
        QList<Sensor *> voltmeterSensors = {mVoltmeterSensor};
        mVoltmeterGauge = new AccessoryGauge(
                    this->parent(), &mConfig, voltmeterSensors,
                    &mVoltMeterModel, AccessoryGaugeModel::VOLT_METER_MODEL_NAME,
                    mContext
                    );

        // fuel level (acc gauge)
        QList<Sensor *> fuelGaugeSensors = {mFuelLevelSensor};
        mFuelLevelGauge = new AccessoryGauge(
                    this->parent(), &mConfig, fuelGaugeSensors,
                    &mFuelLevelModel, AccessoryGaugeModel::FUEL_LEVEL_MODEL_NAME,
                    mContext
                    );

        // oil pressure gauge
        QList<Sensor *> oilPressureSensors = {mOilPressureSensor};
        mOilPressureGauge = new AccessoryGauge(
                    this->parent(), &mConfig, oilPressureSensors,
                    &mOilPressureModel, AccessoryGaugeModel::OIL_PRESSURE_MODEL_NAME,
                    mContext
                    );
    }

    void initSpeedo() {
        // init gauge+
        QList<Sensor *> speedoSensors = {mSpeedoSensor, mAmbientTempSensor};
        mSpeedoGauge = new SpeedometerGauge(
                    this->parent(), &mConfig, speedoSensors,
                    &mSpeedoModel, SpeedometerModel::SPEEDO_MODEL_NAME,
                    mContext
                    );
    }

    void init() {
        initSensorSources();
        initSensors();
        initAccessoryGauges();
        initSpeedo();
    }

    void start() {
        mEventTiming.start();
    }

private:
    QQmlContext * mContext;
    EventTimers mEventTiming;
    Config mConfig;

    AdcSource * mAdcSource;
    GpsSource * mGpsSource;

    Map_Sensor * mMapSensor;
    NtcSensor * mCoolantTempSensor;
    NtcSensor * mAmbientTempSensor;
    NtcSensor * mOilTempSensor;
    VoltmeterSensor * mVoltmeterSensor;
    ResistiveSensor * mOilPressureSensor;
    ResistiveSensor * mFuelLevelSensor;
    SpeedometerSensor<GpsSource> * mSpeedoSensor;

    AccessoryGaugeModel mBoostModel;
    AccessoryGaugeModel mOilTemperatureModel;
    AccessoryGaugeModel mCoolantTempModel;
    AccessoryGaugeModel mOilPressureModel;
    AccessoryGaugeModel mFuelLevelModel;
    AccessoryGaugeModel mVoltMeterModel;

    SpeedometerModel mSpeedoModel;

    AccessoryGauge * mBoostGauge;
    AccessoryGauge * mCoolantTempGauge;
    AccessoryGauge * mOilTempGauge;
    AccessoryGauge * mVoltmeterGauge;
    AccessoryGauge * mOilPressureGauge;
    AccessoryGauge * mFuelLevelGauge;

    SpeedometerGauge * mSpeedoGauge;
};

#endif // DASH_NEW_H
