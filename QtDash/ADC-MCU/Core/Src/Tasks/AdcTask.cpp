/*
 * AdcTask.cpp
 *
 *  Created on: Mar 8, 2025
 *      Author: whitfijs
 */

#include <Tasks/AdcTask.hpp>
#include <priorities.hpp>
#include <algorithm>
#include <stm32u5xx_hal.h>

using namespace Tasks;

AdcTask::AdcTask() :
	Task("adc_task", TaskPriorities::ADC_TASK_PRIORITY, 1024) {
}

Return AdcTask::setup() {
	if (auto ret = mAdc.init(); ret != Return::OK) {
		return ret;
	}

	return Return::OK;
}

void AdcTask::loop() {
	mAdc.enableSampling(mWordData);
	while(1) {
		if (mAdc.waitForSample(0) == osOK) {
			// truncate 32 bit data
		    std::transform(mWordData.cbegin(), mWordData.cend(), mHalfWordData.begin(), [](uint32_t x) {
		       return static_cast<uint16_t>(x & 0xFFFF);
		    });
		}

		// wait on i2c comms
		osDelay(1000);

		HAL_I2C_Slave_Seq_Receive_DMA(hi2c, pData, Size, XferOptions)
	}
}
