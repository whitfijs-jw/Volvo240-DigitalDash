#ifndef PWM_H
#define PWM_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <cmath>

class Pwm {
public:
    Pwm(std::string path = DEFAULT_PATH,
        std::string dev = DEFAULT_DEVICE,
        int periodNsec = DEFAULT_PERIOD,
        float dutyCycle = 0.5) :
        mPath(path), mDev(dev), mPeriod(periodNsec), mDutyCycle(dutyCycle) {
        // make sure pwm0 is enabled
        writeAttribute("export", 0);

        //check that the device is there now
        if (std::filesystem::exists(mPath + dev + "/")) {
            std::cout << "pwm0 exported" << std::endl;
            // update path
            mPath += mDev + "/";

            // set up period (will configure duty cycle)
            std::cout << "pwm: setting period" << std::endl;
            setPeriod(mPeriod);

            // enable
            std::cout << "pwm: enabled" << std::endl;
            enable(true);
        }
    }

    int enable(bool enable) {
        return writeAttribute(ENABLE, enable);
    }

    int setFrequency(float frequency) {
        int nsecPeriod = (int) std::round(1.0 / frequency * 1.0e9);
        return setPeriod(nsecPeriod);
    }

    int setPeriod(int period) {
        // update period
        if (writeAttribute(PERIOD, period) == period) {
            mPeriod = period;

            //update duty cycle to reflect new period
            setDutyCycle(mDutyCycle);

            return period;
        }

        return -1;
    }

    int setDutyCycle(float dutyCycle) {
        if (dutyCycle > 1.0) {
            dutyCycle = 1.0;
        } else if (dutyCycle < 0) {
            dutyCycle = 0;
        }

        int dc = std::round((float) mPeriod * dutyCycle);

        if (dc == mDutyCycle) {
            std::cout << "duty cycle already set" << std::endl;
            return dc;
        }

        if (writeAttribute(DUTY_CYCLE, dc) == dc) {
            mDutyCycle = dc;

            return dc;
        }

        return -1;
    }

private:
    static constexpr char DEFAULT_PATH[] = "/sys/class/pwm/pwmchip0/";
    static constexpr char DEFAULT_DEVICE[] = "pwm0";
    static constexpr char ENABLE[] = "enable";
    static constexpr char DUTY_CYCLE[] = "duty_cycle";
    static constexpr char PERIOD[] = "period";
    static constexpr int DEFAULT_PERIOD = 33333; //!< 30kHz

    /**
     * @brief Write attribute in the tach input sysfs
     * @param attr: attribute to write
     * @param value: value to write
     * @return: returns value if written successfully
     */
    int writeAttribute(std::string attr, int value) {
        // read the nano second spacing variable
        std::string fullPath = mPath + attr;
        std::ofstream ofs(fullPath, std::ofstream::out);
        if (!ofs.is_open()) {
            std::cout << "Error opening " << attr << std::endl;
            return -1.0;
        }

        ofs << value;
        ofs.close();

        //std::cout << attr << " set to: " << value <<  std::endl;

        return value;
    }

    std::string mPath;
    std::string mDev;
    int mPeriod = DEFAULT_PERIOD;
    float mDutyCycle = 0.5;
};

#endif // PWM_H
