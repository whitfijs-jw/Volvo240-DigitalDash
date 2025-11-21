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

#include <array>

namespace Drivers {

class Adc : public Tasks::Task {
public:
    static constexpr size_t NUM_CHANNELS = 16;
    static constexpr uint32_t DEFAULT_SAMPLING_RATE = 250;

    static constexpr uint32_t SAMPLE_READY_FLAG = 1 << 0;

    explicit Adc(uint32_t sampleRate = DEFAULT_SAMPLING_RATE);
    ~Adc() final = default;
    Adc& operator=(const Adc& src) = delete;
    Adc(const Adc& src) = delete;
    Adc& operator=(const Adc&& src) = delete;
    Adc(Task& src) = delete;

    Return setup() final;
    void loop() final;

    Return enableSampling(std::array<uint32_t, NUM_CHANNELS>& data);
    Return disableSampling();

    Return setIntsance(Adc& instance) const {
        mInstance = &instance;
        return Return::OK;
    }

    static Adc* getInstance() {
        return mInstance;
    }

    ADC_HandleTypeDef* getAdcHandle() {
    	return &mAdcHandle;
    }

    DMA_HandleTypeDef* getDmaHandle() {
    	return &mAdcDmaHandle;
    }

    osStatus_t waitForSample(uint32_t timeout);

private:
    Return initGpios();
    Return initTimer(uint32_t samplingRate);
    Return initAdc();
    Return initAdcChannels();
    Return initDma();

    ADC_HandleTypeDef mAdcHandle = {};
    DMA_HandleTypeDef mAdcDmaHandle = {};
    TIM_HandleTypeDef mSampleRateTimer = {};

    osSemaphoreId_t mDataSemaphore {nullptr};
    std::array<uint32_t, NUM_CHANNELS>* mData;
    uint32_t mSamplingRate {DEFAULT_SAMPLING_RATE};

    static Adc* mInstance;

    static constexpr std::array<uint32_t, NUM_CHANNELS> ADC_CHANNELS = {
    		ADC_CHANNEL_0, ADC_CHANNEL_1, ADC_CHANNEL_2, ADC_CHANNEL_3, ADC_CHANNEL_4,
			ADC_CHANNEL_5, ADC_CHANNEL_6, ADC_CHANNEL_7, ADC_CHANNEL_8, ADC_CHANNEL_9,
			ADC_CHANNEL_10, ADC_CHANNEL_11, ADC_CHANNEL_12, ADC_CHANNEL_13, ADC_CHANNEL_14,
			ADC_CHANNEL_15,
    };

    static constexpr std::array<uint32_t, NUM_CHANNELS> ADC_CHANNEL_RANKS = {
    		ADC_REGULAR_RANK_1, ADC_REGULAR_RANK_2, ADC_REGULAR_RANK_3, ADC_REGULAR_RANK_4,
			ADC_REGULAR_RANK_5, ADC_REGULAR_RANK_6, ADC_REGULAR_RANK_7, ADC_REGULAR_RANK_8,
			ADC_REGULAR_RANK_9, ADC_REGULAR_RANK_10, ADC_REGULAR_RANK_11, ADC_REGULAR_RANK_12,
			ADC_REGULAR_RANK_13, ADC_REGULAR_RANK_14, ADC_REGULAR_RANK_15, ADC_REGULAR_RANK_16,
    };
};

}


#endif /* INC_DRIVERS_ADC_HPP_ */
