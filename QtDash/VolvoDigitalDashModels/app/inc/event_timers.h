#ifndef EVENT_TIMERS_H
#define EVENT_TIMERS_H

#include <QObject>
#include <QTimer>
#include <QMap>

/**
 * @brief Collection of timers to run Dash events
 */
class EventTimers : public QObject{
    Q_OBJECT

public:
    static constexpr int VERY_FAST_TIMER_TIMEOUT_MSEC = 50; //!< very fast timer timeout
    static constexpr int FAST_TIMER_TIMEOUT_MSEC = 100; //!< fast timer timeout
    static constexpr int MEDIUM_TIMER_TIMEOUT_MSEC = 150; //!< medium timer timeout
    static constexpr int SLOW_TIMER_TIMEOUT_MSEC = 500; //!< slow timer timeout

    /**
     * @brief Default timer values
     */
    enum class DataTimers{
        VERY_FAST_TIMER = 0,
        FAST_TIMER,
        MEDIUM_TIMER,
        SLOW_TIMER,
    };

    /**
     * @brief EventTimers Constructor
     * @param parent
     */
    EventTimers(QObject * parent);
    /**
     * @brief Add timer to the collection
     * @param timerId: timer id of timer to add
     * @param timeoutMSec: timer timeout in milliseconds
     * @param start: Set true to start time immediately
     * @return true if timer was added, false if it already exists
     */
    bool addTimer(int timerId, int timeoutMSec, bool start = false);

    /**
     * @brief Get timer from collection
     * @param timerId: timer id
     * @return Pointer to timer if it exists in collection, nullptr otherwise
     */
    QTimer * getTimer(int timerId);
signals:

public slots:
    /**
     * @brief Start all timers in collection
     */
    void start();

    /**
     * @brief Stop all timers in collection
     */
    void stop();
private:
    QMap<int, QTimer *> mTimers; //!< map of timers that are running in the app
};

#endif // EVENT_TIMERS_H
