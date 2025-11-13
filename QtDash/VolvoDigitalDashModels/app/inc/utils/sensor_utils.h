#ifndef SENSOR_UTILS_H
#define SENSOR_UTILS_H

#include <QObject>
#include <QtMath>
#include <units.h>

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
    static constexpr qreal INHG_PER_KPA = 0.2953;
    static constexpr qreal MMHG_PER_KPA = 7.50062;

    // distance constants
    static constexpr qreal METER_PER_IN = .0254; //!< meters per in
    static constexpr qreal METER_PER_FOOT = .3048; //!< meters per foot
    static constexpr qreal METER_PER_YARD = .9144; //!< meters per yard
    static constexpr qreal METER_PER_MILE = 1609.344; //!< meters per mile

    static constexpr qreal IN_PER_MILE = 63360.0; //!< inches per mile
    static constexpr qreal FOOT_PER_MILE = 5280.0; //!< feet per mile
    static constexpr qreal YARD_PER_MILE = 1760.0; //!< yard per mile

    static constexpr qreal IN_PER_FOOT = 12; //!< inches per foot
    static constexpr qreal FOOT_PER_YARD = 3.0; //!< feet per yard
    //speed constants
    static constexpr qreal MPH_TO_KPH = METER_PER_MILE / 1000.0; //!< mph to kph
    static constexpr qreal KPH_TO_METERS_PER_SEC = 1000.0 / 3600.0; //!< kph to m/s

    // Check for disconnected or shorted sensor
    static constexpr qreal SENSOR_MAX_PCT = .95; //!< above this percentage and an error is assumed

    static constexpr qreal INVALID_RESISTANCE = -1.0; //!< invalid resistance return value

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
        if (!isValid(volts, vSupply)) {
            return INVALID_RESISTANCE;
        }

        qreal res = rBalance / ((vSupply / volts) - 1.0);

        return res;
    }

    /**
     * @brief Estimate optimal balance resistor (largest range)
     * @param rLow: lowest sensor resistance
     * @param rHigh: highest sensor resistance
     * @return balance resistor value
     */
    static qreal estimateOptimalBalanceResistor(qreal rLow, qreal rHigh) {
        if (rLow <= 0 || rHigh <= 0) {
            return INVALID_RESISTANCE;
        }

        return qSqrt(rLow * rHigh);
    }

    /**
     * @brief Convert distance to meters
     * @param distance: input distance
     * @param units: input units
     * @return distance in meters
     */
    static constexpr qreal toMeters(qreal distance, Units::DistanceUnits units) {
        if (units == Units::DistanceUnits::INCH) {
            return distance * METER_PER_IN;
        } else if (units == Units::DistanceUnits::FOOT) {
            return distance * METER_PER_FOOT;
        } else if (units == Units::DistanceUnits::YARD) {
            return distance * METER_PER_YARD;
        } else if (units == Units::DistanceUnits::MILE) {
            return distance * METER_PER_MILE;
        } else if (units == Units::DistanceUnits::MILLIMETER) {
            return distance / 1000.0;
        } else if (units == Units::DistanceUnits::CENTIMETER) {
            return distance / 100.0;
        } else if (units == Units::DistanceUnits::METER) {
            return distance;
        } else if (units == Units::DistanceUnits::KILOMETER) {
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
    static constexpr qreal toMiles(qreal distance, Units::DistanceUnits units) {
        if (units == Units::DistanceUnits::INCH) {
            return distance / IN_PER_MILE;
        } else if (units == Units::DistanceUnits::FOOT) {
            return distance / FOOT_PER_MILE;
        } else if (units == Units::DistanceUnits::YARD) {
            return distance / YARD_PER_MILE;
        } else if (units == Units::DistanceUnits::MILE) {
            return distance;
        } else if (units == Units::DistanceUnits::MILLIMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Units::DistanceUnits::CENTIMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Units::DistanceUnits::METER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else if (units == Units::DistanceUnits::KILOMETER) {
            return toMeters(distance, units) / METER_PER_MILE;
        } else {
            return -1;
        }
    }

    /**
     * @brief Convert distance to feet
     * @param distance: input distance
     * @param units: input units
     * @return distance in feet
     */
    static constexpr qreal toFeet(qreal distance, Units::DistanceUnits units) {
        if (units == Units::DistanceUnits::INCH) {
            return distance / IN_PER_FOOT;
        } else if (units == Units::DistanceUnits::FOOT) {
            return distance;
        } else if (units == Units::DistanceUnits::YARD) {
            return distance * FOOT_PER_YARD;
        } else if (units == Units::DistanceUnits::MILE) {
            return distance * FOOT_PER_MILE;
        } else if (units == Units::DistanceUnits::MILLIMETER) {
            return toMeters(distance, units) / METER_PER_FOOT;
        } else if (units == Units::DistanceUnits::CENTIMETER) {
            return toMeters(distance, units) / METER_PER_FOOT;
        } else if (units == Units::DistanceUnits::METER) {
            return toMeters(distance, units) / METER_PER_FOOT;
        } else if (units == Units::DistanceUnits::KILOMETER) {
            return toMeters(distance, units) / METER_PER_FOOT;
        } else {
            return -1;
        }
    }

    /**
     * @brief Convert distance
     * @param distance: input distance value
     * @param to: units to convert input to
     * @param from units of input value
     * @return converted distance
     */
    static constexpr qreal convertDistance(
            qreal distance,
            Units::DistanceUnits to,
            Units::DistanceUnits from) {

        switch (to) {
        case Units::DistanceUnits::MILE:
            return toMiles(distance, from);
        case Units::DistanceUnits::KILOMETER:
            return toMeters(distance, from) / 1000.0;
        case Units::DistanceUnits::METER:
            return toMeters(distance, from);
        case Units::DistanceUnits::CENTIMETER:
            return toMeters(distance, from) * 100.0;
        case Units::DistanceUnits::MILLIMETER:
            return toMeters(distance, from) * 1000.0;
        case Units::DistanceUnits::INCH:
            return toFeet(distance, from) * IN_PER_FOOT;
        case Units::DistanceUnits::FOOT:
            return toFeet(distance, from);
        case Units::DistanceUnits::YARD:
            return toFeet(distance, from) / FOOT_PER_YARD;
        }

        return 0;
    }

    /**
     * @brief Convert temperature to kelvin
     * @param temp: input temperature
     * @param units: input units
     * @return temperature in kelvin
     */
    static constexpr qreal toKelvin(qreal temp, Units::TemperatureUnits units) {
        if (units == Units::TemperatureUnits::FAHRENHEIT) {
            return ((temp - T0_F) / C_CONST) + T0_K;
        } else if (units == Units::TemperatureUnits::CELSIUS) {
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
    static constexpr qreal toCelsius(qreal temp, Units::TemperatureUnits units) {
        return toKelvin(temp, units) - T0_K;
    }

    /**
     * @brief Convert temperature to fahrenheit
     * @param temp: input temperature
     * @param units: input units
     * @return temperature in fahrenheit
     */
    static constexpr qreal toFahrenheit(qreal temp, Units::TemperatureUnits units) {
        if (units == Units::TemperatureUnits::KELVIN) {
            return ((temp - T0_K) * C_CONST) + T0_F;
        } else if (units == Units::TemperatureUnits::CELSIUS) {
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
                                   Units::TemperatureUnits to,
                                   Units::TemperatureUnits from) {
        if (to == from) {
            return temp;
        }

        if (to == Units::TemperatureUnits::FAHRENHEIT) {
            return toFahrenheit(temp, from);
        } else if (to == Units::TemperatureUnits::CELSIUS) {
            return toCelsius(temp, from);
        } else if (to == Units::TemperatureUnits::KELVIN) {
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
    static constexpr qreal toKpa(qreal pressure, Units::PressureUnits units) {
        if (units == Units::PressureUnits::PSI) {
            return pressure / PSI_PER_KPA;
        } else if (units == Units::PressureUnits::BAR) {
            return pressure / BAR_PER_KPA;
        } else if (units == Units::PressureUnits::INHG) {
            return pressure / INHG_PER_KPA;
        } else if (units == Units::PressureUnits::MMHG) {
            return pressure / MMHG_PER_KPA;
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
    static constexpr qreal toPsi(qreal pressure, Units::PressureUnits units) {
        if (units == Units::PressureUnits::PSI) {
            return pressure;
        } else if (units == Units::PressureUnits::BAR) {
            return (pressure / BAR_PER_KPA) * PSI_PER_KPA;
        } else if (units == Units::PressureUnits::INHG) {
            return (pressure / INHG_PER_KPA) * PSI_PER_KPA;
        } else if (units == Units::PressureUnits::MMHG) {
            return (pressure / MMHG_PER_KPA) * PSI_PER_KPA;
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
    static constexpr qreal toBar(qreal pressure, Units::PressureUnits units) {
        if (units == Units::PressureUnits::PSI) {
            return (pressure / PSI_PER_KPA) * BAR_PER_KPA;
        } else if (units == Units::PressureUnits::BAR) {
            return pressure;
        } else if (units == Units::PressureUnits::INHG) {
            return (pressure / INHG_PER_KPA) * BAR_PER_KPA;
        } else if (units == Units::PressureUnits::MMHG) {
            return (pressure / MMHG_PER_KPA) * BAR_PER_KPA;
        } else {
            // kPA
            return pressure * BAR_PER_KPA;
        }
    }

    static constexpr qreal toInHg(qreal pressure, Units::PressureUnits units) {
        if (units == Units::PressureUnits::PSI) {
            return (pressure / PSI_PER_KPA) * INHG_PER_KPA;
        } else if (units == Units::PressureUnits::BAR) {
            return (pressure / BAR_PER_KPA) * INHG_PER_KPA;
        } else if (units == Units::PressureUnits::INHG) {
            return pressure;
        } else if (units == Units::PressureUnits::MMHG) {
            return (pressure / MMHG_PER_KPA) * INHG_PER_KPA;
        } else {
            // kPA
            return pressure * INHG_PER_KPA;
        }
    }

    static constexpr qreal toMmHg(qreal pressure, Units::PressureUnits units) {
        if (units == Units::PressureUnits::PSI) {
            return (pressure / PSI_PER_KPA) * MMHG_PER_KPA;
        } else if (units == Units::PressureUnits::BAR) {
            return (pressure / BAR_PER_KPA) * MMHG_PER_KPA;
        } else if (units == Units::PressureUnits::INHG) {
            return (pressure / INHG_PER_KPA) * MMHG_PER_KPA;
        } else if (units == Units::PressureUnits::MMHG) {
            return pressure;
        } else {
            // kPA
            return pressure * MMHG_PER_KPA;
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
            qreal pressure, Units::PressureUnits to,
            Units::PressureUnits from) {
        switch (to) {
        case Units::PressureUnits::PSI:
            return toPsi(pressure, from);
            break;
        case Units::PressureUnits::BAR:
            return toBar(pressure, from);
            break;
        case Units::PressureUnits::KPA:
            return toKpa(pressure, from);
            break;
        case Units::PressureUnits::INHG:
            return toInHg(pressure, from);
        case Units::PressureUnits::MMHG:
            return toMmHg(pressure, from);
        default:
            return 0;
        }
    }

    /**
     * @brief Convert speed to MPH
     * @param speed input speed
     * @param units units of input speed
     * @return converted speed
     */
    static constexpr qreal toMph(qreal speed, Units::SpeedUnits units) {
        if (units == Units::SpeedUnits::MPH) {
            return speed;
        } else if (units == Units::SpeedUnits::KPH) {
            return speed / MPH_TO_KPH;
        } else if (units == Units::SpeedUnits::METER_PER_SECOND) {
            return speed / MPH_TO_KPH / KPH_TO_METERS_PER_SEC;
        }

        return 0;
    }

    /**
     * @brief Convert speed to KPH
     * @param speed input speed
     * @param units input speed units
     * @return speed converted to MPH
     */
    static constexpr qreal toKph(qreal speed, Units::SpeedUnits units) {
        if (units == Units::SpeedUnits::MPH) {
            return speed * MPH_TO_KPH;
        } else if (units == Units::SpeedUnits::KPH) {
            return speed;
        } else if (units == Units::SpeedUnits::METER_PER_SECOND) {
            return speed / KPH_TO_METERS_PER_SEC;
        }

        return 0;
    }

    /**
     * @brief Convert speed to meters per second (m/s)
     * @param speed input speed
     * @param units input speed units
     * @return speed converted to m/s
     */
    static constexpr qreal toMetersPerSecond(qreal speed, Units::SpeedUnits units) {
        if (units == Units::SpeedUnits::MPH) {
            return speed * MPH_TO_KPH * KPH_TO_METERS_PER_SEC;
        } else if (units == Units::SpeedUnits::KPH) {
            return speed * KPH_TO_METERS_PER_SEC;
        } else if (units == Units::SpeedUnits::METER_PER_SECOND) {
            return speed;
        }

        return 0;
    }

    /**
     * @brief Convert speed to desired units
     * @param speed input speed
     * @param to units to convert to
     * @param from input speed units
     * @return converted speed
     */
    static constexpr qreal convertSpeed(qreal speed,
                                  Units::SpeedUnits to,
                                  Units::SpeedUnits from) {
        switch (to) {
        case Units::SpeedUnits::MPH:
            return toMph(speed, from);
        case Units::SpeedUnits::KPH:
            return toKph(speed, from);
        case Units::SpeedUnits::METER_PER_SECOND:
            return toMetersPerSecond(speed, from);
        }

        return 0.0;
    }

    /**
     * @brief Generic conversion
     * @param value input value
     * @param to units to convert to
     * @param from input value units
     * @return converted value
     */
    static qreal convert(qreal value, QString to, QString from);

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
    static QList<qreal> polynomialRegression(QList<qreal> x, QList<qreal> y, int order);

    /**
     * @brief calculate polynomial value given coefficients and x value
     * @param x: x value
     * @param coeff: polynomial coefficients
     * @return value of polynomial at x
     */
    static qreal polynomialValue(qreal x, QList<qreal> coeff);

};

#endif // SENSOR_UTILS_H
