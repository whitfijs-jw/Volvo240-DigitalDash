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

/**
 * @brief Class to interface with the
 * pulse_counter module -- responsible for
 * tracking tach pulses and tach pulse
 * time spacing
 */
class TachInput {

public:
    /**
     * @brief Constructor
     * @param config: tach input config from Config class
     * @param path: path where the sysfs pulse_counter device is found
     */
    TachInput(Config::TachInputConfig_t config,
              std::string path = DEFAULT_TACH_PULSE_PATH) :
        mConfig(config), mPath(path) {
        setMaxRpm(config.maxRpm);
        setNumSamplesToAvg(config.avgNumSamples);
    }

    /**
     * @brief Get the current rpm
     * @return -1 if invalid 0 to max rpm if valid
     */
    int getRpm() {
        // read the nano second spacing variable
        std::string fullPath = mPath + PULSE_SPACING_AVG;
        std::ifstream ifs(fullPath, std::ios::in);
        if (!ifs.is_open()) {
            std::cout << "Error opening pulse spacing file" << std::endl;
            return -1.0;
        }

        std::string val;
        std::getline(ifs, val);
        ifs.close();

        int spacingNano = 0;
        try {
            spacingNano = std::stoi(val);
        } catch (std::invalid_argument& e) {
            std::cout << "tach input, invalid argument -- rpm will be 0" << std::endl;
        } catch (std::out_of_range& e) {
            std::cout << "tach input, out of range -- rpm will be 0" << std::endl;
        } catch (...) {
            std::cout << "tach input, other exception -- rpm will be 0" << std::endl;
        }

        if (spacingNano != 0) {
            float pulsePerSecond = 1.0e9 / ((float)spacingNano);
            return pulsePerSecond * 60 / mConfig.pulsesPerRot;
        } else {
            return 0;
        }
    }

    int getTachPulseCount() {
        std::string fullPath = mPath + PULSE_COUNT_ATTR;
        std::ifstream ifs(fullPath, std::ios::in);
        if (!ifs.is_open()) {
            std::cout << "Error opening pulse count file" << std::endl;
            return -1.0;
        }

        std::string val;
        std::getline(ifs, val);
        ifs.close();

        int count = 0;
        try {
            count = std::stoi(val);
        } catch (std::invalid_argument& e) {
            std::cout << "tach input, invalid argument -- count will be 0" << std::endl;
        } catch (std::out_of_range& e) {
            std::cout << "tach input, out of range -- count will be 0" << std::endl;
        } catch (...) {
            std::cout << "tach input, other exception -- count will be 0" << std::endl;
        }

        return count;
    }

    /**
     * @brief Set the max rpm
     * @param rpm: RPM to be the new max
     * @return returns new max if written to sysfs.  returns -1 if failed
     */
    int setMaxRpm(int rpm) {
        //calculate min time in nsec
        int nsec = (int)std::round(1.0e9 * 60.0 / (rpm * 2.0));

        return writeAttribute(PULSE_SPACING_MIN, nsec);

    }

    /**
     * @brief Set number of tach samples to average over
     * @param num: number of samples to average
     * @return: returns new value if written to sysfs.  returns -1 if failed
     */
    int setNumSamplesToAvg(int num) {
        return writeAttribute(PULSE_SPACING_AVG_NUM_SAMPLES, num);
    }

private:

    static constexpr char DEFAULT_TACH_PULSE_PATH[] = "/sys/class/volvo_dash/tach_counter/"; //!< default pulse counter location
    static constexpr char PULSE_COUNT_ATTR[] = "pulse_count"; //!< total pulses detected attribute
    static constexpr char PULSE_SPACING_AVG[] = "pulse_spacing_avg"; //!< average pulse spacing attribute
    static constexpr char PULSE_SPACING_MIN[] = "pulse_spacing_min"; //!< minimum pulse spacing (in nsec)
    static constexpr char PULSE_SPACING_AVG_NUM_SAMPLES[] = "pulse_spacing_avg_num_samples"; //!< number of samples to average over

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

        std::cout << attr << " set to: " << value <<  std::endl;

        return value;
    }

    Config::TachInputConfig_t mConfig; //!< Tach configuration
    std::string mPath; //!< path to sysfs tach input class
};

#endif // TACH_INPUT_H
