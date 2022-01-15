#ifndef NTC_H
#define NTC_H

#include <QtMath>
#include <QDebug>
#include <config.h>

class Ntc {
public:
    typedef struct SteinhartHartCoefficients {
        qreal A;
        qreal B;
        qreal C;
    } SteinhartHartCoefficients_t;

    Ntc(Config::TempSensorConfig_t config) {
        calculateCoefficients(config.r1, config.t1,
                        config.r2, config.t2,
                        config.r3, config.t3,
                        config.units);
        mConfig = config;
    }

    qreal calculateTemp(qreal volts, Config::TemperatureUnits units) {
        // calculate NTC resistance
        qreal rNtc = mConfig.rBalance / ((mConfig.vSupply / volts) - 1.0);

        // calculate temperature in kelvin
        qreal lnR = qLn(rNtc);
        qreal lnR3 = lnR * lnR * lnR;
        qreal tKelvinInv = mCoeff.A + (mCoeff.B * lnR) +  (mCoeff.C * lnR3);

        // convert to desired units
        return convert(1 / tKelvinInv, units, Config::TemperatureUnits::KELVIN);
    }

    SteinhartHartCoefficients_t getCoefficients() {
        return mCoeff;
    }

private:
    static constexpr qreal C_CONST = 9.0 / 5.0;
    static constexpr qreal T0_K = 273.15;
    static constexpr qreal T0_F = 32.0;

    /**
     * @brief Convert everything to kelvin
     * @param temp
     * @param units
     * @return
     */
    static constexpr qreal toKelvin(qreal temp, Config::TemperatureUnits units) {
        if (units == Config::TemperatureUnits::FAHRENHEIT) {
            return ((temp - T0_F) / C_CONST) + T0_K;
        } else if (units == Config::TemperatureUnits::CELSIUS) {
            return temp + T0_K;
        } else {
            return temp;
        }
    }

    static constexpr qreal toCelsius(qreal temp, Config::TemperatureUnits units) {
        return toKelvin(temp, units) - T0_K;
    }

    static constexpr qreal toFahrenheit(qreal temp, Config::TemperatureUnits units) {
        if (units == Config::TemperatureUnits::KELVIN) {
            return ((temp - T0_K) * C_CONST) + T0_F;
        } else if (units == Config::TemperatureUnits::CELSIUS) {
            return (temp * C_CONST) + T0_F;
        } else {
            return temp;
        }
    }

    static constexpr qreal convert(qreal temp,
                                   Config::TemperatureUnits to,
                                   Config::TemperatureUnits from) {
        if (to == from) {
            return temp;
        }

        if (to == Config::TemperatureUnits::FAHRENHEIT) {
            return toFahrenheit(temp, from);
        } else if (to == Config::TemperatureUnits::CELSIUS) {
            return toCelsius(temp, from);
        } else if (to == Config::TemperatureUnits::KELVIN) {
            return toKelvin(temp, from);
        }

        return 0;
    }

    void calculateCoefficients(qreal r1, qreal t1,
                         qreal r2, qreal t2,
                         qreal r3, qreal t3, Config::TemperatureUnits units) {
        qreal L1 = qLn(r1);
        qreal L2 = qLn(r2);
        qreal L3 = qLn(r3);
        qreal Y1 = 1 / toKelvin(t1, units);
        qreal Y2 = 1 / toKelvin(t2, units);
        qreal Y3 = 1 / toKelvin(t3, units);
        qreal gamma2 = (Y2 - Y1) / (L2 - L1);
        qreal gamma3 = (Y3 - Y1) / (L3 - L1);
        mCoeff.C = (gamma3 - gamma2) / (L3 - L2) / (L1 + L2 + L3);
        mCoeff.B = gamma2 - mCoeff.C * (L1*L1 + L1*L2 + L2*L2);
        mCoeff.A = Y1 - (mCoeff.B + L1*L1*mCoeff.C) * L1;
    }

    SteinhartHartCoefficients_t mCoeff;

    Config::TempSensorConfig_t mConfig;
};

#endif // NTC_H
