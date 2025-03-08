/*
 * Task.hpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jwhitfield
 */

#ifndef INC_TASKS_TASK_HPP_
#define INC_TASKS_TASK_HPP_

#include <return_type.hpp>
#include <cmsis_os2.h>

namespace Tasks {

class Task {
public:
    static constexpr uint32_t DEFAULT_STACK_SIZE = 256;

    Task(const char * taskName, osPriority_t priority, uint32_t stackSize);
    virtual ~Task() = default;

    Task& operator=(const Task& src) = delete;
    Task(const Task& src) = delete;
    Task& operator=(const Task&& src) = delete;
    Task(Task& src) = delete;

    virtual Return init();
    virtual Return setup() = 0;
    virtual void loop() = 0;

    osThreadId_t getThreadHandle() {
        return mHandle;
    }
private:
    static void runner(void * task);

    uint8_t mId {0};
    osThreadId_t mHandle {nullptr};
    osThreadAttr_t mAttr = {};
};

}


#endif /* INC_TASKS_TASK_HPP_ */
