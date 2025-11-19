#ifndef SENSOR_GEAR_H
#define SENSOR_GEAR_H

#include <sensor.h>
#include <sensor_source_tach.h>
#include <sensor_source_vss.h>
#include <sensor_configs.h>

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
               VssSource * vssSource, int vssChannel);

    /**
     * @brief Get sensor units
     * @return units string
     */
    QString getUnits() const override {
        return "gear";
    }

    /**
     * @brief Estimate the current gear based on current RPM and current speed
     * @param rpm Current engine RPM
     * @param speed Current Speed
     * @param speedUnits Speed units (mph, kmh, m/s)
     * @return the estimated gear
     */
    int estimateGear(qreal rpm, qreal speed, Units::SpeedUnits speedUnits);

public slots:
    /**
     * @brief Transform incoming data for the gauge
     * @param data: data from source
     * @param channel: source channel
     */
    void transform(const QVariant& data, int channel) override;

    /**
     * @brief Transform incoming VSS data to estimate the current gear
     * @param data from VSS source
     * @param channel VSS source channel
     */
    void transformVssData(const QVariant& data, int channel);

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
