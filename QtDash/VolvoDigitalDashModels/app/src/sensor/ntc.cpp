#include <ntc.h>

Ntc::Ntc(const SensorConfig::TempSensorConfig& config) : mConfig(config){
    calculateCoefficients(config.r1, config.t1,
                          config.r2, config.t2,
                          config.r3, config.t3,
                          config.units);
}

qreal Ntc::calculateTemp(qreal volts, Units::TemperatureUnits units) const {
    // calculate NTC resistance
    qreal rNtc = SensorUtils::getResistance(volts, mConfig.vSupply, mConfig.rBalance);

    // calculate temperature in kelvin
    qreal lnR = qLn(rNtc);
    qreal lnR3 = lnR * lnR * lnR;
    qreal tKelvinInv = mCoeff.A + (mCoeff.B * lnR) +  (mCoeff.C * lnR3);

    // convert to desired units
    qreal temp = SensorUtils::convertTemperature(
        1 / tKelvinInv,
        units,
        Units::TemperatureUnits::KELVIN);

    if (temp != temp) {
        return 0;
    } else {
        return temp;
    }
}

void Ntc::calculateCoefficients(qreal r1, qreal t1,
                                qreal r2, qreal t2,
                                qreal r3, qreal t3, Units::TemperatureUnits units) {
    qreal L1 = qLn(r1);
    qreal L2 = qLn(r2);
    qreal L3 = qLn(r3);
    qreal Y1 = 1 / SensorUtils::toKelvin(t1, units);
    qreal Y2 = 1 / SensorUtils::toKelvin(t2, units);
    qreal Y3 = 1 / SensorUtils::toKelvin(t3, units);
    qreal gamma2 = (Y2 - Y1) / (L2 - L1);
    qreal gamma3 = (Y3 - Y1) / (L3 - L1);
    mCoeff.C = (gamma3 - gamma2) / (L3 - L2) / (L1 + L2 + L3);
    mCoeff.B = gamma2 - mCoeff.C * (L1*L1 + L1*L2 + L2*L2);
    mCoeff.A = Y1 - (mCoeff.B + L1*L1*mCoeff.C) * L1;
}
