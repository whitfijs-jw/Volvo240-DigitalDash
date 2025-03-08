/*
 * Task.cpp
 *
 *  Created on: Mar 7, 2025
 *      Author: jwhitfield
 */


#include <Tasks/Task.hpp>
using namespace Tasks;

Task::Task(const char * taskName, osPriority_t priority, uint32_t stackSize) {
    mAttr.name = taskName;
    mAttr.priority = priority;
    mAttr.stack_size = stackSize;
}

Return Task::init() {
    mHandle = osThreadNew(Task::runner, this, &mAttr);

    if (mHandle == nullptr) {
        return Return::ERROR;
    }

    return Return::OK;
}

void Task::runner(void * param) {
    auto * task  = static_cast<Task*>(param);

    if (task == nullptr) {
        // the thread wasn't configured properly
        goto runner_failure;
    }

    task->loop();

    osThreadSuspend(task->mHandle);

runner_failure:
    for (;;) {
        osDelay(1000);
    }
}
