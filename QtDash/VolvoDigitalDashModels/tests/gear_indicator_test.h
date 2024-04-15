#ifndef GEAR_INDICATOR_TEST_H
#define GEAR_INDICATOR_TEST_H

#include <QObject>
#include <QTest>

#include <sensor_gear_indicator.h>

class GearIndicatorTest : public QObject
{
    Q_OBJECT
public:

private:
    GearSensor * mGearSensor;
    Config * mConfig;
    TachSource * mTachSource;
    VssSource * mVssSource;

private slots:
    void init();
    void cleanup();

    void initTestCase();
    void initTestCase_data();
    void cleanupTestCase();

    void testEstimateGear();
    void testEstimateGear_data();

};

#endif // GEAR_INDICATOR_TEST_H
