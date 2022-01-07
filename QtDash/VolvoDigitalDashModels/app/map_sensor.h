#ifndef MAP_SENSOR_H
#define MAP_SENSOR_H

#include <QObject>
#include <config.h>

class MapSensor {

public:


    MapSensor(Config::MapSensorConfig_t config) {
        setVoltages(config.p0V, config.p5V, config.units);
    }

    MapSensor(qreal pressure0V, qreal pressure5V, Config::PressureUnits units) {
        setVoltages(pressure0V, pressure5V, units);
    }

    qreal getAbsolutePressure(qreal volts, Config::PressureUnits units) {
        // pressure in kPa
        qreal p = (volts * mSlope) + mOffset;

        return convert(p, units);
    }

private:
    static constexpr qreal PSI_PER_KPA = .145038;
    static constexpr qreal BAR_PER_KPA = .01;

    static constexpr qreal VDD = 5.0;
    static constexpr qreal VSS = 0.0;

    static constexpr qreal psiToKpa(qreal psi) {
        return psi / PSI_PER_KPA;
    }

    static constexpr qreal barToKpa(qreal bar) {
        return bar / BAR_PER_KPA;
    }

    static constexpr qreal calculateSlope(qreal p5V, qreal p0V) {
        return (p5V - p0V) / (VDD - VSS);
    }

    qreal mP0V = 0.0;
    qreal mP5V = 0.0;
    qreal mSlope = 0.0;
    qreal mOffset = 0.0;

    qreal convert(qreal pressure, Config::PressureUnits units) {
        if (units == Config::PressureUnits::PSI) {
            return pressure * PSI_PER_KPA;
        } else if (units == Config::PressureUnits::BAR) {
            return pressure * BAR_PER_KPA;
        } else {
            // kPA
            return pressure;
        }
    }

    void setVoltages(qreal pressure0V, qreal pressure5V, Config::PressureUnits units) {
        // keep everthing in kPA
        if (units == Config::PressureUnits::PSI) {
            mP0V = psiToKpa(pressure0V);
            mP5V = psiToKpa(pressure5V);
        } else if (units == Config::PressureUnits::BAR) {
            mP0V = barToKpa(pressure0V);
            mP5V = barToKpa(pressure5V);
        } else {
            mP0V = pressure0V;
            mP5V = pressure5V;
        }

        mSlope = calculateSlope(mP5V, mP0V);
        mOffset = mP0V;
    }

};

#endif // MAP_SENSOR_H
