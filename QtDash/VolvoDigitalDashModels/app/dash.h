#ifndef DASH_H
#define DASH_H

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
#include <mcp23017.h>
#include <adc.h>
#include <gps_helper.h>
#include <ntc.h>
#include <map_sensor.h>
#include <tach_input.h>
#include <dash_lights.h>
#include <event_timers.h>
#include <analog_sensors.h>


#include <sensor_source_gps.h>
#include <sensor_source_tach.h>


/**
 * @brief Class for initializing, linking and updating gauge models
 */
class Dash : public QObject {
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
    Dash(QObject * parent, QQmlContext * context) :
        QObject(parent), mContext(context), mEventTiming(parent), mConfig(parent) {

        // populate accessory gauge model map
        mAccessoryGaugeModelMap.insert(COOLANT_TEMP_MODEL_NAME, &mCoolantTempModel);
        mAccessoryGaugeModelMap.insert(FUEL_LEVEL_MODEL_NAME, &mFuelLevelModel);
        mAccessoryGaugeModelMap.insert(OIL_PRESSURE_MODEL_NAME, &mOilPressureModel);
        mAccessoryGaugeModelMap.insert(OIL_TEMPERATURE_MODEL_NAME, &mOilTemperatureModel);
        mAccessoryGaugeModelMap.insert(BOOST_GAUGE_MODEL_NAME, &mBoostModel);
        mAccessoryGaugeModelMap.insert(VOLT_METER_MODEL_NAME, &mVoltMeterModel);
    }

    /**
     * @brief Initialize dash
     */
    void init() {
        // initialize models
        initTacho();
        initSpeedo();
        initTempFuelCluster();
        initAccessoryGuage(COOLANT_TEMP_MODEL_NAME, 120.0, 250.0, "°F", 0.0, 220.0);
        initAccessoryGuage(FUEL_LEVEL_MODEL_NAME, 0.0, 100.0, "%", 10.0, 200.0);
        initAccessoryGuage(OIL_PRESSURE_MODEL_NAME, 0.0, 5.0, "bar", 1.0, 4.5);
        initAccessoryGuage(OIL_TEMPERATURE_MODEL_NAME, 120.0, 300.0, "°F", 0.0, 260.0);
        initAccessoryGuage(BOOST_GAUGE_MODEL_NAME, -20.0, 30.0, "psi", -50.0, 18.0);
        initAccessoryGuage(VOLT_METER_MODEL_NAME, 10.0, 16.0, "V", 12.0, 15.0);
        initDashLights();

        // initialize sensor inputs
        initSensorInputs();

        // initialize event timing
        initEventTiming();
    }

    /**
     * @brief start the event timers to start updating the dash gauges
     */
    void start() {
        mEventTiming.start();
    }

signals:
public slots:
private:
    /**
     * @brief Initialize event timer
     */
    void initEventTiming() {
        // hook up dash light timing
        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    mDashLights,
                    &DashLights::update
                    );

//        // hook up tach update
//        QObject::connect(
//                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
//                    &QTimer::timeout,
//                    this,
//                    &Dash::updateTach
//                    );
        // hook up analog sensor updates that don't need 10Hz updates
        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    mSensors,
                    &AnalogSensors::update
                    );

        // hook up fast analog sensor updates
        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
                    &QTimer::timeout,
                    mSensors,
                    &AnalogSensors::updateFast
                    );
    }

    /**
     * @brief Initialize sensor inputs and connect updates to respective models
     */
    void initSensorInputs() {
        mSensors = new AnalogSensors(this->parent(), &mConfig);

        // setup events
        QObject::connect(mSensors, &AnalogSensors::coolantTempUpdate,
                         &mCoolantTempModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::boostPressureUpdate,
                         &mBoostModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::voltMeterUpdate,
                         &mVoltMeterModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::oilTempUpdate,
                         &mOilTemperatureModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::oilPressureUpdate,
                         &mOilPressureModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::fuelLevelUpdate,
                         &mFuelLevelModel, &AccessoryGaugeModel::setCurrentValue);

        QObject::connect(mSensors, &AnalogSensors::ambientTempUpdate,
                         &mSpeedoModel, &SpeedometerModel::setTopValue);

        QObject::connect(mSensors, &AnalogSensors::coolantTempUpdate,
                         &mTempFuelModel, &TempAndFuelGaugeModel::setCurrentTemp);

        QObject::connect(mSensors, &AnalogSensors::fuelLevelUpdate,
                         &mTempFuelModel, &TempAndFuelGaugeModel::setFuelLevel);
    }

    /**
     * @brief Initialize tachometer model and connect model to qml
     * @param maxRpm: Max gauge rpm
     * @param redLine: gauge redline
     */
    void initTacho(int maxRpm = 7000, int redLine = 6000) {
        // Init tach model
        mTachModel.setMaxRpm(maxRpm);
        mTachModel.setRedLine(redLine);
        mTachModel.setRpm(0);


        // hookup c++ model to qml
        mContext->setContextProperty(TACH_MODEL_NAME, &mTachModel);
    }

    /**
     * @brief Initialize speedo model and connect model to qml
     * @param maxSpeed: speedo max
     * @param speedUnits: speedo units
     * @param topUnits: speedo secondary value units
     */
    void initSpeedo(qreal maxSpeed = 120,
                    QString speedUnits = "mph",
                    QString topUnits = "°F") {
        //Init Speedo
        mSpeedoModel.setMaxValue(maxSpeed);
        mSpeedoModel.setMinValue(0);
        mSpeedoModel.setUnits(speedUnits);
        mSpeedoModel.setCurrentValue(0);
        mSpeedoModel.setTopValue(0);
        mSpeedoModel.setTopUnits(topUnits); // "°F"

        // hookup c++ model to qml model
        mContext->setContextProperty(SPEEDO_MODEL_NAME, &mSpeedoModel);
    }

    /**
     * @brief Initialize 240 temp/fuel sub-cluster
     * @param minTemp: minimum coolant gauge temp
     * @param maxTemp: maximum coolant gauge temp
     * @param tempUnits: coolant temp units
     * @param highTempAlarm: high coolant temp alarm
     * @param lowFuelAlarm: low fuel temp alarm
     */
    void initTempFuelCluster(qreal minTemp = 120, qreal maxTemp = 250, QString tempUnits = "°F",
                             qreal highTempAlarm = 220, qreal lowFuelAlarm = 10) {
        /** Init temp/fuel gauge **/
        mTempFuelModel.setMinTemp(minTemp);
        mTempFuelModel.setMaxTemp(maxTemp);
        mTempFuelModel.setTempUnits(tempUnits);
        mTempFuelModel.setHighTempAlarm(highTempAlarm);
        mTempFuelModel.setLowFuelAlarm(lowFuelAlarm);

        mTempFuelModel.setCurrentTemp(0);
        mTempFuelModel.setFuelLevel(0);

        // hookup c++ model to qml model
        mContext->setContextProperty(TEMP_FUEL_CLUSTER_MODEL_NAME, &mTempFuelModel);
    }

    /**
     * @brief Initialize accessory gauge
     * @param gaugeName: accessory gauge qml model name
     * @param minValue: gauge min value
     * @param maxValue: gauge max value
     * @param units: gauge units
     * @param lowAlarm: gauge low alarm
     * @param highAlarm: gauge high alarm
     */
    void initAccessoryGuage(QString gaugeName, qreal minValue,
                            qreal maxValue, QString units,
                            qreal lowAlarm, qreal highAlarm) {
        AccessoryGaugeModel * gauge = mAccessoryGaugeModelMap.value(gaugeName, nullptr);
        if (gauge != nullptr) {
            gauge->setMinValue(minValue);
            gauge->setMaxValue(maxValue);
            gauge->setUnits(units);;
            gauge->setHighAlarm(highAlarm);
            gauge->setLowAlarm(lowAlarm);

            gauge->setCurrentValue(0.0);

            mContext->setContextProperty(gaugeName, gauge);
        }
    }

    /**
     * @brief Initialize dash lights models and connect qml context properties
     */
    void initDashLights() {
        // init models
        mDashLights = new DashLights(this->parent(), mConfig.getDashLightConfig());
        mDashLights->init();

        // hook up models in QML context
        for (auto modelName : mDashLights->getWarningLightModels()->keys()) {
            mContext->setContextProperty(
                        modelName,
                        mDashLights->getWarningLightModels()->value(modelName));
        }

        // Connect indicator models to qml
        for (auto modelName : mDashLights->getIndicatorModels()->keys()) {
            mContext->setContextProperty(
                        modelName,
                        mDashLights->getIndicatorModels()->value(modelName));
        }
    }


    //Qml Context
    QQmlContext * mContext;

    // models
    TachometerModel mTachModel;
    SpeedometerModel mSpeedoModel;
    TempAndFuelGaugeModel mTempFuelModel;
    AccessoryGaugeModel mOilPressureModel;
    AccessoryGaugeModel mOilTemperatureModel;
    AccessoryGaugeModel mBoostModel;
    AccessoryGaugeModel mVoltMeterModel;
    AccessoryGaugeModel mCoolantTempModel;
    AccessoryGaugeModel mFuelLevelModel;
    DashLights * mDashLights;
    QMap<QString, AccessoryGaugeModel*> mAccessoryGaugeModelMap;

    // Inputs
    AnalogSensors * mSensors;

    // Timing
    EventTimers mEventTiming;

    //Config
    Config mConfig;
};

#endif // DASH_H
