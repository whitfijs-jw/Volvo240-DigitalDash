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

    void init() {
        mAdcSource = new AdcSource(this->parent(), &mConfig);
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

        QObject::connect(
                    mMapSensor, &Sensor::sensorDataReady,
                    [=](QVariant data) {
            mBoostModel.setCurrentValue(data.toReal());
        });

        mBoostModel.setMinValue(-20.0);
        mBoostModel.setMaxValue(30.0);
        mBoostModel.setUnits("psi");
        mBoostModel.setHighAlarm(18.0);
        mBoostModel.setLowAlarm(-50.0);

        mBoostModel.setCurrentValue(0.0);

        mContext->setContextProperty(BOOST_GAUGE_MODEL_NAME, &mBoostModel);
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

    AccessoryGaugeModel mBoostModel;
};

#endif // DASH_NEW_H
