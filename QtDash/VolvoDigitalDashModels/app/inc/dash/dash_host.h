#ifndef DASH_HOST_H
#define DASH_HOST_H

#include <QObject>
#include <QQmlContext>
#include <QMap>
#include <QFile>
#include <QKeyEvent>
#include <QDir>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <odometer_model.h>

#include <config.h>
#include <config_keys.h>
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
        QObject(parent), mContext(context), mEventTiming(parent),
        mConfig(parent, "../../../config.ini",
                "../../../config_gauges.ini",
                "../../../config_odo.ini",
                "../../../config_can.ini") {

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

        GaugeConfig::GaugeConfig gaugeConfig;
        gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);

        initAccessoryGuage(
            COOLANT_TEMP_MODEL_NAME,
            gaugeConfig.min,
            gaugeConfig.max,
            gaugeConfig.displayUnits,
            gaugeConfig.lowAlarm,
            gaugeConfig.highAlarm);

        initAccessoryGuage(FUEL_LEVEL_MODEL_NAME, 0.0, 100.0, "%", 10.0, 200.0);
        gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::OIL_PRESSURE_GAUGE_GROUP);
        initAccessoryGuage(
            OIL_PRESSURE_MODEL_NAME,
            gaugeConfig.min,
            gaugeConfig.max,
            gaugeConfig.displayUnits,
            gaugeConfig.lowAlarm,
            gaugeConfig.highAlarm);


        gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::OIL_TEMPERATURE_GAUGE_GROUP);
        initAccessoryGuage(
            OIL_TEMPERATURE_MODEL_NAME,
            gaugeConfig.min,
            gaugeConfig.max,
            gaugeConfig.displayUnits,
            gaugeConfig.lowAlarm,
            gaugeConfig.highAlarm);

        gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::BOOST_GAUGE_GROUP);
        initAccessoryGuage(
            BOOST_GAUGE_MODEL_NAME,
            gaugeConfig.min,
            gaugeConfig.max,
            gaugeConfig.displayUnits,
            gaugeConfig.lowAlarm,
            gaugeConfig.highAlarm);

        initAccessoryGuage(VOLT_METER_MODEL_NAME, 10.0, 16.0, "V", 12.0, 15.0);
        initDashLights();
        initOdometer();

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
    void keyPress(QKeyEvent * event);
public slots:
    void odoTripReset(int trip) {
        switch (trip) {
        case 0:
            mOdometerModel.setTripAValue(0.0);
            break;
        case 1:
            mOdometerModel.setTripBValue(0.0);
            break;
        default:
            break;
        }
    }

    /**
     * @brief Update tachometer model
     */
    void sysfsUpdate() {
        QString tempPath = "/sys/class/hwmon/hwmon4/temp1_input";
        QString rpmPath = "/sys/bus/cpu/devices/cpu0/cpufreq/scaling_cur_freq";
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

            GaugeConfig::GaugeConfig gaugeConfig;
            gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);

            qreal temp = coreTemp.toFloat() / 1000.0;
            qreal tVal = SensorUtils::convert(temp, gaugeConfig.displayUnits, Units::UNITS_C);
            qreal tempF = SensorUtils::convert(temp, Units::UNITS_F, Units::UNITS_C);

            mTempFuelModel.setCurrentTemp(tVal);
            mSpeedoModel.setTopValue(tempF);
            mCoolantTempModel.setCurrentValue(tVal);

            mOilTemperatureModel.setCurrentValue(
                SensorUtils::convert(
                    temp,
                    mConfig.getGaugeConfig(ConfigKeys::OIL_TEMPERATURE_GAUGE_GROUP).displayUnits,
                    Units::UNITS_C)
            );

        }


        mOdometerModel.setOdometerValue(mOdometerModel.odometerValue() + 0.1);
        mOdometerModel.setTripAValue(mOdometerModel.tripAValue() + 0.1);
        mOdometerModel.setTripBValue(mOdometerModel.tripBValue() + 0.1);

//        static int i = 0;
//        if (++i % 100 == 0) {
//            Config::OdometerConfig_t c = mConfig.getOdometerConfig(Config::ODO_NAME_ODOMETER);
//            c.value = mOdometerModel.odometerValue();
//            mConfig.writeOdometerConfig(Config::ODO_NAME_ODOMETER, c);

//            c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPA);
//            c.value = mOdometerModel.tripAValue();
//            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPA, c);

//            c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPB);
//            c.value = mOdometerModel.tripBValue();
//            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPB, c);
//        }


        if(rpmFile.isOpen())
        {
            QString rpmString = rpmStream.readLine();
            int rpm = rpmString.toInt();
            rpm /= 1000;
            mTachModel.setRpm(rpm);

            // qreal boost_psi = ((float)rpm/1000.0) * 5.0;
            static qreal boost_psi = -10;

            auto mGaugeConfig = mConfig.getGaugeConfig(ConfigKeys::BOOST_GAUGE_GROUP);
            QString units = Units::UNITS_PSI;
            QString displayUnits = mGaugeConfig.displayUnits;

            auto val = boost_psi;
            if (mGaugeConfig.altDisplayUnits.use && mGaugeConfig.altDisplayUnits.checkCutoff(val)) {
                mBoostModel.setUnits(mGaugeConfig.altDisplayUnits.displayUnits);
                displayUnits = mGaugeConfig.altDisplayUnits.displayUnits;
            } else {
                mBoostModel.setUnits(mGaugeConfig.displayUnits);
            }

            mBoostModel.setCurrentValue(SensorUtils::convert(boost_psi,
                                    displayUnits,
                                    units)
                );

            boost_psi += 0.3;
            if (boost_psi > 20) {
                boost_psi = -20;
            }

            qreal oilPBar = ((float)rpm / 1000.0);
            qreal oilP = SensorUtils::convert(oilPBar,
                                             mConfig.getGaugeConfig(ConfigKeys::OIL_PRESSURE_GAUGE_GROUP).displayUnits,
                                             Units::UNITS_BAR);
            mOilPressureModel.setCurrentValue( oilP );

            float speedMph = rpm / 100;
            qreal speedo = SensorUtils::convert(speedMph, mConfig.getSpeedoConfig().gaugeConfig.displayUnits, Units::UNITS_MPH);
            mSpeedoModel.setCurrentValue(speedo);
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

        //mSpeedoModel.setCurrentValue(mSpeedoModel.currentValue() + 0.5);
        if (mSpeedoModel.currentValue() > mSpeedoModel.maxValue()) {
            mSpeedoModel.setCurrentValue(0.0);
        }

        mTachModel.setRpm(mTachModel.rpm() + 100);
        if (mTachModel.rpm() > 9000) {
            mTachModel.setRpm(0);
        }


//        mBoostModel.setCurrentValue(mBoostModel.currentValue() + 1);
//        mFuelLevelModel.setCurrentValue(mFuelLevelModel.currentValue() + 1);
        mCoolantTempModel.setCurrentValue(mCoolantTempModel.currentValue() + 1);
        mOilTemperatureModel.setCurrentValue(mOilTemperatureModel.currentValue() + 1);

//        if (mBoostModel.currentValue() > mBoostModel.maxValue()) {
//            mBoostModel.setCurrentValue(-25.0);
//        }


//        if (mFuelLevelModel.currentValue() > mFuelLevelModel.maxValue()) {
//            mFuelLevelModel.setCurrentValue(0);
//        }


        if (mCoolantTempModel.currentValue() > mCoolantTempModel.maxValue()) {
            mCoolantTempModel.setCurrentValue(90);
        }

        if (mOilTemperatureModel.currentValue() > mOilTemperatureModel.maxValue()) {
            mOilTemperatureModel.setCurrentValue(140);
        }

//        static int key = 0;
//        if(++key % 10 == 0) {
//            QKeyEvent * ev = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
//            keyPress(ev);
//        }

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

    void initOdometer() {
        mOdometerModel.setOdometerValue(mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER).value);
        mOdometerModel.setTripAValue(mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPA).value);
        mOdometerModel.setTripBValue(mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPB).value);

        mContext->setContextProperty(OdometerModel::ODOMETER_MODEL_NAME,
                                     &mOdometerModel);
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
        (void)speedUnits;
        (void)topUnits;
        (void)maxSpeed;

        //Init Speedo
        mSpeedoModel.setMaxValue(mConfig.getSpeedoConfig().gaugeConfig.max);
        mSpeedoModel.setMinValue(mConfig.getSpeedoConfig().gaugeConfig.min);
        mSpeedoModel.setUnits(mConfig.getSpeedoConfig().gaugeConfig.displayUnits);
        mSpeedoModel.setCurrentValue(0);
        mSpeedoModel.setTopValue(0);
        mSpeedoModel.setTopUnits(mConfig.getSpeedoConfig().topUnits); // "°F"

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
    void initTempFuelCluster() {
        GaugeConfig::GaugeConfig gaugeConfig;
        gaugeConfig = mConfig.getGaugeConfig(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);

        /** Init temp/fuel gauge **/
        mTempFuelModel.setMinTemp(gaugeConfig.min);
        mTempFuelModel.setMaxTemp(gaugeConfig.max);
        mTempFuelModel.setTempUnits(gaugeConfig.displayUnits);
        mTempFuelModel.setHighTempAlarm(gaugeConfig.highAlarm);
        mTempFuelModel.setLowFuelAlarm(10);

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
            gauge->setUnits(units);
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
        mDashLights = new DashLights(this->parent(), &mConfig);
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
    OdometerModel mOdometerModel;

    // Inputs
    GpsHelper * mGpsHelper;

    // Timing
    EventTimers mEventTiming;

    //Config
    Config mConfig;
};

#endif // DASH_HOST_H
