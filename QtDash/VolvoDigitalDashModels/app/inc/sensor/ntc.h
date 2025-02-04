#ifndef NTC_H
#define NTC_H

#include <QtMath>
#include <QDebug>
#include <config.h>
#include <sensor_utils.h>

/**
 * @brief The Ntc class
 */
class Ntc {
public:
    /**
     * @struct SteinhartHartCoefficients Steinhart-Hart Coefficients
     */
    using SteinhartHartCoefficients_t = struct SteinhartHartCoefficients {
        qreal A; //!< A
        qreal B; //!< B
        qreal C; //!< C
    };

    /**
     * @brief Ntc constructor
     * @param config: sensor config
     */
    Ntc(const SensorConfig::TempSensorConfig& config);

    /**
     * @brief Calculate temp from ADC voltage
     * @param volts: adc voltage
     * @param units: temperature units
     * @return calculate temperature in desired units
     */
    qreal calculateTemp(qreal volts, Units::TemperatureUnits units) const;

    /**
     * @brief Get calibration curve coefficients
     * @return current coefficients
     */
    SteinhartHartCoefficients_t getCoefficients() {
        return mCoeff;
    }

    /**
     * @brief Get sensor config
     * @return Sensor config
     */
    SensorConfig::TempSensorConfig * getSensorConfig() {
        return &mConfig;
    }

private:
    /**
     * @brief Calculate Steinhart-Hart Coefficients
     * @param r1: resistance at point 1
     * @param t1: temperature at point 1
     * @param r2: resistance at point 2
     * @param t2: temperature at point 2
     * @param r3: resistance at point 3
     * @param t3: temperature at point 3
     * @param units: temperature units used
     */
    void calculateCoefficients(qreal r1, qreal t1,
                         qreal r2, qreal t2,
                        qreal r3, qreal t3, Units::TemperatureUnits units);

    SteinhartHartCoefficients_t mCoeff; //!< internal coefficients

    SensorConfig::TempSensorConfig mConfig; //!< sensor config
};

#endif // NTC_H
