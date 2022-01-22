#ifndef DASH_HOST_H
#define DASH_HOST_H

#include <QObject>
#include <QQmlContext>
#include <QMap>
#include <QFile>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>

#include <config.h>
#include <gps_helper.h>
#include <dash_lights.h>
#include <event_timers.h>
#include <sensor_utils.h>

/**
 * @brief Class for initializing, linking and updating gauge models
 */
class DashHost : public QObject {
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
    DashHost(QObject * parent, QQmlContext * context) :
        QObject(parent), mContext(context), mEventTiming(parent), mConfig(parent, "/home/whitfijs/git/Volvo240-DigitalDash/QtDash/config.ini") {

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
    /**
     * @brief Update tachometer model
     */
    void sysfsUpdate() {
        QString tempPath = "/sys/class/hwmon/hwmon4/temp1_input";
        QString rpmPath = "/sys/class/hwmon/hwmon3/fan1_input";
        QString battPath = "/sys/class/power_supply/BAT0/voltage_now";
        QString fuelLevelPath = "/sys/class/power_supply/BAT0/capacity";

        QFile tempFile(tempPath);
        QFile rpmFile(rpmPath);
        QFile battFile(battPath);
        QFile fuelFile(fuelLevelPath);

        QTextStream tempStream(&tempFile);
        QTextStream rpmStream(&rpmFile);
        QTextStream battStream(&battFile);
        QTextStream fuelStream(&fuelFile);

        tempFile.open(QIODevice::ReadOnly);
        rpmFile.open(QIODevice::ReadOnly);
        battFile.open(QIODevice::ReadOnly);
        fuelFile.open(QIODevice::ReadOnly);

        if(tempFile.isOpen())
        {
            QString coreTemp = tempStream.readLine();
            float temp = coreTemp.toFloat();
            qreal tempF = ((temp/1000.0) * 9.0/5.0)+32.0;
            mOilTemperatureModel.setCurrentValue(tempF);
            mTempFuelModel.setCurrentTemp(tempF);
            mSpeedoModel.setTopValue(tempF);
            mCoolantTempModel.setCurrentValue(tempF);
        }

        if(rpmFile.isOpen())
        {
            QString rpmString = rpmStream.readLine();
            int rpm = rpmString.toInt();
            mTachModel.setRpm(rpm);
            //mBoostModel.setCurrentValue( ((float)rpm/1000.0) * 5.0 );
            mOilPressureModel.setCurrentValue( ((float)rpm / 1000.0 * 3) );
        }

        if(battFile.isOpen())
        {
            QString voltage = battStream.readLine();
            float volts = voltage.toInt();
            mVoltMeterModel.setCurrentValue(volts/1.0e6);
        }

        if(fuelFile.isOpen())
        {
            QString fuelLevel = fuelStream.readLine();
            int level = fuelLevel.toInt();
            mTempFuelModel.setFuelLevel(level);
            mFuelLevelModel.setCurrentValue(level);
        }


        mBoostModel.setCurrentValue(mBoostModel.currentValue() + 1);
        mFuelLevelModel.setCurrentValue(mFuelLevelModel.currentValue() + 1);
        mCoolantTempModel.setCurrentValue(mCoolantTempModel.currentValue() + 1);

        if (mBoostModel.currentValue() > mBoostModel.maxValue()) {
            mBoostModel.setCurrentValue(-25.0);
        }


        if (mFuelLevelModel.currentValue() > mFuelLevelModel.maxValue()) {
            mFuelLevelModel.setCurrentValue(0);
        }


        if (mCoolantTempModel.currentValue() > mCoolantTempModel.maxValue()) {
            mCoolantTempModel.setCurrentValue(120);
        }

        tempFile.close();
        rpmFile.close();
        battFile.close();
        fuelFile.close();
    }
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

        // hook up tach update
        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    this,
                    &DashHost::sysfsUpdate
                    );
    }

    /**
     * @brief Initialize sensor inputs and connect updates to respective models
     */
    void initSensorInputs() {
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

        // init speedo input
        mGpsHelper = new GpsHelper(this->parent());
        QObject::connect(mGpsHelper, SIGNAL(speedUpdateMilesPerHour(qreal)),
                         &mSpeedoModel, SLOT(setCurrentValue(qreal)));

        QObject::connect(this->parent(), SIGNAL(lastWindowClosed()), mGpsHelper, SLOT(close()));

        mGpsHelper->init();

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
    GpsHelper * mGpsHelper;

    // Timing
    EventTimers mEventTiming;

    //Config
    Config mConfig;
};

#endif // DASH_HOST_H
