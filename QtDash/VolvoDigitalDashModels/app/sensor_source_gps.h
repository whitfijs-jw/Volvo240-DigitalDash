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

class GpsSource : public SensorSource {
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

    enum class GpsDataChannel {
        SPEED_MILES_PER_HOUR = 0,
        SPEED_METERS_PER_SEC,
        SPEED_KILOMETERS_PER_HOUR,
        HEADING_DEGREES,
        HEADING_CARDINAL
    };

    GpsSource(QObject * parent, Config * config, QString name = "gps") :
        SensorSource(parent, config, name) {
        mLastData.insert(GpsDataChannel::HEADING_CARDINAL, "");
        mLastData.insert(GpsDataChannel::HEADING_DEGREES, 0.0);
        mLastData.insert(GpsDataChannel::SPEED_METERS_PER_SEC, 0.0);
        mLastData.insert(GpsDataChannel::SPEED_MILES_PER_HOUR, 0.0);
        mLastData.insert(GpsDataChannel::SPEED_KILOMETERS_PER_HOUR, 0.0);
    }

    bool init() {
        // serial port
        QVariantMap params;
        // TODO: get port from config? Find ACMx port?
        QString port = "/dev/ttyACM0";
        params["serialnmea.serial_port"] = port;
        QStringList sources = QGeoPositionInfoSource::availableSources();

        std::cout << "number of available data sources: " << sources.size() << std::endl;
        for (int i = 0; i < sources.size(); i++) {
            std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
        }

        QSerialPort * serialPort = new QSerialPort(this->parent());
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
                connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                        this, SLOT(update(QGeoPositionInfo)));

                source->setUpdateInterval(100);

                source->startUpdates();

                QObject::connect(this, SIGNAL(stop()),
                                 source, SLOT(stopUpdates()));
            }
        }

        return true;
    }

    int getNumChannels() {
        return 1;
    }

    QVariant getValue(int channel) {
        return mLastData.value((GpsDataChannel)channel, "");
    }

    QString getUnits(int channel) {
        switch ((GpsDataChannel)channel) {
        case GpsDataChannel::HEADING_CARDINAL:
            return "direction";
        case GpsDataChannel::HEADING_DEGREES:
            return "degrees";
        case GpsDataChannel::SPEED_METERS_PER_SEC:
            return "m/s";
        case GpsDataChannel::SPEED_MILES_PER_HOUR:
            return "mph";
        case GpsDataChannel::SPEED_KILOMETERS_PER_HOUR:
            return "kph";
        default:
            return "";
        }
    }

    void close() {
        emit stop();
    }

signals:
    void stop();

public slots:
    void updateAll() {
        // add the last data points
        for (auto key : mLastData.keys()) {
            update((int) key);
        }
    }

    void update(int channel) {
        emit dataReady(mLastData.value((GpsDataChannel)channel, ""), channel);
    }

    void update(QGeoPositionInfo data) {
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
                                 [=](int exitCode, QProcess::ExitStatus _exitStatus) {
                    std::cout << "finished date set: " << exitCode << std::endl;
                });

                proc->startDetached(pg, args);
                mTimeSet = true;

                std::cout << "Set Time to: " << ts.toString("yyyy-MM-dd hh:mm:ss").toStdString() << std::endl;
            }
#endif

            QString headingString = headingToDirectionString(heading);
            //std::cout << "heading: " << heading << " (" << headingString.toStdString() << ")" << std::endl;

            emit dataReady(heading, (int) GpsDataChannel::HEADING_DEGREES);
            emit dataReady(headingString, (int) GpsDataChannel::HEADING_CARDINAL);

            mLastData.insert(GpsDataChannel::HEADING_DEGREES, heading);
            mLastData.insert(GpsDataChannel::HEADING_CARDINAL, headingString);
        }
        double speed = data.attribute(QGeoPositionInfo::GroundSpeed);

        qreal speedMph = speed * 2.23694;
        qreal speedKph = speed * 3.6;

        mLastData.insert(GpsDataChannel::SPEED_METERS_PER_SEC, speed);
        mLastData.insert(GpsDataChannel::SPEED_MILES_PER_HOUR, speedMph);
        mLastData.insert(GpsDataChannel::SPEED_KILOMETERS_PER_HOUR, speedKph);

        emit dataReady(speed, (int) GpsDataChannel::SPEED_METERS_PER_SEC);
        emit dataReady(speed * 2.23694, (int) GpsDataChannel::SPEED_MILES_PER_HOUR);
        emit dataReady(speed * 3.6, (int) GpsDataChannel::SPEED_KILOMETERS_PER_HOUR);
    }


private:
    bool mTimeSet = false;
    QMap<GpsDataChannel, QVariant> mLastData;

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

#endif // SENSOR_SOURCE_GPS_H
