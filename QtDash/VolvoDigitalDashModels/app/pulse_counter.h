#ifndef PULSE_COUNTER_H
#define PULSE_COUNTER_H

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
 * tracking tach and vss pulse time spacing
 */
class PulseCounter {

public:
    /**
     * @brief Constructor
     * @param path: path where the sysfs pulse_counter device is found
     */
    PulseCounter(std::string path) : mPath(path) {
    }

    /**
     * @brief Get the current pulse frequency
     * @return -1 if invalid 0 to max rpm if valid
     */
    int getFrequency() {
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
            return 1.0e9 / ((float)spacingNano);
        } else {
            return 0;
        }
    }

    /**
     * @brief Get the current pulse count since boot
     * @return current pulse count
     */
    int getPulseCount() {
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
     * @brief Set the maximum frequency for incoming pulses.
     * This is ideally a little higher than the max expected frequency.
     * Too high and noise will be accepted as a valid input
     * @param freq
     * @return: returns new value if written to sysfs.  returns -1 if failed
     */
    int setMaxFrequency(qreal freq) {
        int nsec = (int) std::round(1.0 / freq * 1.0e9);

        return writeAttribute(PULSE_SPACING_MIN, nsec);
    }

    /**
     * @brief Set number of pulses to average over
     * @param num: number of samples to average
     * @return: returns new value if written to sysfs.  returns -1 if failed
     */
    int setNumSamplesToAvg(int num) {
        return writeAttribute(PULSE_SPACING_AVG_NUM_SAMPLES, num);
    }

protected:

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

    std::string mPath; //!< path to sysfs tach input class
};

#endif // PULSE_COUNTER_H
