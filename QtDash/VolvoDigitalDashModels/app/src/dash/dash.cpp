#include <dash.h>
#include <utils.h>

Dash::Dash(QObject *parent, QQmlContext *context) :
    QObject(parent),
    mContext(context),
    mEventTiming(parent),
    mConfig(parent),
    mAdcSource(parent, &mConfig),
    mGpsSource(parent, &mConfig),
    mTachSource(parent, &mConfig),
    mVssSource(parent, &mConfig),
    mCanSource(parent, &mConfig),
    mMapSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::MAP_SENSOR_KEY)),
    mCoolantTempSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::COOLANT_TEMP_KEY), SensorConfig::TemperatureSensorType::COOLANT),
    mAmbientTempSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::AMBIENT_TEMP_KEY), SensorConfig::TemperatureSensorType::AMBIENT),
    mOilTempSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::OIL_TEMP_KEY), SensorConfig::TemperatureSensorType::OIL),
    mVoltmeterSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::FUSE8_12V_KEY), mConfig.getAnalog12VInputConfig(ConfigKeys::ANALOG_INPUT_12V_VOLTMETER)),
    mDimmerVoltageSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::DIMMER_VOLTAGE_KEY), mConfig.getAnalog12VInputConfig(ConfigKeys::ANALOG_INPUT_12V_RHEOSTAT)),
    mOilPressureSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::OIL_PRESSURE_KEY), mConfig.getResistiveSensorConfig(ConfigKeys::RES_SENSOR_TYPE_OIL_PRESSURE)),
    mFuelLevelSensor(parent, &mConfig, &mAdcSource, mConfig.getSensorConfig().value(ConfigKeys::FUEL_LEVEL_KEY), mConfig.getResistiveSensorConfig(ConfigKeys::RES_SENSOR_TYPE_FUEL_LEVEL)),
    mGpsSpeedoSensor(parent, &mConfig, &mGpsSource, DashUtils::to_underlying(GpsSource::GpsDataChannel::SPEED_MILES_PER_HOUR)),
    mSpeedoSensor(parent, &mConfig, &mVssSource, DashUtils::to_underlying(VssSource::VssDataChannel::MPH)),
    mTachSensor(parent, &mConfig, &mTachSource, DashUtils::to_underlying(TachSource::TachDataChannel::RPM_CHANNEL)),
    mOdoSensor(parent, &mConfig, &mVssSource, DashUtils::to_underlying(VssSource::VssDataChannel::PULSE_COUNT), mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER)),
    mTripAOdoSensor(parent, &mConfig, &mVssSource, DashUtils::to_underlying(VssSource::VssDataChannel::PULSE_COUNT), mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPA)),
    mTripBOdoSensor(parent, &mConfig, &mVssSource, DashUtils::to_underlying(VssSource::VssDataChannel::PULSE_COUNT), mConfig.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPB))
{
}

Dash::~Dash() {
    for (auto sensor : mCanSensors) {
        delete sensor;
    }
    mCanSensors.clear();
}

void Dash::init() {
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

void Dash::odoTripReset(int trip) {
    switch (trip) {
    case 0:
        mTripAOdoSensor.reset();
        break;
    case 1:
        mTripBOdoSensor.reset();
        break;
    default:
        break;
    }
}

void Dash::initSensorSources() {
    qDebug() << "Sensor Source Init";
}

void Dash::initCanSensors() {
    for (int channel : mCanSource.getChannelConfigs()->keys()) {
        qDebug() << "CAN Sensor Channel: " << channel;
        CanSensor * sensor = new CanSensor(this->parent(), &mConfig,
                                          &mCanSource, channel);
        qDebug() << "CAN Sensor: " << sensor->getGuage();
        mCanSensors.push_back(sensor);
    }
}

CanSensor * Dash::getCanSensor(QString gaugeName) {
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

void Dash::initSensors() {
    qDebug() << "Sensor Init";
    //map sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &mapSensor = mMapSensor]() {
            adcSource.update(mapSensor.getChannel());
        });

    // coolant temp sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &coolantTempSensor = mCoolantTempSensor]() {
            adcSource.update(coolantTempSensor.getChannel());
        });

    // ambient temp sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &ambientTempSensor = mAmbientTempSensor]() {
            adcSource.update(ambientTempSensor.getChannel());
        });

    // oil temp sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &oilTempSensor = mOilTempSensor]() {
            adcSource.update(oilTempSensor.getChannel());
        });

    // oil pressure sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::FAST_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &oilPressureSensor = mOilPressureSensor]() {
            adcSource.update(oilPressureSensor.getChannel());
        });

    //fuel level sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &fuelLevelSensor = mFuelLevelSensor]() {
            adcSource.update(fuelLevelSensor.getChannel());
        });


    // voltmeter
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &voltmeterSensor = mVoltmeterSensor]() {
            adcSource.update(voltmeterSensor.getChannel());
        });

    // rheostat/dimmer voltage
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::MEDIUM_TIMER)),
        &QTimer::timeout,
        [&adcSource = mAdcSource, &dimmerVoltageSensor = mDimmerVoltageSensor]() {
            adcSource.update(dimmerVoltageSensor.getChannel());
        });

    // speedometer
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::VERY_FAST_TIMER)),
        &QTimer::timeout,
        [&vssSource = mVssSource]() {
            vssSource.update(DashUtils::to_underlying(VssSource::VssDataChannel::MPH));
        });

    // tacho
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::VERY_FAST_TIMER)),
        &QTimer::timeout,
        [&tachSource = mTachSource]() {
            tachSource.update(DashUtils::to_underlying(TachSource::TachDataChannel::RPM_CHANNEL));
        });

    // odometer sensor
    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::SLOW_TIMER)),
        &QTimer::timeout,
        [&vssSource = mVssSource]() {
            vssSource.update(DashUtils::to_underlying(VssSource::VssDataChannel::PULSE_COUNT));
        });

    QObject::connect(
        &mOdoSensor, &OdometerSensor::writeOdoValue,
        [&config = mConfig](qreal value) {
            SensorConfig::OdometerConfig c = config.getOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER);
            c.value = value;
            config.writeOdometerConfig(ConfigKeys::ODO_NAME_ODOMETER, c);
        });

    // trip counters
    QObject::connect(
        &mTripAOdoSensor, &OdometerSensor::writeOdoValue,
        [&config = mConfig](qreal value) {
            SensorConfig::OdometerConfig c = config.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPA);
            c.value = value;
            config.writeOdometerConfig(ConfigKeys::ODO_NAME_TRIPA, c);
        });

    QObject::connect(
        &mTripBOdoSensor, &OdometerSensor::writeOdoValue,
        [&config = mConfig](qreal value) {
            SensorConfig::OdometerConfig c = config.getOdometerConfig(ConfigKeys::ODO_NAME_TRIPB);
            c.value = value;
            config.writeOdometerConfig(ConfigKeys::ODO_NAME_TRIPB, c);
        });
}

void Dash::initAccessoryGauges() {
    qDebug() << "Accessory Gauge Models Init";
    // boost gauge
    CanSensor * sensor = getCanSensor(ConfigKeys::BOOST_GAUGE_GROUP);

    QList<Sensor *> boostSensors;
    if (sensor != nullptr) {
        boostSensors.push_back(sensor);
    } else {
        boostSensors.push_back(&mMapSensor);
    }

    mBoostGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            boostSensors,
            &mBoostModel,
            AccessoryGaugeModel::BOOST_GAUGE_MODEL_NAME,
            mContext)
    );

    // coolant temp gauge
    sensor = getCanSensor(ConfigKeys::COOLANT_TEMP_GAUGE_GROUP);
    QList<Sensor *> coolantSensors;
    if (sensor != nullptr) {
        coolantSensors.push_back(sensor);
    } else {
        coolantSensors.push_back(&mCoolantTempSensor);
    }

    mCoolantTempGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            coolantSensors,
            &mCoolantTempModel,
            AccessoryGaugeModel::COOLANT_TEMP_MODEL_NAME,
            mContext)
    );

    // oil temp gauge
    sensor = getCanSensor(ConfigKeys::OIL_TEMPERATURE_GAUGE_GROUP);
    QList<Sensor *> oilTempSensors;
    if (sensor != nullptr) {
        oilTempSensors.push_back(sensor);
    } else {
        oilTempSensors.push_back(&mOilTempSensor);
    }

    mOilTempGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            oilTempSensors,
            &mOilTemperatureModel,
            AccessoryGaugeModel::OIL_TEMPERATURE_MODEL_NAME,
            mContext)
    );

    // voltmeter
    sensor = getCanSensor(ConfigKeys::VOLTMETER_GAUGE_GROUP);
    QList<Sensor *> voltmeterSensors;
    if (sensor != nullptr) {
        voltmeterSensors.push_back(sensor);
    } else {
        voltmeterSensors.push_back(&mVoltmeterSensor);
    }

    mVoltmeterGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            voltmeterSensors,
            &mVoltMeterModel,
            AccessoryGaugeModel::VOLT_METER_MODEL_NAME,
            mContext
        )
    );

    // fuel level (acc gauge)
    sensor = getCanSensor(ConfigKeys::FUEL_GAUGE_GROUP);
    QList<Sensor *> fuelGaugeSensors;
    if (sensor != nullptr) {
        fuelGaugeSensors.push_back(sensor);
    } else {
        fuelGaugeSensors.push_back(&mFuelLevelSensor);
    }

    mFuelLevelGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            fuelGaugeSensors,
            &mFuelLevelModel,
            AccessoryGaugeModel::FUEL_LEVEL_MODEL_NAME,
            mContext
        )
    );

    // oil pressure gauge
    sensor = getCanSensor(ConfigKeys::OIL_PRESSURE_GAUGE_GROUP);
    QList<Sensor *> oilPressureSensors;
    if (sensor != nullptr) {
        oilPressureSensors.push_back(sensor);
    } else {
        oilPressureSensors.push_back(&mOilPressureSensor);
    }

    mOilPressureGauge.reset(
        new AccessoryGauge(
            this->parent(),
            &mConfig,
            oilPressureSensors,
            &mOilPressureModel,
            AccessoryGaugeModel::OIL_PRESSURE_MODEL_NAME,
            mContext
        )
    );

    //temp and fuel cluster
    QList<Sensor *> tempAndFuelSensors = {coolantSensors.at(0), fuelGaugeSensors.at(0)};

    mTempFuelClusterGauge.reset(
        new TempFuelClusterGauge(
            this->parent(),
            &mConfig,
            tempAndFuelSensors,
            &mTempFuelModel,
            TempAndFuelGaugeModel::TEMP_FUEL_CLUSTER_MODEL_NAME,
            mContext
        )
    );
}

void Dash::initSpeedo() {
    qDebug() << "Speedometer Gauge Model Init";

    // init gauge -- default is VSS
    QList<Sensor *> speedoSensors = {&mSpeedoSensor};
    if (mConfig.getVssConfig().useGps) {
        speedoSensors.replace(0, &mGpsSpeedoSensor);
    }

    // Speedometer has a secondary output -- assign it now
    QString topSource = mConfig.getSpeedoConfig().topSource;
    if (topSource == ConfigKeys::AMBIENT_TEMP_KEY) {
        speedoSensors.append(&mAmbientTempSensor);
    } else if (topSource == ConfigKeys::COOLANT_TEMP_KEY) {
        speedoSensors.append(&mCoolantTempSensor);
    } else if (topSource == ConfigKeys::OIL_TEMP_KEY) {
        speedoSensors.append(&mOilTempSensor);
    } else if (topSource == ConfigKeys::OIL_PRESSURE_KEY) {
        speedoSensors.append(&mOilPressureSensor);
    } else if (topSource == ConfigKeys::MAP_SENSOR_KEY) {
        speedoSensors.append(&mMapSensor);
    } else if (topSource == ConfigKeys::ANALOG_INPUT_12V_VOLTMETER) {
        speedoSensors.append(&mVoltmeterSensor);
    } else if (topSource == ConfigKeys::ANALOG_INPUT_12V_RHEOSTAT) {
        speedoSensors.append(&mDimmerVoltageSensor);
    } else if (topSource == ConfigKeys::FUEL_LEVEL_KEY) {
        speedoSensors.append(&mFuelLevelSensor);
    } else {
        // default to ambient
        speedoSensors.append(&mAmbientTempSensor);
    }

    mSpeedoGauge.reset(
        new SpeedometerGauge(
            this->parent(),
            &mConfig,
            speedoSensors,
            &mSpeedoModel,
            SpeedometerModel::SPEEDO_MODEL_NAME,
            mContext
        )
    );
}

void Dash::initTacho() {
    qDebug() << "Tachometer Gauge Model Init";
    QList<Sensor *> tachSensors;

    // check if we have a can sensor
    for (CanSensor * sensor : mCanSensors) {
        if (sensor->getGuage().toLower() == ConfigKeys::TACHOMETER_GAUGE_GROUP) {
            tachSensors.push_back(sensor);
        }
    }

    // If no can source is available -- use the kernel module tach sensor
    if (tachSensors.isEmpty()) {
        tachSensors.push_back(&mTachSensor);
    }

    // initialize
    mTachoGauge.reset(
        new TachometerGauge(
            this->parent(),
            &mConfig,
            tachSensors,
            &mTachoModel,
            TachometerModel::TACH_MODEL_NAME,
            mContext
        )
    );
}

void Dash::initOdometer() {
    QList<Sensor *> odoSensors = {&mOdoSensor, &mTripAOdoSensor, &mTripBOdoSensor};

    mOdoGauge.reset(
        new OdometerGauge(
            this->parent(),
            &mConfig,
            odoSensors,
            &mOdometerModel,
            OdometerModel::ODOMETER_MODEL_NAME,
            mContext
        )
    );
}

void Dash::initDashLights() {
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
            mTripAOdoSensor.reset();
            break;
        case 2:
            mTripBOdoSensor.reset();
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

void Dash::initBackLightControl() {
    mBacklightControl.reset(
        new BackLightControl(
            this,
            &mConfig,
            &mVoltmeterSensor,
            &mDimmerVoltageSensor
        )
    );

    QObject::connect(
        mEventTiming.getTimer(static_cast<int>(EventTimers::DataTimers::SLOW_TIMER)),
        &QTimer::timeout,
        mBacklightControl.get(),
        &BackLightControl::updateBacklightPwm
        );
}
