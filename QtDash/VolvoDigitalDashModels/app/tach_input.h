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

class TachInput {

public:
    TachInput(Config::TachInputConfig_t config,
              std::string path = DEFAULT_TACH_PULSE_PATH) :
        mConfig(config), mPath(path) {
    }

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

        int spacingNano = std::stoi(val);
        if (spacingNano != 0) {
            float pulsePerSecond = 1.0e9 / ((float)spacingNano);
            return pulsePerSecond * 60 / mConfig.pulsesPerRot;
        } else {
            return 0;
        }
    }

private:
    static constexpr char DEFAULT_TACH_PULSE_PATH[] = "/sys/class/volvo_dash/pulse_counter/";
    static constexpr char PULSE_COUNT_ATTR[] = "pulse_count";
    static constexpr char PULSE_SPACING_AVG[] = "pulse_spacing_avg";

    Config::TachInputConfig_t mConfig;
    std::string mPath;
};

#endif // TACH_INPUT_H
