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
#include <QProcess>
#include <QDateTime>
#include <QTimeZone>
#include <QtMath>
#include <sensor_utils.h>

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

        std::cout << "number of available data sources: " << sources.size() << std::endl;
        for (int i = 0; i < sources.size(); i++) {
            std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
        }

        QSerialPort * serialPort = new QSerialPort(this);
        serialPort->setPortName(port);
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->open(QIODevice::ReadOnly);

        if(serialPort->isOpen()) {
            QNmeaPositionInfoSource *source = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode);
            source->setDevice(serialPort);

            if(source){
                connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdate(QGeoPositionInfo)));

                source->setUpdateInterval(100);

                source->startUpdates();

                QObject::connect(this, SIGNAL(stop()), source, SLOT(stopUpdates()));
                //QObject::connect(this, SIGNAL(stop()), serialPort, SLOT(close()));
            }
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

#ifdef RASPBERRY_PI
            // setting time -- this is gross
            if (!mTimeSet) {
                auto ts = data.timestamp();

                auto coord = data.coordinate();
                auto tz = guessAtTheTimeZone(coord);
                //ts.setTimeZone(tz);

                std::cout << "Timezone? maybe?: " << tz.abbreviation(ts).toStdString() << std::endl;

                QString pg = "/bin/date";
                QStringList args;
                args << "-s" << ts.toString("yyyy-MM-dd hh:mm:ss") << "-u";

                QProcess *proc = new QProcess(this);

                QObject::connect(proc, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
                                 [=](int exitCode, QProcess::ExitStatus exitStatus) {
                    (void)exitStatus;
                    std::cout << "finished date set: " << exitCode << std::endl;
                });

                proc->startDetached(pg, args);
                mTimeSet = true;

                std::cout << "Set Time to: " << ts.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
            }
#endif

//            QString headingString = headingToDirectionString(heading);
//            std::cout << "heading: " << heading << " (" << headingString.toStdString() << ")" << std::endl;

            emit headingUpdateDegree(heading);
            emit headingUpdate(headingToDirectionString(heading));
        }
        double speed = data.attribute(QGeoPositionInfo::GroundSpeed);
        //std::cout << std::setprecision(3) << speed << " m/s\t" << (speed * 2.23694) << " mph" << std::endl;

        emit speedUpdateMeterPerSec(speed);
        emit speedUpdateMilesPerHour(SensorUtils::convert(speed, Config::UNITS_MPH, Config::UNITS_METERS_PER_SECOND));
        emit speedUpdateKph(SensorUtils::convert(speed, Config::UNITS_KPH, Config::UNITS_METERS_PER_SECOND));
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
    static constexpr uint8_t UBLOX_CFG_RATE_10HZ[] = {
        0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12
    };

    static constexpr uint8_t UBLOX_SAVE_CONFIG[] = {
        0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x31, 0xBF
    };

    bool mTimeSet = false;

    QTimeZone guessAtTheTimeZone(QGeoCoordinate coord) {
        // this is more gross
        std::cout << "Current longitude: " << coord.longitude() << std::endl;

        int offset = qRound(coord.longitude() / 15.0) * 3600;
        return QTimeZone(offset);
    }


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

        return "";
    }
};

#endif // GPS_LOCATION_HPP
