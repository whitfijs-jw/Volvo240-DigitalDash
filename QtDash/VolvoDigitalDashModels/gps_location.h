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


class GpsLocation : public QObject {
    Q_OBJECT
public:
    GpsLocation(QObject * parent) : QObject(parent) {

    }

    void init() {
        // serial port
        QVariantMap params;
        params["serialnmea.serial_port"] = "/dev/ttyACM0";
        QStringList sources = QGeoPositionInfoSource::availableSources();
        for (int i = 0; i < sources.size(); i++) {
            std::cout << sources.at(i).toLocal8Bit().constData() << std::endl;
        }

        QGeoPositionInfoSource *serialPositionSource = QGeoPositionInfoSource::createSource("serialnmea", params, this);


        if (serialPositionSource != nullptr) {

            QObject::connect(serialPositionSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdate(QGeoPositionInfo)));

            serialPositionSource->setUpdateInterval(100);

            serialPositionSource->startUpdates();
        }
    }

public slots:
    void positionUpdate(QGeoPositionInfo data) {
        double speed = data.attribute(QGeoPositionInfo::GroundSpeed);
        std::cout << std::setprecision(3) << speed << " m/s at heading: " << data.Direction << std::endl;

        emit speedUpdateMeterPerSec(speed);
        emit speedUpdateMilesPerHour(speed * 2.23694);
    }

signals:
    void speedUpdateMeterPerSec(double mps);
    void speedUpdateMilesPerHour(qreal mph);

private:
    QSerialPort mPort;
    QString mPortName;
};

#endif // GPS_LOCATION_HPP
