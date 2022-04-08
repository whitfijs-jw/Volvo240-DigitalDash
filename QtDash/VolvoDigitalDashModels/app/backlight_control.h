#ifndef BACKLIGHT_CONTROL_H
#define BACKLIGHT_CONTROL_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

#include <sensor_voltmeter.h>
#include <pwm.hpp>
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
        mPwm = new Pwm();
    }
    virtual ~BackLightControl() {}

signals:

public slots:
    void updateBacklightPwm() {
        if (mCurrentDimmerVoltage > 5.0) {
            //Temp -- just set to fixed value
            mPwm->setDutyCycle(mBacklightConfig.lightsOnDutyCycle);

            //dimmer has power -- parking lights or headlights are on
            qreal ratio = mCurrentDimmerVoltage / mCurrentBatteryVoltage;
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
};

#endif // BACKLIGHT_CONTROL_H
