#ifndef SENSORTEST_H
#define SENSORTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include <sensor_utils.h>
#include <sensor.h>
#include <sensor_source.h>

class TestSource : public SensorSource {
    Q_OBJECT
public:
    TestSource(QObject * parent, Config * config, QString name = "testSource") :
        SensorSource(parent, config, name) {

    }

    bool init() override {
        mInit = true;
        return mInit;
    }

    int getNumChannels() override {
        return 4;
    }

    QString getUnits(int channel) override {
        switch(channel) {
        case 0:
            return Config::UNITS_FOOT;
        case 1:
            return Config::UNITS_INCH;
        case 2:
            return Config::UNITS_CENTIMETER;
        case 3:
            return Config::UNITS_METER;
        default:
            return Config::UNITS_FOOT;
        }
    }

public slots:
    void updateAll() {
        for (int i = 0; i < getNumChannels(); i++) {
            emit dataReady(24.0, i);
        }
    }

    void update(int channel) {
        emit dataReady(24.0, channel);
    }

private:
    bool mInit = false;
};

class TestSensor : public Sensor {
    Q_OBJECT
public:
    TestSensor(QObject * parent, Config * config, SensorSource * source, int channel)
        : Sensor(parent, config, source, channel) {

    }

    QString getUnits() override {
        return Config::UNITS_INCH;
    }

public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            emit sensorDataReady(SensorUtils::convert(data.toReal(), getUnits(), mSource->getUnits(channel)));
        }
    }
};

class TestSensor1 : public Sensor {
    Q_OBJECT
public:
    TestSensor1(QObject * parent, Config * config, SensorSource * source, int channel)
        : Sensor(parent, config, source, channel) {

    }

    QString getUnits() override {
        return Config::UNITS_FOOT;
    }

public slots:
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            emit sensorDataReady(SensorUtils::convert(data.toReal(), getUnits(), mSource->getUnits(channel)));
        }
    }
};

class SensorTest : public QObject
{
    Q_OBJECT
public:

signals:

private slots:
    void initTestCase();

    void test_sensorSourceConstructor();
    void test_sensorConstructor();
    void test_sensor1Constructor();
    void test_channelUpdate();

    void cleanupTestCase();

private:
    TestSource * testSource;
    TestSensor * testSensor;
    TestSensor1 * testSensor1;
};

#endif // SENSORTEST_H
