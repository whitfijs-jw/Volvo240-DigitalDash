#ifndef ANALOG_12V_INPUT_H
#define ANALOG_12V_INPUT_H

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
     * @struct 12V analog input configuration
     */
    using Analog12VInputConfig = struct {
        QString type; //!< input type
        qreal optoR1; //!< opto R1 resistance
        qreal optoR2; //!< opto R2 resistance
        qreal inputR1; //!< input voltage divided R1
        qreal inputR2; //!< input voltage divider R2
        qreal gainK3; //!< opto transfer gain K3
        qreal offset;

        // polynomial fit (if the fit isn't perfectly linear)
        QList<qreal> x; //!< input voltage (battery voltage)
        QList<qreal> y; //!< measured voltage
        QList<qreal> coeff;
        int order;

        /**
         * @brief isValid
         * @return is config valid
         */
        bool isValid() {
            return true; //TODO: yea
        }
    };

    /**
     * @brief Constructor
     * @param conf: 12V Analog input config
     */
    Analog12VInput(const Analog12VInputConfig& conf);

    /**
     * @brief Get current voltage
     * @param volts: voltage measured at ADC (0-Vref)
     * @return: measured voltage
     */
    qreal getVoltage(qreal volts) const;
private:
    Analog12VInputConfig mConfig; //!< 12V input config
};

#endif // ANALOG_12V_INPUT_H
