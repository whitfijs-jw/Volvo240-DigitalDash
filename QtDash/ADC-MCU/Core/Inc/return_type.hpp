/*
 * return_type.hpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jwhitfield
 */

#ifndef INC_RETURN_TYPE_HPP_
#define INC_RETURN_TYPE_HPP_


enum class ReturnCode {
    OK = 0,
    ERROR = -1,
    HAL_ADC_ERROR = -2,
    HAL_DMA_ERROR = -3,
    HAL_TIM_ERROR = -4,
    HAL_GPIO_ERROR = -5,
};


namespace Tasks {
    using Return = ReturnCode;
}

namespace Drivers {
    using Return = ReturnCode;
}

#endif /* INC_RETURN_TYPE_HPP_ */
