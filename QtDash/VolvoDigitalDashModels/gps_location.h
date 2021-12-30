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


class GpsLocation : public QObject {
    Q_OBJECT
public:
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

    GpsLocation(QObject * parent) : QObject(parent) {

    }

    void init(QString port) {
        // serial port
        QVariantMap params;
        params["serialnmea.serial_port"] = port;//"/dev/ttyACM0";
        QStringList sources = QGeoPositionInfoSource::availableSources();
        for (int i = 0; i < sources.size(); i++) {
            std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
        }

        QGeoPositionInfoSource *serialPositionSource = QGeoPositionInfoSource::createSource("serialnmea", params, this);

        if (serialPositionSource != nullptr) {

            QObject::connect(serialPositionSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdate(QGeoPositionInfo)));

            serialPositionSource->setUpdateInterval(100);

            serialPositionSource->startUpdates();

            QObject::connect(this, SIGNAL(stop()), serialPositionSource, SLOT(stopUpdates()));
        }
    }

public slots:
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
    }

    void close() {
        emit stop();
    }

signals:
    void speedUpdateMeterPerSec(double mps);
    void speedUpdateMilesPerHour(qreal mph);
    void headingUpdateDegree(qreal heading);
    void headingUpdate(QString heading);
    void stop();

private:
    QSerialPort mPort;
    QString mPortName;

    CardinalDirection headingToDirection(qreal angle) {
        if (angle < 0) {
            angle += 360.0;
        }

        int iAngle = std::floor(angle);

        int dir = std::floor((iAngle + 23)%360/45);

        return (CardinalDirection) dir;
    }

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
