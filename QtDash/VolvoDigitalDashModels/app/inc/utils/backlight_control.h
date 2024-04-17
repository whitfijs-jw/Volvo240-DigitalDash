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

    /**
     * @brief BackLightControl constructor
     * @param parent Parent Object
     * @param config Dash Config
     * @param voltmeter Battery voltage sensor input
     * @param dimmerVoltage Dimmer Rheostat Voltage
     */
    BackLightControl(QObject * parent,
                     Config * config,
                     VoltmeterSensor * voltmeter,
                     VoltmeterSensor * dimmerVoltage);

    virtual ~BackLightControl() {}

signals:

public slots:
    /**
     * @brief Update the backlight pwm
     */
    void updateBacklightPwm();

private slots:
    /**
     * @brief Update the battery voltage
     * @param voltage Voltage from ADC
     */
    void batteryVoltageUpdate(QVariant voltage);

    /**
     * @brief Update the dimmer (rheostat) voltage
     * @param voltage Voltage from ADC
     */
    void dimmerVoltageUpdate(QVariant voltage);

private:
    Config::BacklightControlConfig_t mBacklightConfig;
    qreal mCurrentBatteryVoltage = 0.0;
    qreal mCurrentDimmerVoltage = 0.0;
    Pwm * mPwm = nullptr;

    /**
     * @brief Get duty cycle from current dimmer voltage ratio
     * @param ratio Current dimmer to battery voltage ratio
     * @return PWM duty cycle
     */
    qreal dutyCycleFromDimmer(qreal ratio);
};

#endif // BACKLIGHT_CONTROL_H
