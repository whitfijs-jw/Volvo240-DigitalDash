/*
 * Adc.cpp
 *
 *  Created on: Mar 7, 2025
 *      Author: whitfijs
 */
#include <Drivers/Adc.hpp>
#include <priorities.hpp>

using namespace Drivers;

Adc::Adc(size_t numChannels, uint32_t samplingRate) :
        Tasks::Task("adc_driver", TaskPriorities::ADC_TASK_PRIORITY, 512),
        mNumChannels(numChannels),
        mSamplingRate(samplingRate) {

}

Return Drivers::Adc::setup() {
    if (auto ret = initGpios(); ret != Return::OK) {
        return ret;
    }

    if (auto ret = initAdc(mNumChannels); ret != Return::OK) {
        return ret;
    }

    if (auto ret = initDma(); ret != Return::OK) {
        return ret;
    }

    if (auto ret = initTimer(mSamplingRate); ret != Return::OK) {
        return ret;
    }

    return Return::OK;
}

Return Drivers::Adc::loop() {
}

Return Drivers::Adc::initGpios() {
    // enable clocks
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef gpioInit = {};
    gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
    gpioInit.Mode = GPIO_MODE_ANALOG;
    gpioInit.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &gpioInit);

    gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
            |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &gpioInit);

    gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    HAL_GPIO_Init(GPIOB, &gpioInit);
}

Return Drivers::Adc::initTimer(uint32_t samplingRate) {
}

Return Drivers::Adc::initAdc(size_t numChannels) {
    __HAL_RCC_ADC12_CLK_ENABLE();

    mAdcHandle.Instance = ADC1;
    mAdcHandle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    mAdcHandle.Init.Resolution = ADC_RESOLUTION_14B;
    mAdcHandle.Init.GainCompensation = 0;
    mAdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    mAdcHandle.Init.ScanConvMode = ADC_SCAN_ENABLE;
    mAdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    mAdcHandle.Init.LowPowerAutoWait = DISABLE;
    mAdcHandle.Init.ContinuousConvMode = DISABLE;
    mAdcHandle.Init.NbrOfConversion = numChannels;
    mAdcHandle.Init.DiscontinuousConvMode = DISABLE;
    mAdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIG_T4_TRGO;
    mAdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
    mAdcHandle.Init.DMAContinuousRequests = DISABLE;
    mAdcHandle.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
    mAdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    mAdcHandle.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
    mAdcHandle.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
    mAdcHandle.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_68CYCLES;
    mAdcHandle.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_68CYCLES;
    mAdcHandle.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&mAdcHandle) != HAL_OK) {
        return Return::HAL_ADC_ERROR;
    }

    HAL_NVIC_SetPriority(ADC1_IRQn, InterruptPriorities::ADC_PRIO, InterruptPriorities::DEFAULT_SUBPRIORITY);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    HAL_ADC_Stop(&mAdcHandle);
}

Return Drivers::Adc::initAdcChannels() {
}

Return Drivers::Adc::initDma() {
    /* ADC1 DMA Init */
    __HAL_RCC_GPDMA1_CLK_ENABLE();

    /* GPDMA1_REQUEST_ADC1 Init */
    mAdcDmaHandle.Instance = GPDMA1_Channel0;
    mAdcDmaHandle.Init.Request = GPDMA1_REQUEST_ADC1;
    mAdcDmaHandle.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    mAdcDmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    mAdcDmaHandle.Init.SrcInc = DMA_SINC_FIXED;
    mAdcDmaHandle.Init.DestInc = DMA_DINC_INCREMENTED;
    mAdcDmaHandle.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_WORD;
    mAdcDmaHandle.Init.DestDataWidth = DMA_DEST_DATAWIDTH_WORD;
    mAdcDmaHandle.Init.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
    mAdcDmaHandle.Init.SrcBurstLength = 1;
    mAdcDmaHandle.Init.DestBurstLength = 1;
    mAdcDmaHandle.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT0;
    mAdcDmaHandle.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    mAdcDmaHandle.Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(&mAdcDmaHandle) != HAL_OK) {
      return Return::HAL_DMA_ERROR;
    }

    __HAL_LINKDMA(&mAdcHandle, DMA_Handle, mAdcDmaHandle);

    if (HAL_DMA_ConfigChannelAttributes(&mAdcDmaHandle, DMA_CHANNEL_NPRIV) != HAL_OK) {
        return Return::HAL_DMA_ERROR;
    }
}

extern "C" void ADC1_IRQHandler(void) {
    auto * instance = Adc::getInstance();
    if (instance != nullptr) {
        HAL_ADC_IRQHandler(instance->getHandle());
    }
}

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandle) {
    auto * instance = AdcLL::getInstance();
    osThreadFlagsSet(
        instance->getThreadHandle(),
        to_underlying(AdcLL::NotificationsType::SampleReady));
}

/**
 * @brief This function handles GPDMA1 Channel 0 global interrupt.
 */
extern "C" void GPDMA1_Channel0_IRQHandler(void) {
    auto* instance = AdcLL::getInstance(AdcLL::Adc_t::ADC_1);
    if (instance) {
        HAL_DMA_IRQHandler(instance->getDMAHandle());
    }
}




