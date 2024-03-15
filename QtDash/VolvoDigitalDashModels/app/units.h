#ifndef UNITS_H
#define UNITS_H

class Units {
public:
    // units for sensors
    static constexpr char UNITS_KPA[] = "kpa";
    static constexpr char UNITS_PSI[] = "psi";
    static constexpr char UNITS_BAR[] = "bar";
    static constexpr char UNITS_F[] = "F";
    static constexpr char UNITS_C[] = "C";
    static constexpr char UNITS_K[] = "K";
    static constexpr char UNITS_PCT[] = "%";
    static constexpr char UNITS_INCH[] = "inch";
    static constexpr char UNITS_FOOT[] = "foot";
    static constexpr char UNITS_YARD[] = "yard";
    static constexpr char UNITS_MILE[] = "mile";
    static constexpr char UNITS_MILLIMETER[] = "millimeter";
    static constexpr char UNITS_CENTIMETER[] = "centimeter";
    static constexpr char UNITS_METER[] = "meter";
    static constexpr char UNITS_KILOMETER[] = "kilometer";
    static constexpr char UNITS_MPH[] = "mph";
    static constexpr char UNITS_KPH[] = "kph";
    static constexpr char UNITS_KMH[] = "km/h";
    static constexpr char UNITS_METERS_PER_SECOND[] = "m/s";

    /**
     * @brief The PressureUnits enum
     */
    using PressureUnits = enum class PressureUnits_t {
        KPA = 0, //!< Kilopascals
        PSI, //!< pounds per square inch
        BAR, //!< Bar
    };

    /**
     * @brief The TemperatureUnits enum
     */
    using TemperatureUnits = enum class TemperatureUnits_t {
        KELVIN = 0, //!< Kelvin
        CELSIUS, //!< Celsius
        FAHRENHEIT, //!< Fahrenheit
    };

    /**
     * @brief The DistanceUnits enum
     */
    using DistanceUnits = enum class DistanceUnits_t {
        INCH = 0, //!< inches
        FOOT,   //!< feet
        YARD,   //!< yards
        MILE, //!< miles
        MILLIMETER, //!< millimeters
        CENTIMETER, //!< centimeters
        METER, //!< meters
        KILOMETER, //!< kilometer
    };

    /**
     * @brief SpeedUnits enum
     */
    enum class SpeedUnits {
        MPH,
        KPH,
        METER_PER_SECOND,
    };


    /**
     * @brief Get pressure units from string
     * @param units: units string
     * @return @ref PressureUnits
     */
    static PressureUnits getPressureUnits(QString units) {
        if (units.compare(UNITS_BAR, Qt::CaseInsensitive) == 0) {
            return PressureUnits::BAR;
        } else if (units.compare(UNITS_KPA, Qt::CaseInsensitive) == 0) {
            return PressureUnits::KPA;
        } else {
            //default to psi
            return PressureUnits::PSI;
        }
    }

    /**
     * @brief Get temperature units from string
     * @param units: units string
     * @return @ref TemperatureUnits
     */
    static TemperatureUnits getTempUnits(QString units) {
        if (units.compare(UNITS_C, Qt::CaseInsensitive) == 0) {
            return TemperatureUnits::CELSIUS;
        } else if (units.compare(UNITS_K, Qt::CaseInsensitive) == 0) {
            return TemperatureUnits::KELVIN;
        } else {
            //default to f
            return TemperatureUnits::FAHRENHEIT;
        }
    }

    /**
     * @brief Get distance units from string
     * @param units: Units string
     * @return @ref DistanceUnits
     */
    static DistanceUnits getDistanceUnits(QString units) {
        if (units.compare(UNITS_INCH, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::INCH;
        } else if (units.compare(UNITS_FOOT, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::FOOT;
        } else if (units.compare(UNITS_YARD, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::YARD;
        } else if (units.compare(UNITS_MILE, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::MILE;
        } else if (units.compare(UNITS_MILLIMETER, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::MILLIMETER;
        } else if (units.compare(UNITS_CENTIMETER, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::CENTIMETER;
        } else if (units.compare(UNITS_METER, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::METER;
        } else if (units.compare(UNITS_KILOMETER, Qt::CaseInsensitive) == 0) {
            return DistanceUnits::KILOMETER;
        }

        // default to mm:
        return DistanceUnits::MILLIMETER;
    }

    /**
     * @brief Get speed units from string
     * @param units: units string
     * @return @ref SpeedUnits
     */
    static SpeedUnits getSpeedUnits(QString units) {
        if (units.compare(UNITS_MPH, Qt::CaseInsensitive) == 0) {
            return SpeedUnits::MPH;
        } else if ((units.compare(UNITS_KPH, Qt::CaseInsensitive) == 0) || (units.compare(UNITS_KMH, Qt::CaseInsensitive) == 0)) {
            return SpeedUnits::KPH;
        } else if (units.compare(UNITS_METERS_PER_SECOND, Qt::CaseInsensitive) == 0) {
            return SpeedUnits::METER_PER_SECOND;
        }

        //default to mph
        return SpeedUnits::MPH;
    }
};

#endif // UNITS_H
