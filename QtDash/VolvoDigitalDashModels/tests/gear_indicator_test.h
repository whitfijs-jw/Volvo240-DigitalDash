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

    void testMovingAverageFilter();
    void testMovingAverageFilter_data();

    void testCalculateLikelihood();
    void testCalculateLikelihood_data();

    void testGenerateLikelihoodVector();
    void testGenerateLikelihoodVector_data();

    void testFlattenLikelihood();
    void testFlattenLikelihood_data();

    void testGenerateExpectedValues();
    void testGenerateExpectedValues_data();

    void testGenerateInitialProbabilities();
    void testGenerateInitialProbabilities_data();

    void testGenerateSigmaNoiseVector();
    void testGenerateSigmaNoiseVector_data();

};

#endif // GEAR_INDICATOR_TEST_H
