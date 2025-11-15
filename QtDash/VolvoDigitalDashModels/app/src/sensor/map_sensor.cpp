#include <map_sensor.h>

MapSensor::MapSensor(const SensorConfig::MapSensorConfig& config, qreal vRef) {
    setVoltages(config.p0V, config.p5V, vRef, config.units);
}

MapSensor::MapSensor(qreal pressure0V, qreal pressure5V,
                     qreal vRef, Units::PressureUnits units) {
    setVoltages(pressure0V, pressure5V, vRef, units);
}

qreal MapSensor::getAbsolutePressure(qreal volts, Units::PressureUnits units) const {
    // pressure in kPa
    qreal p = (volts * mSlope) + mOffset;

    return SensorUtils::convertPressure(p, units, Units::PressureUnits::KPA);
}

void MapSensor::setVoltages(qreal pressure0V, qreal pressure5V,
                       qreal vRef, Units::PressureUnits units) {
    // keep everthing in kPA
    mP0V = SensorUtils::toKpa(pressure0V, units);
    mP5V = SensorUtils::toKpa(pressure5V, units);

    mSlope = calculateSlope(mP5V, mP0V, vRef);
    mOffset = mP0V;
    mVRef = vRef;
}
