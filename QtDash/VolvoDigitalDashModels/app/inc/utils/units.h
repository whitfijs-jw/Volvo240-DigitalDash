#ifndef UNITS_H
#define UNITS_H

#include <QString>

class Units {
public:
    // units for sensors
    static constexpr char UNITS_KPA[] = "kpa";
    static constexpr char UNITS_PSI[] = "psi";
    static constexpr char UNITS_BAR[] = "bar";
    static constexpr char UNITS_INHG[] = "inhg";
    static constexpr char UNITS_MMHG[] = "mmhg";
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
        INHG, //!< inches of mercury
        MMHG, //!< millimeters of mercury
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
    static PressureUnits getPressureUnits(QString units);

    /**
     * @brief Get temperature units from string
     * @param units: units string
     * @return @ref TemperatureUnits
     */
    static TemperatureUnits getTempUnits(QString units);

    /**
     * @brief Get distance units from string
     * @param units: Units string
     * @return @ref DistanceUnits
     */
    static DistanceUnits getDistanceUnits(QString units);

    /**
     * @brief Get speed units from string
     * @param units: units string
     * @return @ref SpeedUnits
     */
    static SpeedUnits getSpeedUnits(QString units);
};

#endif // UNITS_H
