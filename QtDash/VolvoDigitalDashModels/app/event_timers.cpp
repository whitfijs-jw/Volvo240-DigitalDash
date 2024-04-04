#include <event_timers.h>

EventTimers::EventTimers(QObject *parent) : QObject(parent) {
    // Add the default timers
    addTimer(static_cast<int>(DataTimers::VERY_FAST_TIMER), VERY_FAST_TIMER_TIMEOUT_MSEC);
    addTimer(static_cast<int>(DataTimers::FAST_TIMER), FAST_TIMER_TIMEOUT_MSEC);
    addTimer(static_cast<int>(DataTimers::MEDIUM_TIMER), MEDIUM_TIMER_TIMEOUT_MSEC);
    addTimer(static_cast<int>(DataTimers::SLOW_TIMER), SLOW_TIMER_TIMEOUT_MSEC);
}


bool EventTimers::addTimer(int timerId, int timeoutMSec, bool start) {
    if (!mTimers.contains(timerId)) {
        QTimer * timer = new QTimer(this->parent());
        timer->setInterval(timeoutMSec);

        mTimers.insert(timerId, timer);

        if (start) {
            getTimer(timerId)->start();
        }

        return true;
    } else {
        return false;
    }
}

QTimer * EventTimers::getTimer(int timerId) {
    return mTimers.value(timerId, nullptr);
}

void EventTimers::start() {
    QList<int> keys = mTimers.keys();
    for (auto id : keys) {
        if (getTimer(id) != nullptr) {
            getTimer(id)->start();
        }
    }
}

void EventTimers::stop() {
    QList<int> keys = mTimers.keys();
    for (auto id : keys) {
        if (getTimer(id) != nullptr) {
            getTimer(id)->stop();
        }
    }
}
