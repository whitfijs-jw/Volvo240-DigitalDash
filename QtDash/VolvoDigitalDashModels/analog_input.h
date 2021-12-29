#ifndef ANALOG_INPUT_H
#define ANALOG_INPUT_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>

class AnalogInput
{
public:
    AnalogInput(std::string name = "mcp3208",
                std::string path = IIO_DEVICE_PATH,
                double vRef = 5.0) :
        mDeviceName(name), mVref(vRef) {
        mPath = findDevicePath(path, name);

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

        for (int i = 0; i < mNumChannels; i++) {
            std::string dataPath = CHANNEL_DATA_PATH;
            std::size_t p = dataPath.find("X");
            if (p != std::string::npos) {
                dataPath.replace(p, 1, std::to_string(i));
            }
            std::string fullPath = mPath + "/" + dataPath;
            mChannelMap.insert(std::pair<int, std::string>(i, fullPath));

            std::cout << "Channel data path: " << mChannelMap.at(i) << std::endl;
        }
    }

    bool setVoltageRef(double vref) {
        mVref = vref;
    }

    double readValue(int channel) {
        return  ((double)readRawValue(channel) / (double)mMaxVal) * mVref;
    }

    int readRawValue(int channel) {
        if (mChannelMap.find(channel) != mChannelMap.end()) {
            std::ifstream ifs(mChannelMap.at(channel), std::ios::in);
            if (!ifs.is_open()) {
                std::cout << "Error opening channel data file" << std::endl;
                return false;
            }

            std::string val;
            std::getline(ifs, val);
            ifs.close();

            //std::cout << "Read val: " << val << std::endl;

            return std::stoi(val);
        }

        return -1;
    }

private:

    static constexpr char IIO_DEVICE_PATH[] = "/sys/bus/iio/devices/";
    static constexpr char IIO_DEVICE_BASENAME[] = "iio:device";
    static constexpr char CHANNEL_DATA_PATH[] = "in_voltageX_raw";

    static constexpr char MCP3208[] = "mcp3208";
    static constexpr char ADS1115[] = "ads1115";
    static constexpr char MCP3008[] = "mcp3008";

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

    std::string mDeviceName;
    std::string mPath;
    int mNumChannels = 0;
    double mVref = 0.0f;
    int mMaxVal = 0;
    std::map<int, std::string> mChannelMap;
};

#endif // ANALOG_INPUT_H
