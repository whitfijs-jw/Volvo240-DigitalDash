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
    typedef struct SteinhartHartCoefficients {
        qreal A; //!< A
        qreal B; //!< B
        qreal C; //!< C
    } SteinhartHartCoefficients_t;

    /**
     * @brief Ntc constructor
     * @param config: sensor config
     */
    Ntc(Config::TempSensorConfig_t config) {
        calculateCoefficients(config.r1, config.t1,
                        config.r2, config.t2,
                        config.r3, config.t3,
                        config.units);
        mConfig = config;
    }

    /**
     * @brief Calculate temp from ADC voltage
     * @param volts: adc voltage
     * @param units: temperature units
     * @return calculate temperature in desired units
     */
    qreal calculateTemp(qreal volts, Config::TemperatureUnits units) {
        // calculate NTC resistance
        qreal rNtc = SensorUtils::getResistance(volts, mConfig.vSupply, mConfig.rBalance);

        // calculate temperature in kelvin
        qreal lnR = qLn(rNtc);
        qreal lnR3 = lnR * lnR * lnR;
        qreal tKelvinInv = mCoeff.A + (mCoeff.B * lnR) +  (mCoeff.C * lnR3);

        // convert to desired units
        qreal temp = SensorUtils::convertTemperature(
                    1 / tKelvinInv,
                    units,
                    Config::TemperatureUnits::KELVIN);

        if (temp != temp) {
            return 0;
        } else {
            return temp;
        }
    }

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
    Config::TempSensorConfig_t * getSensorConfig() {
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
                         qreal r3, qreal t3, Config::TemperatureUnits units) {
        qreal L1 = qLn(r1);
        qreal L2 = qLn(r2);
        qreal L3 = qLn(r3);
        qreal Y1 = 1 / SensorUtils::toKelvin(t1, units);
        qreal Y2 = 1 / SensorUtils::toKelvin(t2, units);
        qreal Y3 = 1 / SensorUtils::toKelvin(t3, units);
        qreal gamma2 = (Y2 - Y1) / (L2 - L1);
        qreal gamma3 = (Y3 - Y1) / (L3 - L1);
        mCoeff.C = (gamma3 - gamma2) / (L3 - L2) / (L1 + L2 + L3);
        mCoeff.B = gamma2 - mCoeff.C * (L1*L1 + L1*L2 + L2*L2);
        mCoeff.A = Y1 - (mCoeff.B + L1*L1*mCoeff.C) * L1;
    }

    SteinhartHartCoefficients_t mCoeff; //!< internal coefficients

    Config::TempSensorConfig_t mConfig; //!< sensor config
};

#endif // NTC_H
