#ifndef SENSOR_GEAR_H
#define SENSOR_GEAR_H

#include <sensor.h>
#include <sensor_source_tach.h>
#include <sensor_source_vss.h>
#include <sensor_configs.h>

#include <random>

/**
 * @brief Gear Indicator Sensor
 */
class GearSensor : public Sensor {
public:
    /**
     * @brief Gear sensor constructor
     * @param parent Parent QObject
     * @param config Dash Config
     * @param tachSource Tach Sensor Source
     * @param channel Tach source channel
     * @param vssSource VSS Sensor source
     * @param vssChannel VSS source channel
     */
    GearSensor(QObject * parent, Config * config,
               TachSource * tachSource, int channel,
               VssSource * vssSource, int vssChannel) :
           Sensor(parent, config, tachSource, channel) {
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

    /**
     * @brief Get sensor units
     * @return units string
     */
    QString getUnits() override {
        return "gear";
    }

    /**
     * @brief Estimate the current gear based on current RPM and current speed
     * @param rpm Current engine RPM
     * @param speed Current Speed
     * @param speedUnits Speed units (mph, kmh, m/s)
     * @return the estimated gear
     */
    int estimateGear(qreal rpm, qreal speed, Units::SpeedUnits speedUnits) {
        // Get units to agree
        qreal diameterMile = SensorUtils::convertDistance(
                    mGearIndicatorConfig.tireDiameter,
                    Units::DistanceUnits::MILE,
                    mGearIndicatorConfig.tireDiameterUnits);

        qreal speedMph = SensorUtils::convertSpeed(
                    speed,
                    Units::SpeedUnits::MPH,
                    speedUnits);

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

        // estimate based on pseudo-normal distributions
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

        if (gearEst != gearEstDist) {
            qDebug() << "Gear Estimate: " << gearEstDist << " | " << gearEst;
        }
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

    /**
     * @brief Transform incoming VSS data to estimate the current gear
     * @param data from VSS source
     * @param channel VSS source channel
     */
    void transformVssData(QVariant data, int channel) {
        if (channel == mVssChannel) {
            mCurrentSpeed = data.toReal();

            //estimte the current gear
            int gear = estimateGear(
                        mCurrentRpm,
                        mCurrentSpeed,
                        Units::getSpeedUnits(mVssSource->getUnits(channel))
                        );

            // check that we're in a good place to even use this estimate
            if (mCurrentSpeed > mGearIndicatorConfig.speedDropOut &&
                    mCurrentRpm > mGearIndicatorConfig.idleHighRpm) {
                emit sensorDataReady(gear);
            } else {
                // we can't make a good estimate of gear
                emit sensorDataReady(0);
            }
        }
    }

private:
    static constexpr qreal SIGMA_MAX = 0.25; //!< pseudo-normal distribution sigma max value
    static constexpr qreal SIGMA_MIN = 0.1; //!< pseudo-normal distribution sigma min value

    VssSource * mVssSource; //!< VSS Sensor source
    int mVssChannel; //!< VSS Source channel

    qreal mCurrentSpeed = 0.0; //!< current speed
    qreal mCurrentRpm = 0.0; //!< current RPM

    SensorConfig::GearIndicatorConfig_t mGearIndicatorConfig; //!< gear indicator config
    QList<qreal> mDistSigma; //!< pseudo-normal sigma value for each gear
};

#endif // SENSOR_GEAR_H
