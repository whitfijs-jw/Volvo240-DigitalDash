#ifndef SENSOR_SOURCE_GPS_H
#define SENSOR_SOURCE_GPS_H

#include <sensor_source.h>
#include <QString>
#include <QSerialPort>
#include <filesystem>
#include <iostream>
#include <QNmeaPositionInfoSource>
#include <QGeoPositionInfoSource>
#include <QVariantMap>
#include <cmath>
#include <QProcess>
#include <QDateTime>
#include <QTimeZone>
#include <QtMath>
#include <sensor_utils.h>

/**
 * @brief Gps sensor source
 */
class GpsSource : public SensorSource {
    Q_OBJECT
public:
    /**
     * @brief cardinal directions
     */
    enum class CardinalDirection {
        NORTH = 0,
        NORTH_EAST,
        EAST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST,
        WEST,
        NORTH_WEST,
        NORTH_1,
    };

    /**
     * @brief GPS source channels
     */
    enum class GpsDataChannel {
        SPEED_MILES_PER_HOUR = 0,
        SPEED_METERS_PER_SEC,
        SPEED_KILOMETERS_PER_HOUR,
        HEADING_DEGREES,
        HEADING_CARDINAL
    };

    /**
     * @brief GPS Sensor source
     * @param parent parent object
     * @param config Dash config
     * @param name source name
     */
    GpsSource(QObject * parent,
              Config * config,
              QString name = "gps");

    /**
     * @brief Source initialization
     * @return true on success
     */
    bool init() override {
        return true;
    }

    /**
     * @brief Get the number of channels
     * @return number of channels
     */
    int getNumChannels() override {
        return 5;
    }

    /**
     * @brief Get a channel's units
     * @param channel channel number
     * @return String value of the channel's units
     */
    QString getUnits(int channel) override;

    /**
     * @brief Stop the GPS source broadcasts
     */
    void close() {
        emit stop();
    }

signals:
    /**
     * @brief Stop GPS update signals
     */
    void stop();

public slots:
    /**
     * @brief Update all channels
     */
    void updateAll() override {
        // add the last data points
        for (auto key : mLastData.keys()) {
            update((int) key);
        }
    }

    /**
     * @brief Channel update
     * @param channel channel to update
     */
    void update(int channel) override {
        emit dataReady(mLastData.value((GpsDataChannel)channel, ""), channel);
    }

    /**
     * @brief Update the current state of the GPS data
     * @param data GPS data from NMEA source
     */
    void updatePosition(QGeoPositionInfo data);


private:
    bool mTimeSet = false; //!< Time has been set
    QMap<GpsDataChannel, QVariant> mLastData; //!< Data from last GPS update

    /**
     * @brief Guess at the current timezone given the current coordinates
     * @param coord current coordinates
     * @return Current timezone estimate
     */
    QTimeZone guessAtTheTimeZone(QGeoCoordinate coord);

    /**
     * @brief Convert heading angle to cardinal direction (enum)
     * @param angle: heading direction retrieved from QGeoPositionInfo structure
     *
     * @return: @ref CardinalDirection
     */
    CardinalDirection headingToDirection(qreal angle);

    /**
     * @brief Convert heading angle to Cardinal Direction string "N", "E", "SE", etc
     * @param angle: heading direction retrieved from QGeoPositionInfo structure
     *
     * @return Cardinal direction string
     */
    QString headingToDirectionString(qreal angle);
};

#endif // SENSOR_SOURCE_GPS_H
