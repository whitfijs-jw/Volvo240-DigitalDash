#ifndef BACKLIGHT_CONTROL_H
#define BACKLIGHT_CONTROL_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

#include <sensor_voltmeter.h>
#include <pwm.h>
#include <config.h>


class BackLightControl : public QObject
{
    Q_OBJECT
public:
    static constexpr qreal DEFAULT_LIGHTS_OFF_DUTY_CYCLE = 0.6;
    static constexpr qreal DEFAULT_LIGHTS_ON_DUTY_CYCLE = 0.4;

    BackLightControl(QObject * parent,
                     Config * config,
                     VoltmeterSensor * voltmeter,
                     VoltmeterSensor * dimmerVoltage) : QObject(parent),
                    mConfig(config), mBacklightConfig(config->getBackLightConfig()) {
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
    virtual ~BackLightControl() {}

signals:

public slots:
    void updateBacklightPwm() {
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

private slots:
    void batteryVoltageUpdate(QVariant voltage) {
        mCurrentBatteryVoltage = voltage.toReal();
        //qDebug() << "Battery Voltage: " << mCurrentBatteryVoltage;
    }

    void dimmerVoltageUpdate(QVariant voltage) {
        mCurrentDimmerVoltage = voltage.toReal();
        //qDebug() << "Dimmer Voltage: " << mCurrentDimmerVoltage;
    }

private:
    Config * mConfig;
    Config::BacklightControlConfig_t mBacklightConfig;
    qreal mCurrentBatteryVoltage = 0.0;
    qreal mCurrentDimmerVoltage = 0.0;
    Pwm * mPwm;

    float dutyCycleFromDimmer(qreal ratio) {
        // scale ratio to min/max duty cycles
        return (ratio - mBacklightConfig.minDimmerRatio) /
                (mBacklightConfig.maxDimmerRatio - mBacklightConfig.minDimmerRatio) *
                (mBacklightConfig.maxDutyCycle - mBacklightConfig.minDutyCycle) + mBacklightConfig.minDutyCycle;
    }
};

#endif // BACKLIGHT_CONTROL_H
