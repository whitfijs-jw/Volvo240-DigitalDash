#ifndef SENSOR_UTILS_H
#define SENSOR_UTILS_H

#include <QObject>
#include <QtMath>

#include <config.h>
#include <../../eigen/Eigen/Dense>

/**
 * @brief The SensorUtils class
 */
class SensorUtils {
public:

    // temperature constant values
    static constexpr qreal C_CONST = 9.0 / 5.0; //!< Celcius to fahrenheit constant
    static constexpr qreal T0_K = 273.15; //!< 0C in kelvin
    static constexpr qreal T0_F = 32.0; //!< 0C in fahrenheit

    // pressure constants
    static constexpr qreal PSI_PER_KPA = .145038; //!< psi per kpa
    static constexpr qreal BAR_PER_KPA = .01; //!< bar per kpa

    // distance constants
    static constexpr qreal METER_PER_IN = .0254; //!< meters per in
    static constexpr qreal METER_PER_FOOT = .3048; //!< meters per foot
    static constexpr qreal METER_PER_YARD = .9144; //!< meters per yard
    static constexpr qreal METER_PER_MILE = 1609.34; //!< meters per mile

    static constexpr qreal IN_PER_MILE = 63360.0; //!< inches per mile
    static constexpr qreal FOOT_PER_MILE = 5280.0; //!< feet per mile
    static constexpr qreal YARD_PER_MILE = 1760.0; //!< yard per mile

    // Check for disconnected or shorted sensor
    static constexpr qreal SENSOR_MAX_PCT = .95; //!< above this percentage and an error is assumed

    /**
     * @brief Is sensor reading valid
     * @param volts: adc voltage
     * @param vSupply: supply voltage
     * @return: true if sensor output is valid
     */
    static constexpr bool isValid(qreal volts, qreal vSupply) {
        if (volts > vSupply * SENSOR_MAX_PCT || volts < vSupply * (1 - SENSOR_MAX_PCT)) {
            return false;
        }

        return true;
    }

    /**
     * @brief Get resistance from sensor output
     * @param volts: ADC voltage
     * @param vSupply: ADC supply
     * @param rBalance: balance resistor
     * @return sensor resistance value
     */
    static constexpr qreal getResistance(qreal volts, qreal vSupply, qreal rBalance) {
        qreal res = rBalance / ((vSupply / volts) - 1.0);

        //checks?

        return res;
    }

    /**
     * @brief Estimate optimal balance resistor (largest range)
     * @param rLow: lowest sensor resistance
     * @param rHigh: highest sensor resistance
     * @return balance resistor value
     */
    static qreal estimateOptimalBalanceResistor(qreal rLow, qreal rHigh) {
        // checks?

        return qSqrt(rLow * rHigh);
    }

    /**
     * @brief Convert distance to meters
     * @param distance: input distance
     * @param units: input units
     * @return distance in meters
     */
    static constexpr qreal toMeters(qreal distance, Config::DistanceUnits units) {
        if (units == Config::DistanceUnits::INCH) {
            return distance * METER_PER_IN;
        } else if (units == Config::DistanceUnits::FOOT) {
            return distance * METER_PER_FOOT;
        } else if (units == Config::DistanceUnits::YARD) {
            return distance * METER_PER_YARD;
        } else if (units == Config::DistanceUnits::MILE) {
            return distance * METER_PER_MILE;
        } else if (units == Config::DistanceUnits::MILLIMETER) {
            return distance / 1000.0;
        } else if (units == Config::DistanceUnits::CENTIMETER) {
            return distance / 100.0;
        } else if (units == Config::DistanceUnits::METER) {
            return distance;
        } else if (units == Config::DistanceUnits::KILOMETER) {
            return distance * 1000.0 ;
        } else {
            return -1;
        }
    }

    /**
     * @brief Convert distance to miles
     * @param distance: input distance
     * @param units: input units
     * @return distance in miles
     */
    static constexpr qreal toMiles(qreal distance, Config::DistanceUnits units) {
        if (units == Config::DistanceUnits::INCH) {
            return distance / IN_PER_MILE;
        } else if (units == Config::DistanceUnits::FOOT) {
            return distance / FOOT_PER_MILE;
        } else if (units == Config::DistanceUnits::YARD) {
            return distance / YARD_PER_MILE;
        } else if (units == Config::DistanceUnits::MILE) {
            return distance;
        } else if (units == Config::DistanceUnits::MILLIMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Config::DistanceUnits::CENTIMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Config::DistanceUnits::METER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Config::DistanceUnits::KILOMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else {
            return -1;
        }
    }

    /**
     * @brief Convert temperature to kelvin
     * @param temp: input temperature
     * @param units: input units
     * @return temperature in kelvin
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

    /**
     * @brief Convert temperature to celsius
     * @param temp: input temperature
     * @param units: input units
     * @return temperature in celsius
     */
    static constexpr qreal toCelsius(qreal temp, Config::TemperatureUnits units) {
        return toKelvin(temp, units) - T0_K;
    }

    /**
     * @brief Convert temperature to fahrenheit
     * @param temp: input temperature
     * @param units: input units
     * @return temperature in fahrenheit
     */
    static constexpr qreal toFahrenheit(qreal temp, Config::TemperatureUnits units) {
        if (units == Config::TemperatureUnits::KELVIN) {
            return ((temp - T0_K) * C_CONST) + T0_F;
        } else if (units == Config::TemperatureUnits::CELSIUS) {
            return (temp * C_CONST) + T0_F;
        } else {
            return temp;
        }
    }

    /**
     * @brief Convert temperature
     * @param temp: input temperature
     * @param to: units to convert to
     * @param from: units to convert from
     * @return temperature in "to" units
     */
    static constexpr qreal convertTemperature(qreal temp,
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

    /**
     * @brief Convert pressure to kPa
     * @param pressure: input pressure
     * @param units: input pressure units
     * @return pressure in kPa
     */
    static constexpr qreal toKpa(qreal pressure, Config::PressureUnits units) {
        if (units == Config::PressureUnits::PSI) {
            return pressure / PSI_PER_KPA;
        } else if (units == Config::PressureUnits::BAR) {
            return pressure / BAR_PER_KPA;
        } else {
            // kPA
            return pressure;
        }
    }

    /**
     * @brief Convert pressure to psi
     * @param pressure: input pressure
     * @param units: input pressure units
     * @return pressure in psi
     */
    static constexpr qreal toPsi(qreal pressure, Config::PressureUnits units) {
        if (units == Config::PressureUnits::PSI) {
            return pressure;
        } else if (units == Config::PressureUnits::BAR) {
            return (pressure / BAR_PER_KPA) * PSI_PER_KPA;
        } else {
            // kPA
            return pressure * PSI_PER_KPA;
        }
    }

    /**
     * @brief Convert pressure to bar
     * @param pressure: input pressure
     * @param units: input pressure units
     * @return pressure in bar
     */
    static constexpr qreal toBar(qreal pressure, Config::PressureUnits units) {
        if (units == Config::PressureUnits::PSI) {
            return (pressure / PSI_PER_KPA) * BAR_PER_KPA;
        } else if (units == Config::PressureUnits::BAR) {
            return pressure;
        } else {
            // kPA
            return pressure * BAR_PER_KPA;
        }
    }

    /**
     * @brief convert pressure
     * @param pressure: input pressure
     * @param to: units to convert to
     * @param from: units to convert from
     * @return pressure in desired units
     */
    static constexpr qreal convertPressure(
            qreal pressure, Config::PressureUnits to, Config::PressureUnits from) {
        switch (to) {
        case Config::PressureUnits::PSI:
            return toPsi(pressure, from);
            break;
        case Config::PressureUnits::BAR:
            return toBar(pressure, from);
            break;
        case Config::PressureUnits::KPA:
            return toKpa(pressure, from);
            break;
        default:
            return 0;
        }
    }

    /**
     * @brief interpolate
     * @param x: interpolation x value
     * @param x0: x0 value
     * @param y0: y0 value
     * @param x1: x1 value
     * @param y1: y1 value
     * @return y value interpolated at x
     */
    static constexpr qreal interp(qreal x, qreal x0, qreal y0, qreal x1, qreal y1) {
        qreal diff = (x - x0) / (x1 - x0);
        return  (y0 * (1 - diff) + y1 * diff);
    }

    /**
     * @brief Polynomial regression of input values
     * @param x: x values
     * @param y: y values
     * @param order: polynomial order
     * @return QList of polynomial coefficients of length (order + 1)
     */
    static QList<qreal> polynomialRegression(QList<qreal> x, QList<qreal> y, int order) {
        if (x.length() != y.length()) {
            // problem
        }

        Eigen::MatrixXd X(x.size(), order + 1);
        Eigen::MatrixXd Beta(x.size(), 1);
        Eigen::MatrixXd Y(y.size(), 1);

        // populate X and Y matrices
        for (int r = 0; r < x.size(); r++) {
            for (int c = 0; c <= order; c++) {
                X(r, c) = qPow(x.at(r), c);
            }

            Y(r) = y.at(r);
        }

        // intermediates
        Eigen::MatrixXd XtX = X.transpose() * X;
        Eigen::MatrixXd XtXinv = XtX.inverse();

        // do it
        Beta = XtXinv * X.transpose() * Y;

        // output coefficients (should be x^0 to x^order)
        QList<qreal> coeff;
        for (int i = 0; i < (order + 1); i++) {
            coeff.push_back(Beta(i));
        }

        return coeff;
    }

    /**
     * @brief calculate polynomial value given coefficients and x value
     * @param x: x value
     * @param coeff: polynomial coefficients
     * @return value of polynomial at x
     */
    static qreal polynomialValue(qreal x, QList<qreal> coeff) {
        qreal sum = 0;
        // sum terms
        for (int i = 0; i < coeff.size(); i++) {
            sum += qPow(x, i) * coeff.at(i);
        }

        return sum;
    }

};

#endif // SENSOR_UTILS_H
