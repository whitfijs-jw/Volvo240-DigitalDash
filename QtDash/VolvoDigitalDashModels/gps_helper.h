#ifndef GPS_LOCATION_HPP
#define GPS_LOCATION_HPP

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <filesystem>
#include <iostream>
#include <QNmeaPositionInfoSource>
#include <QGeoPositionInfoSource>
#include <QVariantMap>
#include <cmath>

/**
 * @brief GPS helper class
 */
class GpsHelper : public QObject {
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
    };

    /**
     * @brief GpsHelper constructor
     * @param parent
     */
    GpsHelper(QObject * parent) : QObject(parent) {

    }

    /**
     * @brief Initialize and start the serial NMEA stream.
     * @param port: port to read from /dev/ttyACM0 is the default
     */
    void init(QString port = "/dev/ttyACM0") {
        // serial port
        QVariantMap params;
        params["serialnmea.serial_port"] = port;
        QStringList sources = QGeoPositionInfoSource::availableSources();
        for (int i = 0; i < sources.size(); i++) {
            std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
        }

        QGeoPositionInfoSource * serialPositionSource = QGeoPositionInfoSource::createSource("serialnmea", params, this);

        if (serialPositionSource != nullptr) {

            QObject::connect(serialPositionSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdate(QGeoPositionInfo)));

            serialPositionSource->setUpdateInterval(100);

            serialPositionSource->startUpdates();

            QObject::connect(this, SIGNAL(stop()), serialPositionSource, SLOT(stopUpdates()));
        }
    }

public slots:
    /**
     * @brief Process incoming GPS data
     * @param data: position information
     */
    void positionUpdate(QGeoPositionInfo data) {

        if (data.hasAttribute(QGeoPositionInfo::Direction)) {
            qreal heading = data.attribute(QGeoPositionInfo::Direction);
            QString headingString = headingToDirectionString(heading);
            std::cout << "heading: " << heading << " (" << headingString.toStdString() << ") " << std::endl;

            emit headingUpdateDegree(heading);
            emit headingUpdate(headingToDirectionString(heading));
        }
        double speed = data.attribute(QGeoPositionInfo::GroundSpeed);
        std::cout << std::setprecision(3) << speed << " m/s\t" << (speed * 2.23694) << " mph" << std::endl;

        emit speedUpdateMeterPerSec(speed);
        emit speedUpdateMilesPerHour(speed * 2.23694);
        emit speedUpdateKph(speed *  3.6);
    }

    /**
     * @brief Stop the current GPS updates
     */
    void close() {
        emit stop();
    }

signals:
    /**
     * @brief speedUpdateMeterPerSec
     * @param mps
     */
    void speedUpdateMeterPerSec(qreal mps);

    /**
     * @brief speedUpdateMilesPerHour
     * @param mph
     */
    void speedUpdateMilesPerHour(qreal mph);

    /**
     * @brief speedUpdateKph
     * @param kph
     */
    void speedUpdateKph(qreal kph);
    /**
     * @brief headingUpdateDegree
     * @param heading
     */
    void headingUpdateDegree(qreal heading);

    /**
     * @brief headingUpdate
     * @param heading
     */
    void headingUpdate(QString heading);

    /**
     * @brief stop
     */
    void stop();

private:
    /**
     * @brief Convert heading angle to cardinal direction (enum)
     * @param angle: heading direction retrieved from QGeoPositionInfo structure
     *
     * @return: @ref CardinalDirection
     */
    CardinalDirection headingToDirection(qreal angle) {
        if (angle < 0) {
            angle += 360.0;
        }

        int iAngle = std::floor(angle);

        int dir = std::floor((iAngle + 23)%360/45);

        return (CardinalDirection) dir;
    }

    /**
     * @brief Convert heading angle to Cardinal Direction string "N", "E", "SE", etc
     * @param angle: heading direction retrieved from QGeoPositionInfo structure
     *
     * @return Cardinal direction string
     */
    QString headingToDirectionString(qreal angle) {
        auto dir = headingToDirection(angle);

        switch (dir) {
        case CardinalDirection::NORTH:
            return "N";
        case CardinalDirection::NORTH_EAST:
            return "NE";
        case CardinalDirection::EAST:
            return "E";
        case CardinalDirection::SOUTH_EAST:
            return "SE";
        case CardinalDirection::SOUTH:
            return "S";
        case CardinalDirection::SOUTH_WEST:
            return "SW";
        case CardinalDirection::WEST:
            return "W";
        case CardinalDirection::NORTH_WEST:
            return "NW";
        }
    }
};

#endif // GPS_LOCATION_HPP
