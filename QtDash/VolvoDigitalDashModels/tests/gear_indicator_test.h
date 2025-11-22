#ifndef GEAR_INDICATOR_TEST_H
#define GEAR_INDICATOR_TEST_H

#include <QObject>
#include <QTest>

#include <sensor_gear_indicator.h>
#include <gear_predictive_filter.h>

class GearIndicatorTest : public QObject
{
    Q_OBJECT
public:

private:
    GearSensor * mGearSensor;
    Config * mConfig;
    TachSource * mTachSource;
    VssSource * mVssSource;

    GearPredictiveFilter * filter = nullptr;

private slots:
    void init();
    void cleanup();

    void initTestCase();
    void initTestCase_data();
    void cleanupTestCase();

    void testEstimateGear();
    void testEstimateGear_data();

    void testGenerateTransformationMatrix();
    void testGenerateTransformationMatrix_data();
};

#endif // GEAR_INDICATOR_TEST_H
