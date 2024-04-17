#include <dash.h>


Dash::Dash(QObject *parent, QQmlContext *context) :
    QObject(parent), mContext(context), mEventTiming(parent), mConfig(parent) {
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
        mTripAOdoSensor->reset();
        break;
    case 1:
        mTripBOdoSensor->reset();
        break;
    default:
        break;
    }
}

void Dash::initSensorSources() {
    qDebug() << "Sensor Source Init";
    mAdcSource = new AdcSource(this->parent(), &mConfig);
    mGpsSource = new GpsSource(this->parent(), &mConfig);
    mTachSource = new TachSource(this->parent(), &mConfig);
    mVssSource = new VssSource(this->parent(), &mConfig);
    mCanSource = new CanSource(this->parent(), &mConfig);
}

void Dash::initCanSensors() {
    for (int channel : mCanSource->getChannelConfigs()->keys()) {
        qDebug() << "CAN Sensor Channel: " << channel;
        CanSensor * sensor = new CanSensor(this->parent(), &mConfig,
                                          mCanSource, channel);
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
        SensorConfig::TemperatureSensorType::COOLANT);

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
        SensorConfig::TemperatureSensorType::AMBIENT);

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
        SensorConfig::TemperatureSensorType::OIL);

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
            SensorConfig::OdometerConfig c = mConfig.getOdometerConfig(Config::ODO_NAME_ODOMETER);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_ODOMETER, c);
        });

    // trip counters
    SensorConfig::OdometerConfig confA = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPA);
    mTripAOdoSensor = new OdometerSensor (
        this->parent(), &mConfig, mVssSource,
        (int) VssSource::VssDataChannel::PULSE_COUNT, &confA);

    QObject::connect(
        mTripAOdoSensor, &OdometerSensor::writeOdoValue,
        [=](qreal value) {
            SensorConfig::OdometerConfig c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPA);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPA, c);
        });

    SensorConfig::OdometerConfig confB = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPB);
    mTripBOdoSensor = new OdometerSensor (
        this->parent(), &mConfig, mVssSource,
        (int) VssSource::VssDataChannel::PULSE_COUNT, &confB);

    QObject::connect(
        mTripBOdoSensor, &OdometerSensor::writeOdoValue,
        [=](qreal value) {
            SensorConfig::OdometerConfig c = mConfig.getOdometerConfig(Config::ODO_NAME_TRIPB);
            c.value = value;
            mConfig.writeOdometerConfig(Config::ODO_NAME_TRIPB, c);
        });

    mGearSensor = new GearSensor(
        this->parent(), &mConfig,
        mTachSource, (int) TachSource::TachDataChannel::RPM_CHANNEL,
        mVssSource, (int) VssSource::VssDataChannel::MPH
    );
}

void Dash::initAccessoryGauges() {
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

void Dash::initSpeedo() {
    qDebug() << "Speedometer Gauge Model Init";

    // init gauge -- default is VSS
    QList<Sensor *> speedoSensors = {mSpeedoSensor};
    if (mConfig.getVssConfig().useGps) {
        speedoSensors.replace(0, mGpsSpeedoSensor);
    }

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

    // append the gear indicator sensor
    speedoSensors.append(mGearSensor);

    mSpeedoGauge = new SpeedometerGauge(
        this->parent(), &mConfig, speedoSensors,
        &mSpeedoModel, SpeedometerModel::SPEEDO_MODEL_NAME,
        mContext
        );
}

void Dash::initTacho() {
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

void Dash::initOdometer() {
    QList<Sensor *> odoSensors = {mOdoSensor, mTripAOdoSensor, mTripBOdoSensor};
    mOdoGauge = new OdometerGauge(
        this->parent(), &mConfig, odoSensors,
        &mOdometerModel, OdometerModel::ODOMETER_MODEL_NAME,
        mContext
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

void Dash::initBackLightControl() {
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
