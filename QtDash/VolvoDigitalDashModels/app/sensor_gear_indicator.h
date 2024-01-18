#ifndef SENSOR_GEAR_H
#define SENSOR_GEAR_H

#include <sensor.h>
#include <sensor_source_tach.h>
#include <sensor_source_vss.h>

#include <random>

/**
 * @brief Tach Sensor
 */
class GearSensor : public Sensor {
public:
    /**
     * @brief TachSensor constructor
     * @param parent
     * @param config
     * @param source
     * @param channel
     */
    GearSensor(QObject * parent, Config * config,
               TachSource * source, int channel,
               VssSource * vssSource, int vssChannel) :
           Sensor(parent, config, source, channel) {
        // setup additional vss source
        mVssSource = vssSource;
        mVssChannel = vssChannel;

        // connect vss to transform
        QObject::connect(
                    mVssSource, &SensorSource::dataReady,
                    this, &GearSensor::transformVssData);

        // get a copy of the config
        mGearIndicatorConfig = config->getGearIndicatorConfig();

        // Calculate some stuff for gear estimation distributions
        for (int i = 0; i < mGearIndicatorConfig.gearRatios.size(); i++) {
            qreal ratio = mGearIndicatorConfig.gearRatios.at(i);
            qreal sigma = SIGMA_MIN;
            if (i + 1 < mGearIndicatorConfig.gearRatios.size()) {
                qreal ratioNext = mGearIndicatorConfig.gearRatios.at(i+1);
                sigma = qMin(ratio - ratioNext, SIGMA_MAX);
            }
            mDistSigma.push_back(sigma);
        }
    }


    QString getUnits() override {
        return "gear";
    }

    int estimateGear(qreal rpm, qreal speed, Config::SpeedUnits speedUnits) {
        // Get units to agree
        qreal diameterMile = SensorUtils::convertDistance(
                    mGearIndicatorConfig.tireDiameter,
                    Config::DistanceUnits::MILE,
                    mGearIndicatorConfig.tireDiameterUnits);

        qreal speedMph = SensorUtils::convertSpeed(
                    speed,
                    Config::SpeedUnits::MPH,
                    speedUnits
                    );

        // Estimate the gear ratio from the speed and rpm
        qreal ratioEst = ((rpm * 60.0) * (diameterMile * M_PI)) /
                          (speedMph * mGearIndicatorConfig.rearEndRatio);

        // first esimate of what gear we're in
        qreal ratioDiff = 100.0;
        qreal gearEst = -1.0;
        for (int i = 0; i < mGearIndicatorConfig.gearRatios.size(); i++) {
            qreal ratio = mGearIndicatorConfig.gearRatios.at(i);
            qreal diff = qAbs(ratio - ratioEst);
            if (diff < ratioDiff) {
                ratioDiff = diff;
                gearEst = i + 1;
            }
        }

        qreal gearEstDist = -1;
        qreal probMax = 0;
        for (int i = 0; i < mGearIndicatorConfig.gearRatios.size(); i++) {
            qreal sigma2 = mDistSigma.at(i) * mDistSigma.at(i);
            qreal ratio = mGearIndicatorConfig.gearRatios.at(i);
            qreal diff = ratioEst - ratio;
            qreal prob = qExp(-(diff * diff) / (2 * sigma2));
            if (prob > probMax) {
                probMax = prob;
                gearEstDist = i + 1;
            }
        }

        qDebug() << "Gear Estimate: " << gearEstDist << " | " << gearEst;

        return gearEstDist;
    }

public slots:
    /**
     * @brief Transform incoming data for the gauge
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            mCurrentRpm = data.toReal();
        }
    }

    void transformVssData(QVariant data, int channel) {
        if (channel == mVssChannel) {
            mCurrentSpeed = data.toReal();
        }
    }

private:
    static constexpr qreal SIGMA_MAX = 0.25;
    static constexpr qreal SIGMA_MIN = 0.1;

    VssSource * mVssSource;
    int mVssChannel;

    qreal mCurrentSpeed = 0.0;
    qreal mCurrentRpm = 0.0;

    Config::GearIndicatorConfig_t mGearIndicatorConfig;
    QList<qreal> mDistSigma;
};

#endif // SENSOR_GEAR_H
