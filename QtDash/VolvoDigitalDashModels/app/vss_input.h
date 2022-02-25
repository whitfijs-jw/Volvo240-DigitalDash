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
#include <pulse_counter.h>

class VssInput : public PulseCounter {
public:

    VssInput(Config::VssInputConfig_t config,
             std::string path = DEFAULT_VSS_PULSE_PATH) :
        PulseCounter(path), mConfig(config) {
        if (mConfig.pulsePerRot <= 0 && mConfig.tireDiameter > 0) {
            // we need to calculate from tire diameter
            qreal circumference = SensorUtils::toMiles(mConfig.tireDiameter, mConfig.tireDiameterUnits) * M_PI;

            mConfig.pulsePerUnitDistance = std::ceil(1 / circumference * mConfig.pulsePerRot);
            mConfig.distanceUnits = Config::DistanceUnits::MILE;
        }

        // adjust min pulse spacing
        qDebug() << "VSS Max Frequency" << mConfig.maxSpeed / 3600.0 * mConfig.pulsePerUnitDistance;
        setMaxFrequency(mConfig.maxSpeed / 3600.0 * mConfig.pulsePerUnitDistance);
    }

    qreal getMph() {
        qreal pulsesPerSecond = getFrequency();
        return pulsesPerSecond * (1.0 / mConfig.pulsePerUnitDistance) * 3600.0;
    }

    qreal getKph() {
        qreal mph = getMph();
        return SensorUtils::toMeters(mph, Config::DistanceUnits::MILE) / 1000.0;
    }


private:
    static constexpr char DEFAULT_VSS_PULSE_PATH[] = "/sys/class/volvo_dash/vss_counter/"; //!< default pulse counter location


    Config::VssInputConfig_t mConfig; //!< Tach configuration
};

#endif // VSS_INPUT_H
