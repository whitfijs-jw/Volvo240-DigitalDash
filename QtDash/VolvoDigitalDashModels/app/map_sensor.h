#ifndef MAP_SENSOR_H
#define MAP_SENSOR_H

#include <QObject>
#include <config.h>
#include <sensor_utils.h>

/**
 * @brief The MapSensor class
 */
class MapSensor {

public:
    /**
     * @brief MapSensor constructor
     * @param config: MAP sensor config
     */
    MapSensor(SensorConfig::MapSensorConfig config, qreal vRef) {
        setVoltages(config.p0V, config.p5V, vRef, config.units);
    }

    /**
     * @brief MapSensor constructor
     * @param pressure0V: pressure when MAP sensor is at 0V
     * @param pressure5V: pressure when MAP sensor it at 5V
     * @param units: pressure units
     */
    MapSensor(qreal pressure0V, qreal pressure5V, qreal vRef, Units::PressureUnits units) {
        setVoltages(pressure0V, pressure5V, vRef, units);
    }

    /**
     * @brief Get absolute pressure
     * @param volts: ADC voltage
     * @param units: pressure units
     * @return Pressure in desired units
     */
    qreal getAbsolutePressure(qreal volts, Units::PressureUnits units) {
        // pressure in kPa
        qreal p = (volts * mSlope) + mOffset;

        return SensorUtils::convertPressure(p, units, Units::PressureUnits::KPA);
    }

private:
    static constexpr qreal VDD = 5.0; //!< sensor VDD
    static constexpr qreal VSS = 0.0; //!< sensor VSS

    /**
     * @brief Calculate slope of sensor
     * @param p5V: pressure at 5V
     * @param p0V: pressure at 0V
     * @return
     */
    static constexpr qreal calculateSlope(qreal p5V, qreal p0V, qreal vRef) {
        return (p5V - p0V) / (vRef - VSS);
    }

    qreal mVRef = 5.0;
    qreal mP0V = 0.0;
    qreal mP5V = 0.0;
    qreal mSlope = 0.0;
    qreal mOffset = 0.0;

    /**
     * @brief Configure internal values
     * @param pressure0V: pressure at 0V
     * @param pressure5V: pressure at 5V
     * @param units: input units -- kPa is used internally
     */
    void setVoltages(qreal pressure0V, qreal pressure5V,
                     qreal vRef, Units::PressureUnits units) {
        // keep everthing in kPA
        mP0V = SensorUtils::toKpa(pressure0V, units);
        mP5V = SensorUtils::toKpa(pressure5V, units);

        mSlope = calculateSlope(mP5V, mP0V, vRef);
        mOffset = mP0V;
        mVRef = vRef;
    }

};

#endif // MAP_SENSOR_H
