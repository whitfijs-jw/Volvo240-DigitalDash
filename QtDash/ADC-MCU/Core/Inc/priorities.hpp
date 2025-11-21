/*
 * interrupt_priorities.hpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jwhitfield
 */

#ifndef INC_PRIORITIES_HPP_
#define INC_PRIORITIES_HPP_

#include <FreeRTOSConfig.h>

namespace InterruptPriorities {

static constexpr uint32_t DEFAULT_SUBPRIORITY = 0;

static constexpr uint32_t ADC_PRIO = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 3;

}

namespace TaskPriorities {
static constexpr osPriority_t ADC_DRIVER_PRIORITY = osPriorityAboveNormal;
static constexpr osPriority_t ADC_TASK_PRIORITY = osPriorityAboveNormal1;
}


#endif /* INC_PRIORITIES_HPP_ */
