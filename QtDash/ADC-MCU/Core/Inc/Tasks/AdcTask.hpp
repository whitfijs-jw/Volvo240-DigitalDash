/*
 * AdcTask.hpp
 *
 *  Created on: Mar 8, 2025
 *      Author: whitfijs
 */

#ifndef INC_TASKS_ADCTASK_HPP_
#define INC_TASKS_ADCTASK_HPP_


#include <Tasks/Task.hpp>
#include <Drivers/Adc.hpp>

namespace Tasks {

class AdcTask : public Task {
public:
	AdcTask();
	~AdcTask() final = default;
    AdcTask& operator=(const AdcTask& src) = delete;
    AdcTask(const AdcTask& src) = delete;
    AdcTask& operator=(const AdcTask&& src) = delete;
    AdcTask(Task& src) = delete;

    Return setup() final;
    void loop() final;

private:
    Drivers::Adc mAdc = Drivers::Adc();
    std::array<uint32_t, Drivers::Adc::NUM_CHANNELS> mWordData;
    std::array<uint16_t, Drivers::Adc::NUM_CHANNELS> mHalfWordData;
};

}

#endif /* INC_TASKS_ADCTASK_HPP_ */
