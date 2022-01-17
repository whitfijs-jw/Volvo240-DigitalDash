#ifndef SENSOR_UTILS_H
#define SENSOR_UTILS_H

#include <QObject>
#include <QtMath>

#include <config.h>
#include <../../eigen/Eigen/Dense>

class SensorUtils {
public:

    // temperature constant values
    static constexpr qreal C_CONST = 9.0 / 5.0;
    static constexpr qreal T0_K = 273.15;
    static constexpr qreal T0_F = 32.0;

    // pressure constants
    static constexpr qreal PSI_PER_KPA = .145038;
    static constexpr qreal BAR_PER_KPA = .01;

    static constexpr qreal getResistance(qreal volts, qreal vSupply, qreal rBalance) {
        qreal res = rBalance / ((vSupply / volts) - 1.0);

        //checks?

        return res;
    }

    static qreal estimateOptimalBalanceResistor(qreal rLow, qreal rHigh) {
        // checks?

        return qSqrt(rLow * rHigh);
    }

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

    static constexpr qreal interp(qreal x, qreal x0, qreal y0, qreal x1, qreal y1) {
        qreal diff = (x - x0) / (x1 - x0);
        return  (y0 * (1 - diff) + y1 * diff);
    }

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
