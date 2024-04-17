#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>

/**
 * @brief The Adc -- relies on correct iio
 * adc driver to be loaded.  Searches in
 * /sys/bus/iio/devices/ path for devices
 * with the matching name.
 */
class Adc
{
public:
    static constexpr char IIO_DEVICE_PATH[] = "/sys/bus/iio/devices/"; //!< Default iio device path
    static constexpr char IIO_DEVICE_BASENAME[] = "iio:device"; //!< default iio device base name
    static constexpr char CHANNEL_DATA_PATH[] = "in_voltageX_raw"; //!< raw data channel X is replaced by the channel number

    static constexpr char MCP3208[] = "mcp3208"; //!< MCP3208
    static constexpr char ADS1115[] = "ads1115"; //!< ADS1115
    static constexpr char MCP3008[] = "mcp3008"; //!< MCP3008

    /* 5V inputs go through voltage divider for 3.3V ADC inputs -- not quite 100% */
    static constexpr double DEFAULT_VREF_VOLTAGE = 5.0;
    static constexpr double REFERENCE_VOLTAGE_DIVIDER = (15.0e3 / (15.0e3 + 8.2e3));
    static constexpr double INPUT_VOLTAGE_DIVIDER = (15.0e3 / (15.0e3 + 8.2e3));
    static constexpr double VOLTAGE_CONVERSION_CORRECTION_FACTOR = 3.3 / (INPUT_VOLTAGE_DIVIDER);

    /**
     * @brief Constructor
     * @param name: device name, must match an existing name in iio subsystem
     * @param path: iio device path to search defaults to "/sys/bus/iio/devices/"
     * @param vRef: reference voltage
     */
    Adc(std::string name = "mcp3208",
                std::string path = IIO_DEVICE_PATH,
                double vRef = DEFAULT_VREF_VOLTAGE,
                int referenceChannel = -1);

    /**
     * @brief Update internal reference with measurement using channel configured to measure
     * the voltage used to drive the sensor inputs
     */
    void updateReference();

    /**
     * @brief Read scaled ADC value
     * @param channel: adc channel to read
     * @return current measured voltage
     */
    double readValue(int channel, double vRef = -1);

    /**
     * @brief Read raw ADC value
     * @param channel: adc channel to read
     * @return:
     */
    int readRawValue(int channel);

    /**
     * @brief Get number of channels
     * @return number of channels
     */
    int getNumChannels() {
        return mNumChannels;
    }

    /**
     * @brief Get device name
     * @return Device name.  MCP3208, ADS1115, etc
     */
    std::string getDeviceName() {
        return mDeviceName;
    }

    double getVRef() {
        return mVref;
    }

private:

    /**
     * @brief Find the iio device given the expected name
     * @param path: path to search -- not a recursive search
     * @param name: name of the iio device
     * @return path to the device if found. empty string if not found
     */
    std::string findDevicePath(std::string& path, std::string name);

    std::string mDeviceName; //!< Device name
    std::string mPath; //!< iio device path
    int mNumChannels = 0; //!< Number of channels that can be read
    double mVref = 0.0f; //!< voltage reference
    int mMaxVal = 0; //!< max adc value
    std::map<int, std::string> mChannelMap; //!< map of channels and their respective paths
    int mRefChannel = -1;
};

#endif // ANALOG_INPUT_H
