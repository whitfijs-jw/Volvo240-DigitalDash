#include <pwm.h>

Pwm::Pwm(const std::string& path,
         const std::string& dev,
         int periodNsec, float dutyCycle,
         bool activeLow) :
    mPath(path), mDev(dev), mPeriod(periodNsec),
    mDutyCycle(dutyCycle), mIsActiveLow(activeLow) {
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

        // set polarity
        std::string polarity = mIsActiveLow ? POLARITY_INVERSED : POLARITY_NORMAL;
        writeAttribute(POLARITY, polarity);

        // enable
        std::cout << "pwm: enabled" << std::endl;
        enable(true);
    }
}


int Pwm::enable(bool enable){
    return writeAttribute(ENABLE, enable);
}

int Pwm::setFrequency(float frequency) {
    auto nsecPeriod = static_cast<int>(std::round(1.0 / frequency * 1.0e9));
    return setPeriod(nsecPeriod);
}

int Pwm::setPeriod(int period) {
    // update period
    if (writeAttribute(PERIOD, period) == period) {
        mPeriod = period;

        //update duty cycle to reflect new period
        setDutyCycle(mDutyCycle);

        return period;
    }

    return -1;
}

int Pwm::setDutyCycle(float dutyCycle) {
    if (dutyCycle > 1.0) {
        dutyCycle = 1.0;
    } else if (dutyCycle < 0) {
        dutyCycle = 0;
    }

    int dc = std::round((float) mPeriod * dutyCycle);

    if (dc == mDutyCycle) {
        return dc;
    }

    if (writeAttribute(DUTY_CYCLE, dc) == dc) {
        mDutyCycle = dc;

        return dc;
    }

    return -1;
}

int Pwm::writeAttribute(const std::string& attr, int value) const {
    // read the nano second spacing variable
    std::string fullPath = mPath + attr;
    std::ofstream ofs(fullPath, std::ofstream::out);
    if (!ofs.is_open()) {
        std::cout << "Error opening " << attr << std::endl;
        return -1;
    }

    ofs << value;
    ofs.close();

    return value;
}

bool Pwm::writeAttribute(const std::string& attr, const std::string& value) const {
    // read variable
    std::string fullPath = mPath + attr;
    std::ofstream ofs(fullPath, std::ofstream::out);
    if (!ofs.is_open()) {
        std::cout << "Error opening " << attr << std::endl;
        return false;
    }

    ofs << value;
    ofs.close();

    std::cout << "Set " << attr << " to: " << value << std::endl;

    return true;
}
