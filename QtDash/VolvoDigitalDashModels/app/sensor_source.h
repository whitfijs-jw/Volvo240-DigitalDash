#ifndef SENSOR_SOURCE_H
#define SENSOR_SOURCE_H

#include <QObject>
#include <config.h>

/**
 * @brief The SensorSource class collects raw data from a
 * hardware sensor (adc, gpio, vss, etc) and passes the data along
 * to a sensor class to transform the raw values into
 */
class SensorSource : public QObject {
    Q_OBJECT
public:
    /**
     * @brief SensorSource constructor
     * @param parent: parent QObject
     * @param config: dash config
     * @param name: source name
     */
    SensorSource(QObject * parent, Config * config, QString name) :
        QObject(parent), mConfig(config), mName(name) {

    }
    /**
     * @brief Initialize the source
     * @return
     */
    virtual bool init() = 0;

    /**
     * @brief Get the number of channels available from the source
     * @return
     */
    virtual int getNumChannels() = 0;

    /**
     * @brief Get the units for each channel
     * @param channel: channel to get units from
     * @return: units of the desired channel
     */
    virtual QString getUnits(int channel) = 0;

    /**
     * @brief Get source name
     * @return source name
     */
    virtual QString getName() {
        return mName;
    }

signals:
    /**
     * @brief Signal to emi when data is ready to be served to
     * a sensor
     *
     * @param data: data read from hardware device
     * @param channel: channel read from
     */
    void dataReady(QVariant data, int channel);

public slots:
    /**
     * @brief Read from all channels and emit dataReady for each one
     */
    virtual void updateAll() = 0;

    /**
     * @brief Read from given channel and emit dataReady
     * @param channel: channel to read from
     */
    virtual void update(int channel) = 0;

protected:
    Config * mConfig; //!< Dash config
    QString mName; //!< Source name
};

#endif // SENSOR_SOURCE_H
