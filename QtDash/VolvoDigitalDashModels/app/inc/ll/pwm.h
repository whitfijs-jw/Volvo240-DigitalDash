#ifndef PWM_H
#define PWM_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <cmath>

/**
 * @brief Sysfs PWM class
 */
class Pwm {
public:
    static constexpr char DEFAULT_PATH[] = "/sys/class/pwm/pwmchip0/"; //!< default pwm path
    static constexpr char DEFAULT_DEVICE[] = "pwm0"; //!< default pwm device
    static constexpr char ENABLE[] = "enable"; //!< enable attribute
    static constexpr char DUTY_CYCLE[] = "duty_cycle"; //!< duty cycle attribute
    static constexpr char PERIOD[] = "period"; //!< period attribute
    static constexpr char POLARITY[] = "polarity"; //!< polarity attribute
    static constexpr int DEFAULT_PERIOD = 33333; //!< 30kHz period
    static constexpr char POLARITY_NORMAL[] = "normal"; //!< normal polarity attribute
    static constexpr char POLARITY_INVERSED[] = "inversed"; //!< inversed (active low) polarity attribute

    /**
     * @brief Constructor
     * @param path path to the sysfs device
     * @param dev device name (pwm0, pwm1, etc)
     * @param periodNsec period in nsec
     * @param dutyCycle duty cycle (0.0 to 1.0)
     * @param activeLow true to make the output active low
     */
    Pwm(const std::string& path = DEFAULT_PATH,
        const std::string& dev = DEFAULT_DEVICE,
        int periodNsec = DEFAULT_PERIOD,
        float dutyCycle = 0.5,
        bool activeLow = true);

    /**
     * @brief Enable/Disable PWM output
     * @param enable true to enable the output
     * @return >0 when successful
     */
    int enable(bool enable);

    /**
     * @brief Set PWM frequency
     * @param frequency frequency in Hz
     * @return >0 when successful
     */
    int setFrequency(float frequency);

    /**
     * @brief Set the PWM period
     * @param period desired period in nsec
     * @return >0 when successful
     */
    int setPeriod(int period);

    /**
     * @brief Set the PWM duty cycle
     * @param dutyCycle duty cycle (0.0 to 1.0)
     * @return >0 when successful
     */
    int setDutyCycle(float dutyCycle);

private:
    /**
     * @brief Write attribute in the PWM sysfs
     * @param attr: attribute to write
     * @param value: value to write
     * @return: returns value if written successfully
     */
    int writeAttribute(const std::string& attr, int value) const;

    /**
     * @brief Write attribute to the PWM sysfs
     * @param attr attribute to write
     * @param value string value to write to attribute
     * @return true when successful
     */
    bool writeAttribute(const std::string& attr, const std::string& value) const;

    std::string mPath; //!< sysfs device path
    std::string mDev; //!< PWM device path
    int mPeriod = DEFAULT_PERIOD; //!< current PWM period
    float mDutyCycle = 0.5; //!< current PWM duty cycle
    bool mIsActiveLow = true; //!< current active low status
};

#endif // PWM_H
