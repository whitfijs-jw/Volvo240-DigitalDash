#include <analog_12v_input.h>

#include <QDebug>

Analog12VInput::Analog12VInput(Analog12VInput::Analog12VInputConfig conf) : mConfig(conf) {
    // check if we need to fit data to determine k3
    if (mConfig.order == 1) {
        // we've been supplied with fit data, calculate K3 and offset based on inputs
        mConfig.coeff = SensorUtils::polynomialRegression(mConfig.x, mConfig.y, mConfig.order);
        mConfig.gainK3 = mConfig.coeff.at(1) /
                         (mConfig.optoR2 / mConfig.optoR1) /
                         (mConfig.inputR2 / (mConfig.inputR2 + mConfig.inputR1));
        mConfig.offset = mConfig.coeff.at(0);
        qDebug() << mConfig.type << " Calculated K3 gain: " << mConfig.gainK3;
        qDebug() << mConfig.type << " Calculated offset: " << mConfig.offset;
    }
}

qreal Analog12VInput::getVoltage(qreal volts) {
    // Vin = volts * (optoR1 / optoR2) * (1 / optoK3) * ( (inputR2 + inputR1) / inputR2 )
    return (volts - mConfig.offset) * (1 / mConfig.gainK3) *
           (mConfig.optoR1 / mConfig.optoR2) *
           ( (mConfig.inputR1 + mConfig.inputR2) / mConfig.inputR2 );
}
