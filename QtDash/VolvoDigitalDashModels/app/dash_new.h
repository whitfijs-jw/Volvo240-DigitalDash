#ifndef DASH_NEW_H
#define DASH_NEW_H

#include <QObject>
#include <QQmlContext>
#include <QMap>
#include <QKeyEvent>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <odometer_model.h>

#include <config.h>
#include <event_timers.h>
#include <dash_lights.h>
#include <backlight_control.h>

#include <sensor_source_adc.h>
#include <sensor_source_gps.h>
#include <sensor_source_tach.h>
#include <sensor_source_vss.h>

#include <sensor_map.h>
#include <sensor_ntc.h>
#include <sensor_voltmeter.h>
#include <sensor_resistive.h>
#include <sensor_speedo.h>
#include <sensor_tach.h>
#include <sensor_odometer.h>

#include <gauge_accessory.h>
#include <gauge_speedo.h>
#include <gauge_tach.h>
#include <gauge_temp_fuel_cluster.h>
#include <gauge_odo.h>

#include <sensor_source_can.h>
#include <sensor_can.h>

/**
 * @brief A class to run the digital dash
 */
class DashNew : public QObject {
    Q_OBJECT
public:
    static constexpr char COOLANT_TEMP_MODEL_NAME[] = "coolantTempModel"; //!< coolant temp model name
    static constexpr char FUEL_LEVEL_MODEL_NAME[] = "fuelLevelModel"; //!< fuel level model name
    static constexpr char OIL_PRESSURE_MODEL_NAME[] = "oilPModel"; //!< oil pressure model name
    static constexpr char OIL_TEMPERATURE_MODEL_NAME[] = "oilTModel"; //!< oil temperature model name
    static constexpr char BOOST_GAUGE_MODEL_NAME[] = "boostModel"; //!< boost pressure model name
    static constexpr char VOLT_METER_MODEL_NAME[] = "voltMeterModel"; //!< voltmeter model name
    static constexpr char TACH_MODEL_NAME[] = "rpmModel"; //!< rpm/tacho model name
    static constexpr char SPEEDO_MODEL_NAME[] = "speedoModel"; //!< speedometer model name
    static constexpr char TEMP_FUEL_CLUSTER_MODEL_NAME[] = "tempFuelModel"; //!< 240 combined temp/fuel model name
    static constexpr char ODOMETER_MODEL_NAME[] = "odometerModel";

    /**
     * @brief Constructor
     * @param parent: parent qobject
     * @param context: qml context to link the gauge models to their respective c++ model
     */
    DashNew(QObject * parent, QQmlContext * context) :
        QObject(parent), mContext(context), mEventTiming(parent), mConfig(parent) {

    }

    /**
     * @brief Initialize everything
     */
    void init() {
        initSensorSources();
        initSensors();
        initCanSensors();
        initAccessoryGauges();
        initSpeedo();
        initTacho();
        initOdometer();
        initBackLightControl();

        initDashLights();
    }

    /**
     * @brief Start dash event timers
     */
    void start() {
        mEventTiming.start();
    }

    /**
     * @brief Stop the dash event timers
     */
    void stop() {
        mEventTiming.stop();
    }

signals:
    void keyPress(QKeyEvent * event);

public slots:
    void odoTripReset(int trip) {
        switch (trip) {
        case 0:
            mTripAOdoSensor->reset();
            break;
        case 1:
            mTripBOdoSensor->reset();
            break;
        default:
            break;
        }
    }

private:
    QQmlContext * mContext; //!< QML Context
    EventTimers mEventTiming; //!< Event Timer
    Config mConfig; //!< Dash Config

    DashLights * mDashLights; //!< Dash lights

    AdcSource * mAdcSource; //!< ADC source
    GpsSource * mGpsSource; //!< GPS speed/position/heading source
    TachSource * mTachSource; //!< tach source (pulse counter)
    VssSource * mVssSource; //!< vehicle speed sensor source (pulse counter)
    CanSource * mCanSource; //!< can data source

    Map_Sensor * mMapSensor; //!< map sensor
    NtcSensor * mCoolantTempSensor; //!< coolant temp sensor
    NtcSensor * mAmbientTempSensor; //!< ambient temp sensor
    NtcSensor * mOilTempSensor; //!< oil temp sensor
    VoltmeterSensor * mVoltmeterSensor; //!< voltmeter sensor
    VoltmeterSensor * mDimmerVoltageSensor; //!< rheostat dimmer voltage
    ResistiveSensor * mOilPressureSensor; //!< oil pressure sensor
    ResistiveSensor * mFuelLevelSensor; //!< fuel level sensor
    SpeedometerSensor<GpsSource> * mGpsSpeedoSensor; //!< speedometer w/ gps input
    SpeedometerSensor<VssSource> * mSpeedoSensor; //!< speedometer w/ vss input
    TachSensor * mTachSensor; //!< tachometer sensor
    OdometerSensor * mOdoSensor; //!< odometer
    OdometerSensor * mTripAOdoSensor; //!< trip a counter
    OdometerSensor * mTripBOdoSensor; //!< trip b counter

    AccessoryGaugeModel mBoostModel; //!< boost pressure QML model
    AccessoryGaugeModel mOilTemperatureModel; //!< oil temperature QML model
    AccessoryGaugeModel mCoolantTempModel; //!< coolant temperature QML model
    AccessoryGaugeModel mOilPressureModel; //!< oil pressure QML model
    AccessoryGaugeModel mFuelLevelModel; //!< fuel level QML model
    AccessoryGaugeModel mVoltMeterModel; //!< voltmeter QML model
    TempAndFuelGaugeModel mTempFuelModel; //!< 240 combined temp/fuel QML model
    OdometerModel mOdometerModel; //!< odometer QML model

    SpeedometerModel mSpeedoModel; //!< speedometer QML model
    TachometerModel mTachoModel; //!< Tachometer QML model

    AccessoryGauge * mBoostGauge; //!< boost pressure gauge
    AccessoryGauge * mCoolantTempGauge; //!< coolant temp gauge
    AccessoryGauge * mOilTempGauge; //!< oil temp gauge
    AccessoryGauge * mVoltmeterGauge; //!< voltmeter gauge
    AccessoryGauge * mOilPressureGauge; //!< oil pressure gauge
    AccessoryGauge * mFuelLevelGauge; //!< fuel level gauge
    TempFuelClusterGauge * mTempFuelClusterGauge; //!< 240 combined temp/fuel gauge

    SpeedometerGauge * mSpeedoGauge; //!< speedometer gauge
    TachometerGauge * mTachoGauge; //!< tachometer gauge
    OdometerGauge * mOdoGauge; //!< odometer gauge

    BackLightControl * mBacklightControl;

    QVector<CanSensor *> mCanSensors;

    /**
     * @brief Initialize sensor sources
     */
    void initSensorSources() {
        qDebug() << "Sensor Source Init";
        mAdcSource = new AdcSource(this->parent(), &mConfig);
        mGpsSource = new GpsSource(this->parent(), &mConfig);
        mTachSource = new TachSource(this->parent(), &mConfig);
        mVssSource = new VssSource(this->parent(), &mConfig);
        mCanSource = new CanSource(this->parent(), &mConfig);
    }

    void initCanSensors() {
        for (int channel : mCanSource->getChannelConfigs()->keys()) {
            qDebug() << "CAN Sensor Channel: " << channel;
            CanSensor * sensor = new CanSensor(this->parent(), &mConfig,
                                               mCanSource, channel);
            qDebug() << "CAN Sensor: " << sensor->getGuage();
            mCanSensors.push_back(sensor);
        }
    }

    CanSensor * getCanSensor(QString gaugeName) {
        // check if we have a can sensor
        qDebug() << "Get Can Sensor for: " << gaugeName;
        for (CanSensor * sensor : mCanSensors) {
            qDebug() << "Sensor found: " << sensor->getGuage();
            if (sensor->getGuage().toLower() == gaugeName) {
                return sensor;
            }
        }
        return nullptr;
    }

    /**
     * @brief Initialize sensors
     */
    void initSensors() {
        qDebug() << "Sensor Init";
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

        // rheostat/dimmer voltage
        mDimmerVoltageSensor = new VoltmeterSensor(
                    this->parent(), &mConfig, mAdcSource,
                    mConfig.getSensorConfig().value(Config::DIMMER_VOLTAGE_KEY),
                    mConfig.getAnalog12VInputConfig(Config::ANALOG_INPUT_12V_RHEOSTAT)
                    );

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mAdcSource->update(mDimmerVoltageSensor->getChannel());
        });

        // speedometer
        mGpsSpeedoSensor = new SpeedometerSensor(
                    this->parent(), &mConfig, mGpsSource,
                    (int) GpsSource::GpsDataChannel::SPEED_MILES_PER_HOUR);

        mSpeedoSensor = new SpeedometerSensor(
                    this->parent(), &mConfig, mVssSource,
                    (int) VssSource::VssDataChannel::MPH);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::VERY_FAST_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mVssSource->update((int) VssSource::VssDataChannel::MPH);
        });

        // tacho
        mTachSensor = new TachSensor(
                    this->parent(), &mConfig, mTachSource,
                    (int) TachSource::TachDataChannel::RPM_CHANNEL);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::VERY_FAST_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mTachSource->update((int) TachSource::TachDataChannel::RPM_CHANNEL);
        });

        mOdoSensor = new OdometerSensor (
                    this->parent(), &mConfig, mVssSource,
                    (int) VssSource::VssDataChannel::PULSE_COUNT);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::SLOW_TIMER)),
                    &QTimer::timeout,
                    [=]() {
            mVssSource->update((int) VssSource::VssDataChannel::PULSE_COUNT);
        });

        QObject::connect(
                    mOdoSensor, &OdometerSensor::writeOdoValue,
                    [=](qreal value) {
            Config::OdometerConfig_t c = mConfig.getOdometerConfig(Config::ODO_NAME_ODOMETER);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_ODOMETER, c);
        });

        // trip counters
        Config::OdometerConfig_t confA = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPA);
        mTripAOdoSensor = new OdometerSensor (
                    this->parent(), &mConfig, mVssSource,
                    (int) VssSource::VssDataChannel::PULSE_COUNT, &confA);

        QObject::connect(
                    mTripAOdoSensor, &OdometerSensor::writeOdoValue,
                    [=](qreal value) {
            Config::OdometerConfig_t c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPA);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPA, c);
        });

        Config::OdometerConfig_t confB = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPB);
        mTripBOdoSensor = new OdometerSensor (
                    this->parent(), &mConfig, mVssSource,
                    (int) VssSource::VssDataChannel::PULSE_COUNT, &confB);

        QObject::connect(
                    mTripBOdoSensor, &OdometerSensor::writeOdoValue,
                    [=](qreal value) {
            Config::OdometerConfig_t c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPB);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPB, c);
        });
    }

    /**
     * @brief Initialize the accessory gauges (coolant, fuel level, oil pressure/temp, etc)
     */
    void initAccessoryGauges() {
        qDebug() << "Accessory Gauge Models Init";
        // boost gauge
        CanSensor * sensor = getCanSensor(Config::BOOST_GAUGE_GROUP);

        QList<Sensor *> boostSensors;
        if (sensor != nullptr) {
            boostSensors.push_back(sensor);
        } else {
            boostSensors.push_back(mMapSensor);
        }

        mBoostGauge = new AccessoryGauge(
                    this->parent(), &mConfig, boostSensors, &mBoostModel,
                    AccessoryGaugeModel::BOOST_GAUGE_MODEL_NAME,
                    mContext);

        // coolant temp gauge
        sensor = getCanSensor(Config::COOLANT_TEMP_GAUGE_GROUP);
        QList<Sensor *> coolantSensors;
        if (sensor != nullptr) {
            coolantSensors.push_back(sensor);
        } else {
            coolantSensors.push_back(mCoolantTempSensor);
        }

        mCoolantTempGauge = new AccessoryGauge(
                    this->parent(), &mConfig, coolantSensors,
                    &mCoolantTempModel, AccessoryGaugeModel::COOLANT_TEMP_MODEL_NAME,
                    mContext);

        // oil temp gauge
        sensor = getCanSensor(Config::OIL_TEMPERATURE_GAUGE_GROUP);
        QList<Sensor *> oilTempSensors;
        if (sensor != nullptr) {
            oilTempSensors.push_back(sensor);
        } else {
            oilTempSensors.push_back(mOilTempSensor);
        }

        mOilTempGauge = new AccessoryGauge(
                    this->parent(), &mConfig, oilTempSensors,
                    &mOilTemperatureModel, AccessoryGaugeModel::OIL_TEMPERATURE_MODEL_NAME,
                    mContext);

        // voltmeter
        sensor = getCanSensor(Config::VOLTMETER_GAUGE_GROUP);
        QList<Sensor *> voltmeterSensors;
        if (sensor != nullptr) {
            voltmeterSensors.push_back(sensor);
        } else {
            voltmeterSensors.push_back(mVoltmeterSensor);
        }

        mVoltmeterGauge = new AccessoryGauge(
                    this->parent(), &mConfig, voltmeterSensors,
                    &mVoltMeterModel, AccessoryGaugeModel::VOLT_METER_MODEL_NAME,
                    mContext
                    );

        // fuel level (acc gauge)
        sensor = getCanSensor(Config::FUEL_GAUGE_GROUP);
        QList<Sensor *> fuelGaugeSensors;
        if (sensor != nullptr) {
            fuelGaugeSensors.push_back(sensor);
        } else {
            fuelGaugeSensors.push_back(mFuelLevelSensor);
        }

        mFuelLevelGauge = new AccessoryGauge(
                    this->parent(), &mConfig, fuelGaugeSensors,
                    &mFuelLevelModel, AccessoryGaugeModel::FUEL_LEVEL_MODEL_NAME,
                    mContext
                    );

        // oil pressure gauge
        sensor = getCanSensor(Config::OIL_PRESSURE_GAUGE_GROUP);
        QList<Sensor *> oilPressureSensors;
        if (sensor != nullptr) {
            oilPressureSensors.push_back(sensor);
        } else {
            oilPressureSensors.push_back(mOilPressureSensor);
        }

        mOilPressureGauge = new AccessoryGauge(
                    this->parent(), &mConfig, oilPressureSensors,
                    &mOilPressureModel, AccessoryGaugeModel::OIL_PRESSURE_MODEL_NAME,
                    mContext
                    );

        //temp and fuel cluster
        QList<Sensor *> tempAndFuelSensors = {coolantSensors.at(0), fuelGaugeSensors.at(0)};
        mTempFuelClusterGauge = new TempFuelClusterGauge(
                    this->parent(), &mConfig, tempAndFuelSensors,
                    &mTempFuelModel, TempAndFuelGaugeModel::TEMP_FUEL_CLUSTER_MODEL_NAME,
                    mContext
                    );
    }

    /**
     * @brief Initialize the speedometer
     */
    void initSpeedo() {
        qDebug() << "Speedometer Gauge Model Init";

        // init gauge
        QList<Sensor *> speedoSensors = {mSpeedoSensor};

        // Speedometer has a secondary output -- assign it now
        QString topSource = mConfig.getSpeedoConfig().topSource;
        if (topSource == Config::AMBIENT_TEMP_KEY) {
            speedoSensors.append(mAmbientTempSensor);
        } else if (topSource == Config::COOLANT_TEMP_KEY) {
            speedoSensors.append(mCoolantTempSensor);
        } else if (topSource == Config::OIL_TEMP_KEY) {
            speedoSensors.append(mOilTempSensor);
        } else if (topSource == Config::OIL_PRESSURE_KEY) {
            speedoSensors.append(mOilPressureSensor);
        } else if (topSource == Config::MAP_SENSOR_KEY) {
            speedoSensors.append(mMapSensor);
        } else if (topSource == Config::ANALOG_INPUT_12V_VOLTMETER) {
            speedoSensors.append(mVoltmeterSensor);
        } else if (topSource == Config::ANALOG_INPUT_12V_RHEOSTAT) {
            speedoSensors.append(mDimmerVoltageSensor);
        } else if (topSource == Config::FUEL_LEVEL_KEY) {
            speedoSensors.append(mFuelLevelSensor);
        } else {
            // default to ambient
            speedoSensors.append(mAmbientTempSensor);
        }

        mSpeedoGauge = new SpeedometerGauge(
                    this->parent(), &mConfig, speedoSensors,
                    &mSpeedoModel, SpeedometerModel::SPEEDO_MODEL_NAME,
                    mContext
                    );
    }

    /**
     * @brief Initialize the tachometer
     */
    void initTacho() {
        qDebug() << "Tachometer Gauge Model Init";
        QList<Sensor *> tachSensors;

        // check if we have a can sensor
        for (CanSensor * sensor : mCanSensors) {
            if (sensor->getGuage().toLower() == Config::TACHOMETER_GAUGE_GROUP) {
                tachSensors.push_back(sensor);
            }
        }

        // If no can source is available -- use the kernel module tach sensor
        if (tachSensors.isEmpty()) {
            tachSensors.push_back(mTachSensor);
        }

        // initialize
        mTachoGauge = new TachometerGauge(
                    this->parent(), &mConfig, tachSensors,
                    &mTachoModel, TachometerModel::TACH_MODEL_NAME,
                    mContext
                    );
    }



    void initOdometer() {
        QList<Sensor *> odoSensors = {mOdoSensor, mTripAOdoSensor, mTripBOdoSensor};
        mOdoGauge = new OdometerGauge(
                    this->parent(), &mConfig, odoSensors,
                    &mOdometerModel, OdometerModel::ODOMETER_MODEL_NAME,
                    mContext
                    );
    }

    /**
     * @brief Initialize the dash lights and indicators
     */
    void initDashLights() {
        // init models
        mDashLights = new DashLights(this->parent(), &mConfig);
        mDashLights->init();

        // Hook up key press events
        QObject::connect(mDashLights, &DashLights::userInputActive, [=] (uint8_t n) {
            QKeyEvent * event = nullptr;
            if (n <= 3) {
                event = new QKeyEvent(QKeyEvent::KeyPress, mConfig.geUserInputConfig().value(n, Qt::Key::Key_Left), Qt::NoModifier);
                emit keyPress(event);
            }
        });

        // hook up long press events -- this will need to be configurable at some point:
        QObject::connect(mDashLights, &DashLights::userInputLongPress, [=] (uint8_t n) {
            qDebug() << "Long press detected: " << n;
            switch(n) {
            case 0:
                break;
            case 1:
                mTripAOdoSensor->reset();
                break;
            case 2:
                mTripBOdoSensor->reset();
                break;
            case 3:
                break;
            default:
                break;
            }
        });

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

        // hook up dash light timing
        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
                    &QTimer::timeout,
                    mDashLights,
                    &DashLights::update
                    );
    }

    void initBackLightControl() {
        mBacklightControl = new BackLightControl(
                    this,
                    &mConfig,
                    mVoltmeterSensor,
                    mDimmerVoltageSensor);

        QObject::connect(
                    mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::SLOW_TIMER)),
                    &QTimer::timeout,
                    mBacklightControl,
                    &BackLightControl::updateBacklightPwm
                    );
    }
};

#endif // DASH_NEW_H
