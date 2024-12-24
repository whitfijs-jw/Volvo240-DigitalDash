#include <dash_lights.h>
#include <config_keys.h>

DashLights::DashLights(QObject *parent, Config *config) :
    QObject(parent), mConfig(config), mLightsConfig(config->getDashLightConfig()) {
    mActiveInput.longPressDuration =
        mConfig->getUserInputPinConfig().value(
            ConfigKeys::USER_INPUT_LONG_PRESS_DURATION, ConfigKeys::DEFAULT_LONG_PRESS_DURATION_MSEC);
}

void DashLights::init() {
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

void DashLights::update() {
#ifdef RASPBERRY_PI
    // load raw port values
    mDashLightInputs.openDevice();
    uint8_t portA = mDashLightInputs.read(Mcp23017::RegisterAddr::GPIOA);
    uint8_t portB = mDashLightInputs.read(Mcp23017::RegisterAddr::GPIOB);
    mDashLightInputs.closeDevice();

    // combine ports
    uint16_t inputs = (portB << 8) | portA;

    auto lightConf = mLightsConfig;
    bool activeLow = mLightsConfig.value(ConfigKeys::ACTIVE_LOW, true);

    // set em
    mLeftBlinkerModel.setOn(readPin(lightConf.value(ConfigKeys::BLINKER_LEFT_KEY), inputs, activeLow));
    mRightBlinkerModel.setOn(readPin(lightConf.value(ConfigKeys::BLINKER_RIGHT_KEY), inputs, activeLow));
    mHighBeamLightModel.setOn(readPin(lightConf.value(ConfigKeys::HIGH_BEAM_KEY), inputs, activeLow));
    mParkingBrakeLightModel.setOn(readPin(lightConf.value(ConfigKeys::PARKING_BRAKE_KEY), inputs, activeLow));
    mBrakeFailureLightModel.setOn(readPin(lightConf.value(ConfigKeys::BRAKE_FAILURE_KEY), inputs, activeLow));
    mBulbFailureLightModel.setOn(readPin(lightConf.value(ConfigKeys::BULB_FAILURE_KEY), inputs, activeLow));;
    mSrsWarningLightModel.setOn(readPin(lightConf.value(ConfigKeys::OD_LAMP_KEY), inputs, activeLow));
    mOilWarningLightModel.setOn(readPin(lightConf.value(ConfigKeys::OIL_PRESSURE_SW_KEY), inputs, activeLow));
    mBatteryWarningLightModel.setOn(readPin(lightConf.value(ConfigKeys::CHARGING_LIGHT_KEY), inputs, activeLow));
    mAbsWarningLightModel.setOn(readPin(lightConf.value(ConfigKeys::CONN_32_PIN3), inputs, activeLow));
    mCheckEngineLightModel.setOn(readPin(lightConf.value(ConfigKeys::CHECK_ENGINE_KEY), inputs, activeLow));

    // not used at the moment?
    mShiftUpLightModel.setOn(0);
    mServiceLightModel.setOn(0);

    // deal with user inputs here
    auto userInputPinConfig = mConfig->getUserInputPinConfig();
    auto userInputConfig = mConfig->geUserInputConfig();

    bool userInput1 = readPin(userInputPinConfig.value(ConfigKeys::USER_INPUT1, 12), inputs, activeLow);
    bool userInput2 = readPin(userInputPinConfig.value(ConfigKeys::USER_INPUT2, 13), inputs, activeLow);
    bool userInput3 = readPin(userInputPinConfig.value(ConfigKeys::USER_INPUT3, 14), inputs, activeLow);
    bool userInput4 = readPin(userInputPinConfig.value(ConfigKeys::USER_INPUT4, 15), inputs, activeLow);

    // check if any of the inputs are active
    bool active = (userInput1 || userInput2 || userInput3 || userInput4);

    if (active) {
        // only trigger an event if we haven't previously triggered an event
        if (!mActiveInput.active) {
            // First press -- send out initial active event
            int activeInput = -1;
            if (userInput1) {
                activeInput = 0;
            } else if (userInput2) {
                activeInput = 1;
            } else if (userInput3) {
                activeInput = 2;
            } else if (userInput4) {
                activeInput = 3;
            }
            emit userInputActive(activeInput);
            mActiveInput.activate(activeInput);
        } else {
            // check how long we've been pressed
            if ((mActiveInput.activeTimer->elapsed() >= mActiveInput.longPressDuration) && !mActiveInput.longPressed) {
                // we've been pressed for a while -- emit event and then make sure we don't trigger the event twice
                emit userInputLongPress(mActiveInput.activeInput);
                mActiveInput.longPressed = true;
            }
        }
    } else {
        mActiveInput.reset();
    }

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

bool DashLights::readPin(int pin, uint16_t inputs, bool activeLow) {
    bool val = inputs & (1 << pin);

    if (activeLow) {
        return !val;
    } else {
        return val;
    }
}
