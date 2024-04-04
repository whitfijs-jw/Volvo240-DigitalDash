#include <backlight_control.h>

BackLightControl::BackLightControl(QObject *parent,
                                   Config *config,
                                   VoltmeterSensor *voltmeter,
                                   VoltmeterSensor *dimmerVoltage) : QObject(parent),
    mBacklightConfig(config->getBackLightConfig()) {
    // connect voltmeter output to update slot
    QObject::connect(voltmeter, &Sensor::sensorDataReady,
                     this, &BackLightControl::batteryVoltageUpdate);

    // connect dimmer voltage to update slot
    QObject::connect(dimmerVoltage, &Sensor::sensorDataReady,
                     this, &BackLightControl::dimmerVoltageUpdate);

    // initialize pwm
    mPwm = new Pwm(
        Pwm::DEFAULT_PATH,
        Pwm::DEFAULT_DEVICE,
        Pwm::DEFAULT_PERIOD,
        mBacklightConfig.lightsOffDutyCycle,
        mBacklightConfig.activeLow
    );
}

void BackLightControl::updateBacklightPwm() {
    //qDebug() << "Dimmer: " << mCurrentDimmerVoltage << " Battery: " << mCurrentBatteryVoltage;
    //qDebug() << "Ratio: " << mCurrentDimmerVoltage / mCurrentBatteryVoltage;

    if (mCurrentDimmerVoltage > 5.0) {
        if (!mBacklightConfig.useDimmer) {
            mPwm->setDutyCycle(mBacklightConfig.lightsOnDutyCycle);
        } else {
            //dimmer has power -- parking lights or headlights are on
            qreal ratio = mCurrentDimmerVoltage / mCurrentBatteryVoltage;
            mPwm->setDutyCycle(dutyCycleFromDimmer(ratio));
        }
    } else {
        // dimmer doesn't have power -- default to daytime PWM value
        mPwm->setDutyCycle(mBacklightConfig.lightsOffDutyCycle);
    }
}

void BackLightControl::batteryVoltageUpdate(QVariant voltage)  {
    mCurrentBatteryVoltage = voltage.toReal();
}

void BackLightControl::dimmerVoltageUpdate(QVariant voltage) {
    mCurrentDimmerVoltage = voltage.toReal();
}

qreal BackLightControl::dutyCycleFromDimmer(qreal ratio){
    // scale ratio to min/max duty cycles
    return (ratio - mBacklightConfig.minDimmerRatio) /
               (mBacklightConfig.maxDimmerRatio - mBacklightConfig.minDimmerRatio) *
               (mBacklightConfig.maxDutyCycle - mBacklightConfig.minDutyCycle) + mBacklightConfig.minDutyCycle;
}
