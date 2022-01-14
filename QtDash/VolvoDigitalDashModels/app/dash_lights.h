#ifndef DASH_LIGHTS_H
#define DASH_LIGHTS_H

#include <QObject>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <config.h>
#include <QMap>
#include <mcp23017.h>

class DashLights: public QObject {
Q_OBJECT
public:
    DashLights(QObject * parent, QMap<QString, int> config) :
        QObject(parent), mConfig(config) {
    }

    void init() {
        /** Init blinkers */
        mLeftBlinkerModel.setOn(false);
        mRightBlinkerModel.setOn(false);

        /** Init Warning Lights **/
        mParkingBrakeLightModel.setText("PARKING\nBRAKE");
        mBrakeFailureLightModel.setText("BRAKE\nFAILURE");
        mBulbFailureLightModel.setText("");
        mShiftUpLightModel.setText("SHIFT\nUP");
        mHighBeamLightModel.setText("");
        mSrsWarningLightModel.setText("SRS");
        mOilWarningLightModel.setText("");
        mBatteryWarningLightModel.setText("");
        mAbsWarningLightModel.setText("ABS");
        mCheckEngineLightModel.setText("CHECK\nENGINE");
        mServiceLightModel.setText("SER-\nVICE");

        // populate maps
        mWarningLightModels.insert(PARKING_BRAKE_MODEL_NAME, &mParkingBrakeLightModel);
        mWarningLightModels.insert(BRAKE_FAILURE_MODEL_NAME, &mBrakeFailureLightModel);
        mWarningLightModels.insert(BULB_FAILURE_MODEL_NAME, &mBulbFailureLightModel);
        mWarningLightModels.insert(SHIFT_UP_MODEL_NAME, &mShiftUpLightModel);
        mWarningLightModels.insert(HIGH_BEAM_MODEL_NAME, &mHighBeamLightModel);
        mWarningLightModels.insert(SRS_WARNING_MODEL_NAME, &mSrsWarningLightModel);
        mWarningLightModels.insert(OIL_WARNING_MODEL_NAME, &mOilWarningLightModel);
        mWarningLightModels.insert(BATTERY_WARNING_MODEL_NAME, &mBatteryWarningLightModel);
        mWarningLightModels.insert(ABS_WARNING_MODEL_NAME, &mAbsWarningLightModel);
        mWarningLightModels.insert(CHECK_ENGINE_MODEL_NAME, &mCheckEngineLightModel);
        mWarningLightModels.insert(SERVICE_ENGINE_MODEL_NAME, &mServiceLightModel);

        mIndicatorModels.insert(LEFT_BLINKER_MODEL_NAME, &mLeftBlinkerModel);
        mIndicatorModels.insert(RIGHT_BLINKER_MODEL_NAME, &mRightBlinkerModel);
    }

    QMap<QString, WarningLightModel*> * getWarningLightModels() {
        return &mWarningLightModels;
    }

    QMap<QString, IndicatorModel*> * getIndicatorModels() {
        return &mIndicatorModels;
    }

signals:

public slots:
    void update() {
#ifdef RASPBERRY_PI
        mDashLightInputs.openDevice();
        uint8_t portA = mDashLightInputs.read(mcp23017::RegisterAddr::GPIOA);
        uint8_t portB = mDashLightInputs.read(mcp23017::RegisterAddr::GPIOB);
        mDashLightInputs.closeDevice();

        uint16_t inputs = (portB << 8) | portA;

        auto lightConf = mConfig;

        mLeftBlinkerModel.setOn(inputs & (1 << lightConf.value(Config::BLINKER_LEFT_KEY)));
        mRightBlinkerModel.setOn(inputs & (1 << lightConf.value(Config::BLINKER_RIGHT_KEY)));
        mHighBeamLightModel.setOn(inputs & (1 << lightConf.value(Config::HIGH_BEAM_KEY)));
        mParkingBrakeLightModel.setOn(inputs & (1 << lightConf.value(Config::PARKING_BRAKE_KEY)));
        mBrakeFailureLightModel.setOn(inputs & (1 << lightConf.value(Config::BRAKE_FAILURE_KEY)));
        mBulbFailureLightModel.setOn(inputs & (1 << lightConf.value(Config::BULB_FAILURE_KEY)));
        mSrsWarningLightModel.setOn(inputs & (1 << lightConf.value(Config::OD_LAMP_KEY)));
        mOilWarningLightModel.setOn(inputs & (1 << lightConf.value(Config::OIL_PRESSURE_KEY)));
        mBatteryWarningLightModel.setOn(inputs & (1 << lightConf.value(Config::CHARGING_LIGHT_KEY)));
        mAbsWarningLightModel.setOn(inputs & (1 << lightConf.value(Config::CONN_32_PIN3)));
        mCheckEngineLightModel.setOn(inputs & (1 << lightConf.value(Config::CHECK_ENGINE_KEY)));

        // not used at the moment?
        mShiftUpLightModel.setOn(0);
        mServiceLightModel.setOn(0);
#else
        mLeftBlinkerModel.setOn(true);
        mRightBlinkerModel.setOn(true);
        mHighBeamLightModel.setOn(true);
        mParkingBrakeLightModel.setOn(true);
        mBrakeFailureLightModel.setOn(true);
        mBulbFailureLightModel.setOn(true);
        mSrsWarningLightModel.setOn(true);
        mOilWarningLightModel.setOn(true);
        mBatteryWarningLightModel.setOn(true);
        mAbsWarningLightModel.setOn(true);
        mCheckEngineLightModel.setOn(true);
        mShiftUpLightModel.setOn(true);
        mServiceLightModel.setOn(true);
#endif
    }

private:
    static constexpr char LEFT_BLINKER_MODEL_NAME[] = "leftBlinkerModel";
    static constexpr char RIGHT_BLINKER_MODEL_NAME[] = "rightBlinkerModel";
    static constexpr char PARKING_BRAKE_MODEL_NAME[] = "parkingBrakeLightModel";
    static constexpr char BRAKE_FAILURE_MODEL_NAME[] = "brakeFailureLightModel";
    static constexpr char BULB_FAILURE_MODEL_NAME[] = "bulbFailureLightModel";
    static constexpr char SHIFT_UP_MODEL_NAME[] = "shiftUpLightModel";
    static constexpr char HIGH_BEAM_MODEL_NAME[] = "highBeamLightModel";
    static constexpr char SRS_WARNING_MODEL_NAME[] = "srsWarningLightModel";
    static constexpr char OIL_WARNING_MODEL_NAME[] = "oilWarningLightModel";
    static constexpr char BATTERY_WARNING_MODEL_NAME[] = "batteryWarningLightModel";
    static constexpr char ABS_WARNING_MODEL_NAME[] = "absWarningLightModel";
    static constexpr char CHECK_ENGINE_MODEL_NAME[] = "checkEngineLightModel";
    static constexpr char SERVICE_ENGINE_MODEL_NAME[] = "serviceLightModel";

    QMap<QString, int> mConfig;
    QMap<QString, WarningLightModel*> mWarningLightModels;
    QMap<QString, IndicatorModel*> mIndicatorModels;

    IndicatorModel mLeftBlinkerModel;
    IndicatorModel mRightBlinkerModel;
    WarningLightModel mParkingBrakeLightModel;
    WarningLightModel mBrakeFailureLightModel;
    WarningLightModel mBulbFailureLightModel;
    WarningLightModel mShiftUpLightModel;
    WarningLightModel mHighBeamLightModel;
    WarningLightModel mSrsWarningLightModel;
    WarningLightModel mOilWarningLightModel;
    WarningLightModel mBatteryWarningLightModel;
    WarningLightModel mAbsWarningLightModel;
    WarningLightModel mCheckEngineLightModel;
    WarningLightModel mServiceLightModel;

#ifdef RASPBERRY_PI
    mcp23017 mDashLightInputs;
#endif

};

#endif // DASH_LIGHTS_H
