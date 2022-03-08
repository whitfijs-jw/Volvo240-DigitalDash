#ifndef ANALOG_12V_INPUT_H
#define ANALOG_12V_INPUT_H

#include <config.h>
#include <sensor_utils.h>

/**
 * @brief Analog12VInput class -- This is used for
 * the isolated 12V analog inputs that are measured
 * using a linearized optocoupler.  This is used to
 * measure battery voltage and can be used to measure
 * things like the dimmer rheostat output voltage
 */
class Analog12VInput {

public:
    /**
     * @brief Constructor
     * @param 12V Analog input config
     */
    Analog12VInput(Config::Analog12VInputConfig conf) : mConfig(conf) {
        // check if we need to fit data to determine k3
        if (mConfig.order == 1) {
            // we've been supplied with fit data, calculate K3 and offset based on inputs
            mConfig.coeff = SensorUtils::polynomialRegression(mConfig.x, mConfig.y, mConfig.order);
            mConfig.gainK3 = mConfig.coeff.at(1) / (mConfig.optoR2 / mConfig.optoR1) / (mConfig.inputR2 / (mConfig.inputR2 + mConfig.inputR1));
            mConfig.offset = mConfig.coeff.at(0);
            qDebug() << mConfig.type << " Calculated K3 gain: " << mConfig.gainK3;
            qDebug() << mConfig.type << " Calculated offset: " << mConfig.offset;
        }
    }

    /**
     * @brief Get current voltage
     * @param volts: voltage measured at ADC (0-Vref)
     * @return: measured voltage
     */
    qreal getVoltage(qreal volts) {
        // Vin = volts * (optoR1 / optoR2) * (1 / optoK3) * ( (inputR2 + inputR1) / inputR2 )
        return (volts - mConfig.offset) * (1 / mConfig.gainK3) *
                (mConfig.optoR1 / mConfig.optoR2) *
                ( (mConfig.inputR1 + mConfig.inputR2) / mConfig.inputR2 );
    }

private:
    Config::Analog12VInputConfig_t mConfig; //!< 12V input config
};

#endif // ANALOG_12V_INPUT_H
