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
    /**
     * @brief Constructor
     * @param name: device name, must match an existing name in iio subsystem
     * @param path: iio device path to search defaults to "/sys/bus/iio/devices/"
     * @param vRef: reference voltage
     */
    Adc(std::string name = "mcp3208",
                std::string path = IIO_DEVICE_PATH,
                double vRef = 5.0) :
        mDeviceName(name), mVref(vRef) {
        // search in path for the given device.
        mPath = findDevicePath(path, name);

        if (mPath.empty()) {
            std::cout << "Device: " << name << " not found in iio subsystem" << std::endl;
            return;
        }

        // setup channel number and max values
        if (name == MCP3208) {
            mNumChannels = 8;
            mMaxVal = 4095;
        } else if (name == MCP3008) {
            mNumChannels = 8;
            mMaxVal = 1023;
        } else if (name == ADS1115){
            mNumChannels = 4;
            mMaxVal = 65535;
        } else {
            mNumChannels = 0;
        }

        // setup a map of all of the input channels
        for (int i = 0; i < mNumChannels; i++) {
            // we're looking for in_voltageX_raw files in the iio device directory
            std::string dataPath = CHANNEL_DATA_PATH;
            std::size_t p = dataPath.find("X");
            if (p != std::string::npos) {
                dataPath.replace(p, 1, std::to_string(i));
            }
            std::string fullPath = mPath + "/" + dataPath;

            //make sure it exists
            if (std::filesystem::exists(fullPath)) {
                // add this to the map
                mChannelMap.insert(std::pair<int, std::string>(i, fullPath));

                std::cout << "Channel data path: " << mChannelMap.at(i) << std::endl;
            }
        }
    }

    /**
     * @brief Read scaled ADC value
     * @param channel: adc channel to read
     * @return current measured voltage
     */
    double readValue(int channel) {
        return  ((double)readRawValue(channel) / (double)mMaxVal) * mVref;
    }

    double readValue(int channel, double vRef) {
        return  ((double)readRawValue(channel) / (double)mMaxVal) * vRef;
    }

    /**
     * @brief Read raw ADC value
     * @param channel: adc channel to read
     * @return:
     */
    int readRawValue(int channel) {
        if (mChannelMap.find(channel) != mChannelMap.end()) {
            std::ifstream ifs(mChannelMap.at(channel), std::ios::in);
            if (!ifs.is_open()) {
                std::cout << "Error opening channel data file" << std::endl;
                return -1.0;
            }

            std::string val;
            std::getline(ifs, val);
            ifs.close();

            //std::cout << "Read val: " << val << std::endl;

            return std::stoi(val);
        }

        return -1.0;
    }

    int getNumChannels() {
        return mNumChannels;
    }

    std::string getDeviceName() {
        return mDeviceName;
    }

private:

    static constexpr char IIO_DEVICE_PATH[] = "/sys/bus/iio/devices/";
    static constexpr char IIO_DEVICE_BASENAME[] = "iio:device";
    static constexpr char CHANNEL_DATA_PATH[] = "in_voltageX_raw";

    static constexpr char MCP3208[] = "mcp3208";
    static constexpr char ADS1115[] = "ads1115";
    static constexpr char MCP3008[] = "mcp3008";

    /* 5V inputs go through voltage divider for 3.3V ADC inputs -- not quite 100% */
    static constexpr double VOLTAGE_CONVERSION_CORRECTION_FACTOR = 3.3 / ((620.0 / (620.0 + 330.0)) * 5.0);

    /**
     * @brief Find the iio device given the expected name
     * @param path: path to search -- not a recursive search
     * @param name: name of the iio device
     * @return path to the device if found. empty string if not found
     */
    std::string findDevicePath(std::string& path, std::string name) {
        for (auto& device : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_directory(device.path())) {
                std::cout << device << std::endl;
                auto path = device.path();
                path /= "name";
                std::ifstream ifs(path.c_str(), std::ios::in);

                if (!ifs.is_open()) {
                    std::cout << "Error opening name" << std::endl;
                    return "";
                }
                std::string devName;
                std::getline(ifs, devName);
                ifs.close();

                if (devName == name) {
                    std::cout << "found device: " << devName << std::endl;
                    return device.path();
                }
            }
        }

        return "";
    }

    std::string mDeviceName; //!< Device name
    std::string mPath; //!< iio device path
    int mNumChannels = 0; //!< Number of channels that can be read
    double mVref = 0.0f; //!< voltage reference
    int mMaxVal = 0; //!< max adc value
    std::map<int, std::string> mChannelMap; //!< map of channels and their respective paths
};

#endif // ANALOG_INPUT_H
