#ifndef ANALOG_12V_INPUT_H
#define ANALOG_12V_INPUT_H

#include <config.h>

class Analog12VInput {

public:
    Analog12VInput(Config::Analog12VInputConfig conf) : mConfig(conf) {

    }

    qreal getVoltage(qreal volts) {
        // Vin = volts * (optoR1 / optoR2) * (1 / optoK3) * ( (inputR2 + inputR1) / inputR2 )

        return volts * (1 / mConfig.gainK3) *
                (mConfig.optoR1 / mConfig.optoR2) *
                ( (mConfig.inputR1 + mConfig.inputR2) / mConfig.inputR2 );
    }

private:
    Config::Analog12VInputConfig_t mConfig;
};

#endif // ANALOG_12V_INPUT_H
