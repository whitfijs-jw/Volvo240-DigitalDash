#ifndef DASH_LIGHTS_H
#define DASH_LIGHTS_H

#include <QObject>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <config.h>
#include <QMap>
#include <mcp23017.h>

/**
 * @brief The DashLights class
 */
class DashLights: public QObject {
Q_OBJECT
public:
    struct ActiveInput {
        int activeInput = -1;
        int count = 0;
        bool countEnabled = true;
        bool active = false;


        void reset() {
            activeInput = 0;
            count = 0;
            countEnabled = true;
            active = false;
        }

        void operator++() {
            if (countEnabled) {
                count++;
            }
        }
    };

    /**
     * @brief DashLights
     * @param parent
     * @param config
     */
    DashLights(QObject * parent, Config * config) :
        QObject(parent), mConfig(config), mLightsConfig(config->getDashLightConfig()) {
    }

    /**
     * @brief Initialize blinkers and warning light models
     */
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

    /**
     * @brief Get map of qml model names and references to c++ model
     * @return Map of warning light models
     */
    QMap<QString, WarningLightModel*> * getWarningLightModels() {
        return &mWarningLightModels;
    }

    /**
     * @brief Get map of qml model names and references to c++ model
     * @return Map of indicator models
     */
    QMap<QString, IndicatorModel*> * getIndicatorModels() {
        return &mIndicatorModels;
    }

signals:
    void userInputActive(uint8_t input);
    void userInputLongPress(uint8_t input);

public slots:
    /**
     * @brief update dash light states
     */
    void update() {
#ifdef RASPBERRY_PI
        // load raw port values
        mDashLightInputs.openDevice();
        uint8_t portA = mDashLightInputs.read(mcp23017::RegisterAddr::GPIOA);
        uint8_t portB = mDashLightInputs.read(mcp23017::RegisterAddr::GPIOB);
        mDashLightInputs.closeDevice();

        // combine ports
        uint16_t inputs = (portB << 8) | portA;

        auto lightConf = mLightsConfig;
        bool activeLow = mLightsConfig.value(Config::ACTIVE_LOW, true);

        // set em
        mLeftBlinkerModel.setOn(readPin(lightConf.value(Config::BLINKER_LEFT_KEY), inputs, activeLow));
        mRightBlinkerModel.setOn(readPin(lightConf.value(Config::BLINKER_RIGHT_KEY), inputs, activeLow));
        mHighBeamLightModel.setOn(readPin(lightConf.value(Config::HIGH_BEAM_KEY), inputs, activeLow));
        mParkingBrakeLightModel.setOn(readPin(lightConf.value(Config::PARKING_BRAKE_KEY), inputs, activeLow));
        mBrakeFailureLightModel.setOn(readPin(lightConf.value(Config::BRAKE_FAILURE_KEY), inputs, activeLow));
        mBulbFailureLightModel.setOn(readPin(lightConf.value(Config::BULB_FAILURE_KEY), inputs, activeLow));;
        mSrsWarningLightModel.setOn(readPin(lightConf.value(Config::OD_LAMP_KEY), inputs, activeLow));
        mOilWarningLightModel.setOn(readPin(lightConf.value(Config::OIL_PRESSURE_SW_KEY), inputs, activeLow));
        mBatteryWarningLightModel.setOn(readPin(lightConf.value(Config::CHARGING_LIGHT_KEY), inputs, activeLow));
        mAbsWarningLightModel.setOn(readPin(lightConf.value(Config::CONN_32_PIN3), inputs, activeLow));
        mCheckEngineLightModel.setOn(readPin(lightConf.value(Config::CHECK_ENGINE_KEY), inputs, activeLow));

        // not used at the moment?
        mShiftUpLightModel.setOn(0);
        mServiceLightModel.setOn(0);

        auto userInputPinConfig = mConfig->getUserInputPinConfig();
        auto userInputConfig = mConfig->geUserInputConfig();

        bool userInput1 = readPin(userInputPinConfig.value(Config::USER_INPUT1, 12), inputs, activeLow);
        bool userInput2 = readPin(userInputPinConfig.value(Config::USER_INPUT2, 13), inputs, activeLow);
        bool userInput3 = readPin(userInputPinConfig.value(Config::USER_INPUT3, 14), inputs, activeLow);
        bool userInput4 = readPin(userInputPinConfig.value(Config::USER_INPUT4, 15), inputs, activeLow);

        bool active = (userInput1 || userInput2 || userInput3 || userInput4);

        if (active) {
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
                mActiveInput.activeInput = activeInput;
            } else {
                // continued active event -- check if we've exceeded the long press threshold
                if ((userInput1 && mActiveInput.activeInput == 1) ||
                    (userInput2 && mActiveInput.activeInput == 2) ||
                    (userInput3 && mActiveInput.activeInput == 3) ||
                    (userInput4 && mActiveInput.activeInput == 4)) {
                    ++mActiveInput;
                }

                if (mActiveInput.count > 50) {
                    // we've been pressed for a while -- emit event and then disable counting
                    emit userInputLongPress(mActiveInput.activeInput);
                    mActiveInput.countEnabled = false;
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

    bool readPin(int pin, uint16_t inputs, bool activeLow) {
        bool val = inputs & (1 << pin);

        if (activeLow) {
            return !val;
        } else {
            return val;
        }
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

    Config * mConfig;
    QMap<QString, int> mLightsConfig; //!< Dash light config
    QMap<QString, WarningLightModel*> mWarningLightModels; //!< map of warning light model names (from qml) and c++/qobject model references
    QMap<QString, IndicatorModel*> mIndicatorModels; //!< map of indicator model names (from qml) and c++/qobject model references
    ActiveInput mActiveInput;

    IndicatorModel mLeftBlinkerModel; //!< left blinker model
    IndicatorModel mRightBlinkerModel; //!< right blinker model
    WarningLightModel mParkingBrakeLightModel; //!< parking brake light model
    WarningLightModel mBrakeFailureLightModel; //!< brake failure light model
    WarningLightModel mBulbFailureLightModel; //!< bulb failure light model
    WarningLightModel mShiftUpLightModel; //!< shift up light model
    WarningLightModel mHighBeamLightModel; //!< high beam light model
    WarningLightModel mSrsWarningLightModel; //!< srs warning light model
    WarningLightModel mOilWarningLightModel; //!< oil pressure warning light model
    WarningLightModel mBatteryWarningLightModel; //!< battery/charge light model
    WarningLightModel mAbsWarningLightModel; //!< abs light model
    WarningLightModel mCheckEngineLightModel; //!< check engine light model
    WarningLightModel mServiceLightModel; //!< service light model

#ifdef RASPBERRY_PI
    mcp23017 mDashLightInputs; //!< dash light inputs
#endif

};

#endif // DASH_LIGHTS_H
