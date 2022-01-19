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
#include <sensor_map.h>
#include <sensor_ntc.h>
#include <sensor_voltmeter.h>

#include <gauge_accessory.h>

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
    }

    void init() {
        initSensorSources();
        initSensors();
        initAccessoryGauges();
    }

    void start() {
        mEventTiming.start();
    }

private:
    QQmlContext * mContext;
    EventTimers mEventTiming;
    Config mConfig;

    AdcSource * mAdcSource;
    Map_Sensor * mMapSensor;
    NtcSensor * mCoolantTempSensor;
    NtcSensor * mAmbientTempSensor;
    NtcSensor * mOilTempSensor;
    VoltmeterSensor * mVoltmeterSensor;

    AccessoryGaugeModel mBoostModel;
    AccessoryGaugeModel mOilPressureModel;
    AccessoryGaugeModel mOilTemperatureModel;
    AccessoryGaugeModel mCoolantTempModel;

    AccessoryGaugeModel mFuelLevelModel;
    AccessoryGaugeModel mVoltMeterModel;

    AccessoryGauge * mBoostGauge;
    AccessoryGauge * mCoolantTempGauge;
    AccessoryGauge * mOilTempGauge;
    AccessoryGauge * mVoltmeterGauge;
};

#endif // DASH_NEW_H
