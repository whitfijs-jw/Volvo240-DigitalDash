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
    static constexpr char PULSE_COUNT_ATTR[] = "pulse_count"; //!< total pulses detected attribute
    static constexpr char PULSE_SPACING_AVG[] = "pulse_spacing_avg"; //!< average pulse spacing attribute
    static constexpr char PULSE_SPACING_MIN[] = "pulse_spacing_min"; //!< minimum pulse spacing (in nsec)
    static constexpr char PULSE_SPACING_AVG_NUM_SAMPLES[] = "pulse_spacing_avg_num_samples"; //!< number of samples to average over

    /**
     * @brief Constructor
     * @param path: path where the sysfs pulse_counter device is found
     */
    explicit PulseCounter(const std::string& path) : mPath(path) {}

    /**
     * @brief Get the current pulse frequency
     * @return -1 if invalid 0 to max rpm if valid
     */
    int getFrequency() const;

    /**
     * @brief Get the current pulse count since boot
     * @return current pulse count
     */
    int getPulseCount() const;

    /**
     * @brief Set the maximum frequency for incoming pulses.
     * This is ideally a little higher than the max expected frequency.
     * Too high and noise will be accepted as a valid input
     * @param freq
     * @return: returns new value if written to sysfs.  returns -1 if failed
     */
    int setMaxFrequency(qreal freq) const;

    /**
     * @brief Set number of pulses to average over
     * @param num: number of samples to average
     * @return: returns new value if written to sysfs.  returns -1 if failed
     */
    int setNumSamplesToAvg(int num) const;

    /**
     * @brief Write attribute in the tach input sysfs
     * @param attr: attribute to write
     * @param value: value to write
     * @return: returns value if written successfully
     */
    int writeAttribute(const std::string& attr, int value) const;

private:

    std::string mPath; //!< path to sysfs tach input class
};

#endif // PULSE_COUNTER_H
