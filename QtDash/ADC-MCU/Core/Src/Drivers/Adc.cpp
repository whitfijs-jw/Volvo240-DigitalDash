/*
 * Adc.cpp
 *
 *  Created on: Mar 7, 2025
 *      Author: whitfijs
 */
#include <Drivers/Adc.hpp>
#include <priorities.hpp>

using namespace Drivers;

Adc* Adc::mInstance = nullptr;

Adc::Adc(uint32_t samplingRate) :
        Tasks::Task("adc_driver", TaskPriorities::ADC_DRIVER_PRIORITY, 512),
        mSamplingRate(samplingRate) {
	setIntsance(*this);
}

Return Adc::setup() {
	mDataSemaphore = osSemaphoreNew(1, 0, nullptr);
	if (mData == nullptr) {
		return Return::ERROR;
	}

    if (auto ret = initGpios(); ret != Return::OK) {
        return ret;
    }

    if (auto ret = initAdc(); ret != Return::OK) {
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

void Adc::loop() {
	while(true) {
		auto flags = osThreadFlagsWait(Adc::SAMPLE_READY_FLAG, osFlagsWaitAny, 5000);

		if ((flags & osFlagsErrorTimeout) == osFlagsErrorTimeout) {
			// we're not running skip the remainder of the loop
			continue;
		}

		if ((flags & Adc::SAMPLE_READY_FLAG) == Adc::SAMPLE_READY_FLAG) {
			osSemaphoreRelease(mDataSemaphore);
		}
	}
}

osStatus_t Adc::waitForSample(uint32_t timeout) {
	if (mDataSemaphore == nullptr) {
		return osErrorResource;
	}

	return osSemaphoreAcquire(mDataSemaphore, timeout);
}

Return Adc::enableSampling(std::array<uint32_t, Adc::NUM_CHANNELS>& data) {
	mData = &data;

	//stop everything
	if (auto ret = disableSampling(); ret != Return::OK) {
		return ret;
	}

	//reset member variables

	// restart
	if (HAL_TIM_Base_Start(&mSampleRateTimer) != HAL_OK) {
		return Return::HAL_TIM_ERROR;
	}
	if (HAL_ADC_Start_DMA(&mAdcHandle, data.data(), data.size()) != HAL_OK) {
		return Return::HAL_TIM_ERROR;
	}
    return Return::OK;
}

Return Adc::disableSampling() {
    // stop everything
    if (HAL_TIM_Base_Stop(&mSampleRateTimer) != HAL_OK) {
        return Return::HAL_TIM_ERROR;
    }
    if (HAL_ADC_Stop_DMA(&mAdcHandle) != HAL_OK) {
        return Return::HAL_TIM_ERROR;
    }

    return Return::OK;
}

Return Adc::initGpios() {
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

    gpioInit.Pin = GPIO_PIN_0|GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &gpioInit);

    return Return::OK;
}

Return Drivers::Adc::initTimer(uint32_t samplingRate) {
    uint32_t period = 0;
    uint32_t prescaler = 0;
    RCC_ClkInitTypeDef clkconfig;
    uint32_t timBaseClock;
    uint32_t timApbPrescaler;
    uint32_t pFLatency;

    HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
    /* Get APB1 prescaler */
    timApbPrescaler = clkconfig.APB1CLKDivider;

    /* Compute TIM6 clock */
    if (timApbPrescaler == RCC_HCLK_DIV1)
    {
        timBaseClock = HAL_RCC_GetPCLK1Freq();
    }
    else
    {
        timBaseClock = 2UL * HAL_RCC_GetPCLK1Freq();
    }
     /* Compute the prescaler value to have TIM6 counter clock equal to 100KHz */
    prescaler = ((timBaseClock / 100000U) - 1U);
    period = (100000U / samplingRate) - 1U;

    __HAL_RCC_TIM4_CLK_ENABLE();

    mSampleRateTimer.Instance = TIM4;
    mSampleRateTimer.Init.Prescaler = prescaler;
    mSampleRateTimer.Init.Period = period;
    mSampleRateTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    mSampleRateTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
    mSampleRateTimer.Init.RepetitionCounter = 0;
    mSampleRateTimer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (HAL_TIM_Base_Init(&mSampleRateTimer) != HAL_OK) {
        return Return::HAL_TIM_ERROR;
    }

    // Clock source:
    TIM_ClockConfigTypeDef sClockSourceConfig = {};
    sClockSourceConfig.ClockSource  = TIM_CLOCKSOURCE_INTERNAL;

    if (HAL_TIM_ConfigClockSource(&mSampleRateTimer, &sClockSourceConfig) != HAL_OK) {
        return Return::HAL_TIM_ERROR;
    }

    TIM_MasterConfigTypeDef sMasterConfig = {};
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&mSampleRateTimer, &sMasterConfig) != HAL_OK){
        return Return::HAL_TIM_ERROR;
    }

    return Return::OK;
}

Return Drivers::Adc::initAdc() {
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
    mAdcHandle.Init.NbrOfConversion = Adc::NUM_CHANNELS;
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

    return Return::OK;
}

Return Drivers::Adc::initAdcChannels() {
	ADC_ChannelConfTypeDef channelConfig = {};
	channelConfig.SamplingTime = ADC_SAMPLETIME_68CYCLES;
	channelConfig.OffsetNumber = ADC_OFFSET_NONE;
	channelConfig.Offset = 0;
	channelConfig.SingleDiff = ADC_SINGLE_ENDED;

	for (uint32_t i = 0; i < Adc::NUM_CHANNELS; i++) {
		channelConfig.Channel = ADC_CHANNELS[i];
		channelConfig.Rank = ADC_CHANNEL_RANKS[i];

		HAL_ADC_ConfigChannel(&mAdcHandle, &channelConfig);
	}

	if (auto ret = HAL_ADCEx_Calibration_Start(&mAdcHandle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED); ret != HAL_OK) {
		return Return::HAL_ADC_ERROR;
	}

	return Return::OK;
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

    return Return::OK;
}

extern "C" void ADC1_IRQHandler(void) {
    auto * instance = Adc::getInstance();
    if (instance != nullptr) {
        HAL_ADC_IRQHandler(instance->getAdcHandle());
    }
}

extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef * AdcHandle) {
	(void) AdcHandle;
    auto * instance = Adc::getInstance();
    osThreadFlagsSet(instance->getThreadHandle(), Adc::SAMPLE_READY_FLAG);
}

extern "C" void GPDMA1_Channel0_IRQHandler(void) {
    auto* instance = Adc::getInstance();
    if (instance) {
        HAL_DMA_IRQHandler(instance->getDmaHandle());
    }
}




