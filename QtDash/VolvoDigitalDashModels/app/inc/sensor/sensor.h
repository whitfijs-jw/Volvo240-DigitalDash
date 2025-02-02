#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <sensor_source.h>
#include <config.h>

/**
 * @brief Sensor class -- takes data from a sensor source,
 * performs the necessary transform from the raw sensor source
 * values to the value to be displayed by a gauge
 */
class Sensor : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent: Parent QObject
     * @param config: Dash config
     * @param source: Sensor source that provides raw values
     * @param channel: channel to read from sensor source
     */
    Sensor(QObject * parent, Config * config,
           SensorSource * source, int channel) :
    QObject(parent), mConfig(config), mSource(source),
    mChannel(channel) {
        // connect the source dataReady signal to the sensor's transform slot
        QObject::connect(
                    mSource, &SensorSource::dataReady,
                    this, &Sensor::transform);
    }

    /**
     * @brief get the channel that we should be waiting on from the source
     * @return: channel
     */
    int getChannel() const {
        return mChannel;
    }

    /**
     * @brief getUnits
     * @return Expected units
     */
    virtual QString getUnits() const = 0;

signals:
    /**
     * @brief Signal to emit when the data has been transformed -- picked up by the gauge
     * @param data: data that has been transformed
     */
    void sensorDataReady(QVariant data);
public slots:
    /**
     * @brief Transform the raw data from the sensor source to the desired units.
     * Emits the sensorDataReady signal that should be used by a gauge to update
     * the gauge model.
     *
     * @param data: data from the sensor source
     * @param channel: channel that has been read
     */
    virtual void transform(QVariant data, int channel) {
        if (channel == mChannel) {
            emit sensorDataReady(data);
        }
    }

protected:
    Config * mConfig; //!< Dash config
    SensorSource * mSource; //!< Sensor source
    int mChannel; //!< Channel from the sensor source
};

#endif // SENSOR_H
