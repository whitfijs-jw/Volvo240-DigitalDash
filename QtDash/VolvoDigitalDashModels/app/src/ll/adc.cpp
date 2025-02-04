#include <adc.h>

Adc::Adc(const std::string& name, const std::string& path, double vRef, int referenceChannel):
    mDeviceName(name), mVref(vRef), mRefChannel(referenceChannel) {
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
        if (std::size_t p = dataPath.find("X"); p != std::string::npos) {
            dataPath.replace(p, 1, std::to_string(i));
        }
        std::string fullPath = mPath + "/" + dataPath;

        //make sure it exists
        if (std::filesystem::exists(fullPath)) {
            // add this to the map
            mChannelMap.try_emplace(i, fullPath);

            std::cout << "Channel data path: " << mChannelMap.at(i) << std::endl;
        }
    }

    if (mRefChannel > 0 && mRefChannel < mNumChannels) {
        mVref = readValue(mRefChannel, 3.3) / REFERENCE_VOLTAGE_DIVIDER;
        std::cout << "Reference Voltage measured:" << mVref << std::endl;
    }
}

void Adc::updateReference() {
    if (mRefChannel > 0 && mRefChannel < mNumChannels) {
        mVref = readValue(mRefChannel, 3.3) / REFERENCE_VOLTAGE_DIVIDER;
    }
}

double Adc::readValue(int channel, double vRef) {
    double volts = ((double)readRawValue(channel) / (double)mMaxVal);

    if (vRef < 0) {
        updateReference();
        return volts * VOLTAGE_CONVERSION_CORRECTION_FACTOR;
    } else {
        return volts * vRef;
    }
}

int Adc::readRawValue(int channel){
    if (mChannelMap.find(channel) != mChannelMap.end()) {
        std::ifstream ifs(mChannelMap.at(channel), std::ios::in);
        if (!ifs.is_open()) {
            std::cout << "Error opening channel data file" << std::endl;
            return -1.0;
        }

        std::string val;
        std::getline(ifs, val);
        ifs.close();

        return std::stoi(val);
    }

    return -1;
}

std::string Adc::findDevicePath(const std::string &path, std::string_view name) const {
    for (auto& device : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_directory(device.path())) {
            std::cout << device << std::endl;
            auto tempPath = device.path();
            tempPath /= "name";
            std::ifstream ifs(tempPath.c_str(), std::ios::in);

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

