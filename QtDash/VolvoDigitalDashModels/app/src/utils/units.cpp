#include <units.h>

Units::PressureUnits Units::getPressureUnits(QString units) {
    if (units.compare(UNITS_BAR, Qt::CaseInsensitive) == 0) {
        return PressureUnits::BAR;
    } else if (units.compare(UNITS_KPA, Qt::CaseInsensitive) == 0) {
        return PressureUnits::KPA;
    } else if (units.compare(UNITS_INHG, Qt::CaseInsensitive) == 0) {
        return PressureUnits::INHG;
    } else if (units.compare(UNITS_MMHG, Qt::CaseInsensitive) == 0) {
        return PressureUnits::MMHG;
    } else {
        //default to psi
        return PressureUnits::PSI;
    }
}

Units::TemperatureUnits Units::getTempUnits(QString units) {
    if (units.compare(UNITS_C, Qt::CaseInsensitive) == 0) {
        return TemperatureUnits::CELSIUS;
    } else if (units.compare(UNITS_K, Qt::CaseInsensitive) == 0) {
        return TemperatureUnits::KELVIN;
    } else {
        //default to f
        return TemperatureUnits::FAHRENHEIT;
    }
}

Units::DistanceUnits Units::getDistanceUnits(QString units) {
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

Units::SpeedUnits Units::getSpeedUnits(QString units) {
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
