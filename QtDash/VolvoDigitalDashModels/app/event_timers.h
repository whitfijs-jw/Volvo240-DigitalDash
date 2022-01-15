#ifndef EVENT_TIMERS_H
#define EVENT_TIMERS_H

#include <QObject>
#include <QTimer>
#include <QMap>

/**
 * @brief The EventTimers class
 */
class EventTimers : public QObject{
    Q_OBJECT

public:
    static constexpr int FAST_TIMER_TIMEOUT_MSEC = 100; //!< fast time timeout
    static constexpr int MEDIUM_TIMER_TIMEOUT_MSEC = 250; //!< medium timer timeout
    static constexpr int SLOW_TIMER_TIMEOUT_MSEC = 500; //!< slow timer timeout

    /**
     * @brief Default timer values
     */
    enum class DataTimers{
        FAST_TIMER = 0,
        MEDIUM_TIMER,
        SLOW_TIMER,
    };

    /**
     * @brief EventTimers
     * @param parent
     */
    EventTimers(QObject * parent) : QObject(parent) {
        // Add the default timers
        addTimer(static_cast<int>(DataTimers::FAST_TIMER), FAST_TIMER_TIMEOUT_MSEC);
        addTimer(static_cast<int>(DataTimers::MEDIUM_TIMER), MEDIUM_TIMER_TIMEOUT_MSEC);
        addTimer(static_cast<int>(DataTimers::SLOW_TIMER), MEDIUM_TIMER_TIMEOUT_MSEC);
    }

    /**
     * @brief addTimer
     * @param timerId
     * @param timeoutMSec
     * @param start
     * @return
     */
    bool addTimer(int timerId, int timeoutMSec, bool start = false) {
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

    /**
     * @brief getTimer
     * @param timerId
     * @return
     */
    QTimer * getTimer(int timerId) {
        return mTimers.value(timerId, nullptr);
    }

    /**
     * @brief start
     */
    void start() {
        for (auto id : mTimers.keys()) {
            getTimer(id)->start();
        }
    }

signals:

public slots:

private:
    QMap<int, QTimer *> mTimers; //!< map of timers that are running in the app
};

#endif // EVENT_TIMERS_H
