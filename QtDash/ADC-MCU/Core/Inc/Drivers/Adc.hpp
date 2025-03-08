/*
 * Adc.hpp
 *
 *  Created on: Mar 7, 2025
 *      Author: whitfijs
 */

#ifndef INC_DRIVERS_ADC_HPP_
#define INC_DRIVERS_ADC_HPP_

#include <Tasks/Task.hpp>
#include <stm32u5xx_hal.h>

namespace Drivers {

class Adc : Tasks::Task {
public:
    static constexpr size_t DEFAULT_NUM_CHANNELS = 17;
    static constexpr uint32_t DEFAULT_SAMPLING_RATE = 250;

    explicit Adc(size_t numChannels = DEFAULT_NUM_CHANNELS, uint32_t sampleRate = DEFAULT_SAMPLING_RATE);

    Return setup() final;
    Return loop() final;

    Return setIntsance(Adc& instance) const {
        mInstance = &instance;
        return Return::OK;
    }

    static Adc* getInstance() {
        return mInstance;
    }

private:
    Return initGpios();
    Return initTimer(uint32_t samplingRate);
    Return initAdc(size_t numChannels);
    Return initAdcChannels();
    Return initDma();

    ADC_HandleTypeDef mAdcHandle = {};
    DMA_HandleTypeDef mAdcDmaHandle = {};

    size_t mNumChannels {DEFAULT_STACK_SIZE};
    uint32_t mSamplingRate {DEFAULT_SAMPLING_RATE};

    static Adc* mInstance = nullptr;
};

}


#endif /* INC_DRIVERS_ADC_HPP_ */
