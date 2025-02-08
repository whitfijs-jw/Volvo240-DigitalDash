#ifndef DASH_LIGHTS_H
#define DASH_LIGHTS_H

#include <QObject>
#include <indicator_model.h>
#include <warning_light_model.h>
#include <config.h>
#include <QMap>
#include <mcp23017.h>
#include <QElapsedTimer>
#include <memory>

/**
 * @brief Input handling for on/off dash light inputs
 */
class DashLights: public QObject {
Q_OBJECT
public:
/**
     * @brief Active input class
     */
    class ActiveInput {
    public:
        int activeInput = -1; //!< ACtive input pin
        bool active = false; //!< is the pin active
        bool longPressed = false; //!< is a long press active
        std::unique_ptr<QElapsedTimer> activeTimer; //!< timer to time active period
        int longPressDuration; //!< long press duration

        /**
         * @brief Active input constructor
         */
        ActiveInput() : activeTimer(new QElapsedTimer()) {
        }

        /**
         * @brief Activate the input timer
         * @param input current input pin
         */
        void activate(int input) {
            activeInput = input;
            active = true;
            activeTimer->restart();
        }

        /**
         * @brief Reset the active input timer
         */
        void reset() {
            activeInput = 0;
            active = false;
            longPressed = false;
        }
    };

    /**
     * @brief DashLights Constructor
     * @param parent
     * @param config
     */
    DashLights(QObject * parent, Config * config);

    /**
     * @brief Initialize blinkers and warning light models
     */
    void init();

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
    /**
     * @brief User input is now active
     * @param input active pin
     */
    void userInputActive(uint8_t input);

    /**
     * @brief User input long pressed
     * @param input long pressed pin
     */
    void userInputLongPress(uint8_t input);

public slots:
    /**
     * @brief update dash light states
     */
    void update();

    /**
     * @brief Read input pin value
     * @param pin pin number to read
     * @param inputs input value
     * @param activeLow true if inputs are active low
     * @return true is active
     */
    bool readPin(int pin, uint16_t inputs, bool activeLow) const;

private:
    static constexpr char LEFT_BLINKER_MODEL_NAME[] = "leftBlinkerModel"; //!< left blinker model name
    static constexpr char RIGHT_BLINKER_MODEL_NAME[] = "rightBlinkerModel"; //!< right blinker model name
    static constexpr char PARKING_BRAKE_MODEL_NAME[] = "parkingBrakeLightModel"; //!< parking brake model name
    static constexpr char BRAKE_FAILURE_MODEL_NAME[] = "brakeFailureLightModel"; //!< brake failure model name
    static constexpr char BULB_FAILURE_MODEL_NAME[] = "bulbFailureLightModel"; //!< bulb failure model name
    static constexpr char SHIFT_UP_MODEL_NAME[] = "shiftUpLightModel"; //!< shift light model name
    static constexpr char HIGH_BEAM_MODEL_NAME[] = "highBeamLightModel"; //!< high beam model name
    static constexpr char SRS_WARNING_MODEL_NAME[] = "srsWarningLightModel"; //!< SRS warning model name
    static constexpr char OIL_WARNING_MODEL_NAME[] = "oilWarningLightModel"; //!< Oil pressure wanring model name
    static constexpr char BATTERY_WARNING_MODEL_NAME[] = "batteryWarningLightModel"; //!< Battery warning model
    static constexpr char ABS_WARNING_MODEL_NAME[] = "absWarningLightModel"; //!< ABS warning model
    static constexpr char CHECK_ENGINE_MODEL_NAME[] = "checkEngineLightModel"; //!< Check engine model
    static constexpr char SERVICE_ENGINE_MODEL_NAME[] = "serviceLightModel"; //!< Service light model

    Config * mConfig; //!< Dash config
    QMap<QString, int> mLightsConfig; //!< Dash light config
    QMap<QString, WarningLightModel*> mWarningLightModels; //!< map of warning light model names (from qml) and c++/qobject model references
    QMap<QString, IndicatorModel*> mIndicatorModels; //!< map of indicator model names (from qml) and c++/qobject model references
    ActiveInput mActiveInput; //!< Current active input

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
    Mcp23017 mDashLightInputs; //!< dash light inputs
#endif

};

#endif // DASH_LIGHTS_H
