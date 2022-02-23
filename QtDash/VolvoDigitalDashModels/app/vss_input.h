#ifndef VSS_INPUT_H
#define VSS_INPUT_H

#include <config.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <cmath>
#include <sensor_utils.h>

class VssInput {
public:

    VssInput(Config::VssInputConfig_t config,
             std::string path = DEFAULT_VSS_PULSE_PATH):
        mConfig(config), mPath(path) {
        if (mConfig.pulsePerRot <= 0 && mConfig.tireDiameter > 0) {
            // we need to calculate from tire diameter
            qreal circumference = SensorUtils::toMiles(mConfig.tireDiameter, mConfig.tireDiameterUnits) * M_PI;

            mConfig.pulsePerUnitDistance = std::ceil(1 / circumference * mConfig.pulsePerRot);
            mConfig.distanceUnits = Config::DistanceUnits::MILE;
        }
    }

    qreal getMph() {
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
            std::cout << "vss input, invalid argument -- rpm will be 0" << std::endl;
        } catch (std::out_of_range& e) {
            std::cout << "vss input, out of range -- rpm will be 0" << std::endl;
        } catch (...) {
            std::cout << "vss input, other exception -- rpm will be 0" << std::endl;
        }

        if (spacingNano != 0) {
            float pulsePerSecond = 1.0e9 / ((float)spacingNano);
            qreal mph = pulsePerSecond * 1 / mConfig.pulsePerUnitDistance * 3600.0; // pulse/sec * miles/pulse * 3600 sec/hr
            return mph;
        } else {
            return 0;
        }
    }

    qreal getKph() {
        qreal mph = getMph();
        return SensorUtils::toMeters(mph, Config::DistanceUnits::MILE) / 1000.0;
    }




private:
    static constexpr char DEFAULT_VSS_PULSE_PATH[] = "/sys/class/volvo_dash/vss_counter/"; //!< default pulse counter location
    static constexpr char PULSE_COUNT_ATTR[] = "pulse_count"; //!< total pulses detected attribute
    static constexpr char PULSE_SPACING_AVG[] = "pulse_spacing_avg"; //!< average pulse spacing attribute
    static constexpr char PULSE_SPACING_MIN[] = "pulse_spacing_min"; //!< minimum pulse spacing (in nsec)
    static constexpr char PULSE_SPACING_AVG_NUM_SAMPLES[] = "pulse_spacing_avg_num_samples"; //!< number of samples to average over



    Config::VssInputConfig_t mConfig; //!< Tach configuration
    std::string mPath; //!< path to sysfs tach input class
};

#endif // VSS_INPUT_H
