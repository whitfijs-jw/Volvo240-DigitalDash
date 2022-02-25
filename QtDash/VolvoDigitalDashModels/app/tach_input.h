#ifndef TACH_INPUT_H
#define TACH_INPUT_H

#include <config.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <cmath>
#include <pulse_counter.h>

/**
 * @brief Class to interface with the
 * pulse_counter module -- responsible for
 * tracking tach pulses and tach pulse
 * time spacing
 */
class TachInput : public PulseCounter {

public:
    /**
     * @brief Constructor
     * @param config: tach input config from Config class
     * @param path: path where the sysfs pulse_counter device is found
     */
    TachInput(Config::TachInputConfig_t config,
              std::string path = DEFAULT_TACH_PULSE_PATH) :
        PulseCounter(path), mConfig(config) {
        setMaxRpm(config.maxRpm);
        setNumSamplesToAvg(config.avgNumSamples);
    }

    /**
     * @brief Get the current rpm
     * @return -1 if invalid 0 to max rpm if valid
     */
    int getRpm() {
        return (int) std::round(getFrequency() * 60.0 / mConfig.pulsesPerRot);
    }

    /**
     * @brief Set the max rpm
     * @param rpm: RPM to be the new max
     * @return returns new max if written to sysfs.  returns -1 if failed
     */
    int setMaxRpm(int rpm) {
        //calculate min time in nsec
        int nsec = (int)std::round(1.0e9 * 60.0 / (rpm * mConfig.pulsesPerRot));

        return writeAttribute(PULSE_SPACING_MIN, nsec);

    }

private:
    static constexpr char DEFAULT_TACH_PULSE_PATH[] = "/sys/class/volvo_dash/tach_counter/"; //!< default pulse counter location

    Config::TachInputConfig_t mConfig; //!< Tach configuration
};

#endif // TACH_INPUT_H
