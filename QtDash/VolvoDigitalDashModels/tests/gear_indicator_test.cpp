#include "gear_indicator_test.h"

using namespace ConfigKeys;

void GearIndicatorTest::init() {

}

void GearIndicatorTest::cleanup() {

}

/**
 * @brief GearIndicatorTest::initTestCase
 *
 * [vss_input]
    pulse_per_rot=12
    tire_diameter=24.9
    diameter_units="inch"
    pulse_per_unit_distance=9720
    distance_units="mile"
    max_speed="185"
    use_gps=false

    [gear_indicator]
    gear_ratios=4.03, 2.16, 1.37, 1.00, 0.82;
    rear_end_ratio=3.31
    ratio_delta=0.25
    speed_drop_out=5
    speed_drop_out_units="mph"
    idle_high_rpm=1100
    idle_low_rpm=500
 */
void GearIndicatorTest::initTestCase() {
    QSettings * gearConfig = new QSettings("gearConfig.ini", QSettings::IniFormat);

    gearConfig->beginGroup(VSS_INPUT_GROUP);
    gearConfig->setValue(VSS_PULSES_PER_ROTATION, 12);
    gearConfig->setValue(VSS_TIRE_DIAMETER, 24.9);
    gearConfig->setValue(VSS_TIRE_DIAMETER_UNITS, "inch");
    gearConfig->setValue(VSS_PULSES_PER_DISTANCE, 9720);
    gearConfig->setValue(VSS_DISTANCE_UNITS, "mile");
    gearConfig->setValue(VSS_MAX_SPEED, 185);
    gearConfig->setValue(VSS_USE_GPS, false);
    gearConfig->endGroup();

    QVariantList gearRatios = {4.03, 2.16, 1.37, 1.00, 0.82};
    gearConfig->beginGroup(GEAR_INDICATOR_GROUP);
    gearConfig->setValue(GEAR_INDICATOR_GEAR_RATIOS,
                         gearRatios);
    gearConfig->setValue(GEAR_INDICATOR_REAR_END_RATIO, 3.31);
    gearConfig->setValue(GEAR_INDICATOR_DELTA, 0.25);
    gearConfig->setValue(GEAR_INDICATOR_SPEED_DROPOUT, 5);
    gearConfig->setValue(GEAR_INDICATOR_SPEED_DROPOUT_UNITS, "mph");
    gearConfig->setValue(GEAR_INDICATOR_HIGH_IDLE, 1100);
    gearConfig->setValue(GEAR_INDICATOR_LOW_IDLE, 500);
    gearConfig->endGroup();

    delete gearConfig;

    mConfig = new Config(this, "gearConfig.ini");
    mTachSource = new TachSource(this, mConfig);
    mVssSource = new VssSource(this, mConfig);

    mGearSensor = new GearSensor(this, mConfig,
                                 mTachSource,
                                 static_cast<int>(TachSource::TachDataChannel::RPM_CHANNEL),
                                 mVssSource,
                                 static_cast<int>(VssSource::VssDataChannel::MPH));
}

void GearIndicatorTest::initTestCase_data() {

}

void GearIndicatorTest::cleanupTestCase() {
    delete mGearSensor;
    delete mVssSource;
    delete mTachSource;
    delete mConfig;
}

void GearIndicatorTest::testEstimateGear() {
    QFETCH(qreal, rpm);
    QFETCH(qreal, speed);
    QFETCH(QString, units);
    QFETCH(qreal, rpmDelta);
    QFETCH(qreal, speedDelta);
    QFETCH(int, expectedGear);

    for (float dRpm = -rpmDelta; dRpm <= rpmDelta; dRpm += (rpmDelta / 1.0)) {
        for(float dSpeed = -speedDelta; dSpeed <= speedDelta; dSpeed += (speedDelta / 1.0)) {
            qreal currentSpeed = speed + dSpeed;
            qreal currentRpm = rpm + dRpm;

            int gearEst = mGearSensor->estimateGear(
                currentRpm,
                currentSpeed,
                Units::getSpeedUnits(units)
            );
            qDebug() << "RPM: " << currentRpm << " Speed: " << currentSpeed << " Est Gear: " << gearEst << " Expected Gear: " << expectedGear;
            QCOMPARE(expectedGear, gearEst);
        }
    }
}

void GearIndicatorTest::testEstimateGear_data() {
    QTest::addColumn<qreal>("rpm");
    QTest::addColumn<qreal>("speed");
    QTest::addColumn<QString>("units");
    QTest::addColumn<qreal>("rpmDelta");
    QTest::addColumn<qreal>("speedDelta");
    QTest::addColumn<int>("expectedGear");

    // calculated using : https://www.tremec.com/calculadora.php
    QTest::addRow("1500_1st_gear") << 1500.0 << 8.33 << "mph" << 50.0 << 2.0 << 1;
    QTest::addRow("2000_1st_gear") << 2000.0 << 11.11 << "mph" << 50.0 << 2.0 << 1;
    QTest::addRow("2500_1st_gear") << 2500.0 << 13.88 << "mph" << 50.0 << 2.0 << 1;
    QTest::addRow("3000_1st_gear") << 3000.0 << 16.66 << "mph" << 50.0 << 2.0 << 1;
    QTest::addRow("3500_1st_gear") << 3500.0 << 19.44 << "mph" << 50.0 << 2.0 << 1;
    QTest::addRow("4000_1st_gear") << 4000.0 << 22.21 << "mph" << 50.0 << 2.0 << 1;

    QTest::addRow("1500_2nd_gear") << 1500.0 << 15.54 << "mph" << 50.0 << 2.0 << 2;
    QTest::addRow("2000_2nd_gear") << 2000.0 << 20.72 << "mph" << 50.0 << 2.0 << 2;
    QTest::addRow("2500_2nd_gear") << 2500.0 << 25.90 << "mph" << 50.0 << 2.0 << 2;
    QTest::addRow("3000_2nd_gear") << 3000.0 << 31.08 << "mph" << 50.0 << 2.0 << 2;
    QTest::addRow("3500_2nd_gear") << 3500.0 << 36.26 << "mph" << 50.0 << 2.0 << 2;
    QTest::addRow("4000_2nd_gear") << 4000.0 << 41.44 << "mph" << 50.0 << 2.0 << 2;

    QTest::addRow("1500_3rd_gear") << 1500.0 << 24.50 << "mph" << 50.0 << 2.0 << 3;
    QTest::addRow("2000_3rd_gear") << 2000.0 << 32.67 << "mph" << 50.0 << 2.0 << 3;
    QTest::addRow("2500_3rd_gear") << 2500.0 << 40.84 << "mph" << 50.0 << 2.0 << 3;
    QTest::addRow("3000_3rd_gear") << 3000.0 << 49.01 << "mph" << 50.0 << 2.0 << 3;
    QTest::addRow("3500_3rd_gear") << 3500.0 << 57.17 << "mph" << 50.0 << 2.0 << 3;
    QTest::addRow("4000_3rd_gear") << 4000.0 << 65.34 << "mph" << 50.0 << 2.0 << 3;

    QTest::addRow("1500_4th_gear") << 1500.0 << 33.57 << "mph" << 50.0 << 2.0 << 4;
    QTest::addRow("2000_4th_gear") << 2000.0 << 44.76 << "mph" << 50.0 << 2.0 << 4;
    QTest::addRow("2500_4th_gear") << 2500.0 << 55.95 << "mph" << 50.0 << 2.0 << 4;
    QTest::addRow("3000_4th_gear") << 3000.0 << 67.14 << "mph" << 50.0 << 2.0 << 4;
    QTest::addRow("3500_4th_gear") << 3500.0 << 78.33 << "mph" << 50.0 << 2.0 << 4;
    QTest::addRow("4000_4th_gear") << 4000.0 << 89.52 << "mph" << 50.0 << 2.0 << 4;

    QTest::addRow("1500_5th_gear") << 1500.0 << 40.94 << "mph" << 50.0 << 2.0 << 5;
    QTest::addRow("2000_5th_gear") << 2000.0 << 54.59 << "mph" << 50.0 << 2.0 << 5;
    QTest::addRow("2500_5th_gear") << 2500.0 << 68.23 << "mph" << 50.0 << 2.0 << 5;
    QTest::addRow("3000_5th_gear") << 3000.0 << 81.88 << "mph" << 50.0 << 2.0 << 5;
    QTest::addRow("3500_5th_gear") << 3500.0 << 95.52 << "mph" << 50.0 << 2.0 << 5;
    QTest::addRow("4000_5th_gear") << 4000.0 << 109.17 << "mph" << 50.0 << 2.0 << 5;
}

void GearIndicatorTest::testGenerateTransformationMatrix() {
    QFETCH(size_t, numGears);
    QFETCH(qreal, stay);
    QFETCH(qreal, adjacent);
    QFETCH(qreal, neutral);
    QFETCH(qreal, skip);

    GearPredictiveFilter::TransitionProbabilities probs = {
        stay, adjacent, neutral, skip, numGears
    };

    Eigen::MatrixXd TMat(numGears, numGears);
    GearPredictiveFilter::generateTransitionMatrix(probs, TMat);

    for (size_t row = 0; row < numGears; row++) {
        auto rowSum = 0.0;
        for (size_t col = 0; col < numGears; col++) {
            rowSum += TMat(row, col);
        }
        QCOMPARE(rowSum, 1.0);
    }
}

void GearIndicatorTest::testGenerateTransformationMatrix_data() {
    QTest::addColumn<size_t>("numGears");
    QTest::addColumn<qreal>("stay");
    QTest::addColumn<qreal>("adjacent");
    QTest::addColumn<qreal>("neutral");
    QTest::addColumn<qreal>("skip");

    QTest::addRow("5_speed_0.9_0.04_0.015_0.001") << static_cast<size_t>(6) << 0.9 << 0.04 << 0.015 << 0.001;
}


void GearIndicatorTest::testMovingAverageFilter() {
    QFETCH(size_t, N);
    QFETCH(QList<qreal>, input_data);
    QFETCH(QList<qreal>, expected_output);

    GearPredictiveFilter::MovingAvgFilter filter(N);
    QCOMPARE(filter.buffer.size(), static_cast<long>(N));
    QCOMPARE(filter.count, 0);


    for (int i = 0; i < input_data.size(); i++) {
        auto output = filter.update(input_data.at(i));
        QCOMPARE(output, expected_output.at(i));
    }
}
void GearIndicatorTest::testMovingAverageFilter_data() {
    QTest::addColumn<size_t>("N");
    QTest::addColumn<QList<qreal>>("input_data");
    QTest::addColumn<QList<qreal>>("expected_output");

    size_t N = 8;
    QList<qreal> input_data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    QList<qreal> expected_output  = {0.0000, 0.1250, 0.3750, 0.7500, 1.2500, 1.8750, 2.6250, 3.5000, 4.5000, 5.5000, 6.5000, 7.5000, 8.5000, 9.5000, 10.5000, 11.5000};

    QTest::addRow("N=8, input_data_sequential-0:15") << N << input_data << expected_output;
}

void GearIndicatorTest::testCalculateLikelihood() {
    QFETCH(qreal, observed);
    QFETCH(qreal, mean);
    QFETCH(qreal, sigma);
    QFETCH(qreal, expected);

    auto val = GearPredictiveFilter::calculateLikelihood(observed, mean, sigma);
    QCOMPARE(val, expected);
}
void GearIndicatorTest::testCalculateLikelihood_data() {
    QTest::addColumn<qreal>("observed");
    QTest::addColumn<qreal>("mean");
    QTest::addColumn<qreal>("sigma");
    QTest::addColumn<qreal>("expected");

    QTest::addRow("10.0_9.0_0.4") << 10.0 << 9.0 << 0.4 << 0.04382075123392136;
    QTest::addRow("0.4_0.0_0.4") << 0.4 << 0.0 << 0.4 << 0.604926811297858;
}

void GearIndicatorTest::testGenerateLikelihoodVector() {
    QFETCH(qreal, observed);
    QFETCH(QList<qreal>, expected);
    QFETCH(QList<qreal>, sigma);
    QFETCH(QList<qreal>, output);
    QFETCH(int, ret);

    // make vectors
    GearPredictiveFilter::ValueVector expectedValues(expected.size());
    GearPredictiveFilter::NoiseSigmaVector sigmaNoiseVector(sigma.size());
    GearPredictiveFilter::LikelihoodVector expectedLikelihood(output.size());
    GearPredictiveFilter::LikelihoodVector likelihoodVector(output.size());

    for(int i = 0; i < expected.size(); i++) {
        expectedValues(i) = expected.at(i);
    }

    for (int i = 0; i < sigma.size(); i++) {
        sigmaNoiseVector(i) = sigma.at(i);
    }

    for (int i = 0; i < output.size(); i++) {
        expectedLikelihood(i) = output.at(i);
    }

    auto retVal = GearPredictiveFilter::generateLikelihoodVector(
        observed,
        expectedValues,
        sigmaNoiseVector,
        likelihoodVector
    );

    QCOMPARE(retVal, ret);
    for (int i = 0; i < expectedLikelihood.size(); i++) {
        QCOMPARE(likelihoodVector(i), expectedLikelihood(i));
    }
}

void GearIndicatorTest::testGenerateLikelihoodVector_data() {
    QTest::addColumn<qreal>("observed");
    QTest::addColumn<QList<qreal>>("expected");
    QTest::addColumn<QList<qreal>>("sigma");
    QTest::addColumn<QList<qreal>>("output");
    QTest::addColumn<int>("ret");

    QList<qreal> expectedM47 = {1.800726538550296e2, 9.651536782304315e1, 6.121576570257830e1, 4.468304065881627e1, 3.664009334022934e1};
    QList<qreal> sigmaM47 = {5.402179615650887, 2.895461034691294, 1.836472971077349, 1.340491219764488, 1.099202800206880};
    QList<qreal> outputValues = {
        GearPredictiveFilter::FIXED_NEUTRAL_LIKELIHOOD, 7.276829916651464e-2, 0.0, 0.0, 0.0, 0.0};
    QTest::addRow("5speed_M47_1st_gear") << 181.0 << expectedM47 << sigmaM47 << outputValues << 0;
}

void GearIndicatorTest::testFlattenLikelihood() {
    QFETCH(QList<qreal>, likelihoods_vector);
    QFETCH(qreal, offset);
    QFETCH(QList<qreal>, expected_output);

    GearPredictiveFilter::LikelihoodVector likelihoodVector(likelihoods_vector.size());
    for (int i = 0; i < likelihoods_vector.size(); i++) {
        likelihoodVector(i) = likelihoods_vector.at(i);
    }

    auto output = GearPredictiveFilter::flattenLikelihood(likelihoodVector, offset);
    QCOMPARE(output, 0);

    for (int i = 0; i < likelihoodVector.size(); i++) {
        QCOMPARE(likelihoodVector(i), expected_output.at(i));
    }

}
void GearIndicatorTest::testFlattenLikelihood_data() {
    QTest::addColumn<QList<qreal>>("likelihoods_vector");
    QTest::addColumn<qreal>("offset");
    QTest::addColumn<QList<qreal>>("expected_output");

    QList<qreal> likelihood_0_9_0_02 = {0.9, 0.02, 0.02, 0.02, 0.02, 0.02};
    QList<qreal> expected_output_0_9_0_02 = {0.5500, 0.1100, 0.1100, 0.1100,0.1100,0.1100};
    QTest::addRow("flatten_0.9_0.02x5") << likelihood_0_9_0_02 << 0.1 << expected_output_0_9_0_02;
}

void GearIndicatorTest::testGenerateExpectedValues() {
    QFETCH(QList<qreal>, gear_ratios);
    QFETCH(qreal, rear_end_ratio);
    QFETCH(qreal, tire_diameter_inch);
    QFETCH(int, tire_diameter_units);
    QFETCH(QList<qreal>, expected_values);
    QFETCH(int, ret_val);

    SensorConfig::GearIndicatorConfig_t gearConfig;

    gearConfig.gearRatios = gear_ratios;
    gearConfig.rearEndRatio = rear_end_ratio;
    gearConfig.tireDiameter = tire_diameter_inch;
    gearConfig.tireDiameterUnits = static_cast<Units::DistanceUnits>(tire_diameter_units);

    GearPredictiveFilter::ValueVector expected(gear_ratios.size());
    auto ret = GearPredictiveFilter::generateExpectedValues(gearConfig, expected);

    QCOMPARE(ret_val, ret);
    QCOMPARE(expected_values.size(), expected.size());
    for (int i = 0; i < expected_values.size(); i++) {
        QCOMPARE(expected_values.at(i), expected(i));
    }
}

void GearIndicatorTest::testGenerateExpectedValues_data() {
    QTest::addColumn<QList<qreal>>("gear_ratios");
    QTest::addColumn<qreal>("rear_end_ratio");
    QTest::addColumn<qreal>("tire_diameter_inch");
    QTest::addColumn<int>("tire_diameter_units");
    QTest::addColumn<QList<qreal>>("expected_values");
    QTest::addColumn<int>("ret_val");

    QList<qreal> m47_ratios = {4.03, 2.16, 1.37, 1.00, 0.82};
    qreal rear_end_ratio = 3.31;
    qreal tire_diameter_inch = 24.9;
    auto tire_diameter_units = Units::DistanceUnits::INCH;
    QList<qreal> expectedM47 = {1.800726427469334e2, 9.651536186932408e1, 6.121576192637685e1, 4.468303790246485e1, 3.664009108002118e1};

    QTest::addRow("m47_331_24.9tire_expected_values") << m47_ratios << rear_end_ratio << tire_diameter_inch << static_cast<int>(tire_diameter_units) << expectedM47 << 0;
}

void GearIndicatorTest::testGenerateInitialProbabilities() {
    QFETCH(QList<qreal>, gear_ratios);
    QFETCH(qreal, neutral_prob);
    QFETCH(QList<qreal>, expected_probs);
    QFETCH(int, ret_val);

    SensorConfig::GearIndicatorConfig_t gearConfig;
    gearConfig.gearRatios = gear_ratios;
    GearPredictiveFilter::ProbabilityVector initial_probs(gear_ratios.size() + 1);

    auto ret = GearPredictiveFilter::generateInitialProbablilities(gearConfig, initial_probs, neutral_prob);
    QCOMPARE(ret_val, ret);

    for (int i = 0; i < initial_probs.size(); i++) {
        QCOMPARE(initial_probs(i), expected_probs.at(i));
    }
}
void GearIndicatorTest::testGenerateInitialProbabilities_data() {
    QTest::addColumn<QList<qreal>>("gear_ratios");
    QTest::addColumn<qreal>("neutral_prob");
    QTest::addColumn<QList<qreal>>("expected_probs");
    QTest::addColumn<int>("ret_val");

    QList<qreal> m47_ratios = {4.03, 2.16, 1.37, 1.00, 0.82};
    qreal neutral_prob = GearPredictiveFilter::DEFAULT_INITIAL_NEUTRAL_PROB;
    QList<qreal> expected_prob = {0.9, 0.02, 0.02, 0.02, 0.02, 0.02};

    QTest::addRow("m47_0.9neutral") << m47_ratios << neutral_prob << expected_prob << 0;
}

void GearIndicatorTest::testGenerateSigmaNoiseVector() {
    QFETCH(QList<qreal>, expected);
    QFETCH(qreal, noise_pct);
    QFETCH(QList<qreal>, expected_sigma_vector);
    QFETCH(int, ret_val);

    // make vectors
    GearPredictiveFilter::ValueVector expectedValues(expected.size());
    GearPredictiveFilter::NoiseSigmaVector expectedSigmaNoiseVector(expected_sigma_vector.size());
    GearPredictiveFilter::NoiseSigmaVector sigmaNoiseVector(expected_sigma_vector.size());

    for(int i = 0; i < expected.size(); i++) {
        expectedValues(i) = expected.at(i);
    }

    for (int i = 0; i < expected_sigma_vector.size(); i++) {
        expectedSigmaNoiseVector(i) = expected_sigma_vector.at(i);
    }

    auto ret = GearPredictiveFilter::generateSigmaNoiseVector(expectedValues, noise_pct, sigmaNoiseVector);

    QCOMPARE(ret_val, ret);
    for (int i = 0; i < expectedSigmaNoiseVector.size(); i++) {
        QCOMPARE(sigmaNoiseVector(i), expectedSigmaNoiseVector(i));
    }

}
void GearIndicatorTest::testGenerateSigmaNoiseVector_data() {
    QTest::addColumn<QList<qreal>>("expected");
    QTest::addColumn<qreal>("noise_pct");
    QTest::addColumn<QList<qreal>>("expected_sigma_vector");
    QTest::addColumn<int>("ret_val");

    QList<qreal> expectedM47 = {1.800726538550296e2, 9.651536782304315e1, 6.121576570257830e1, 4.468304065881627e1, 3.664009334022934e1};
    QList<qreal> sigmaM47 = {5.402179615650887, 2.895461034691294, 1.836472971077349, 1.340491219764488, 1.099202800206880};

    QTest::addRow("m47_0.03sigma_pct") << expectedM47 << GearPredictiveFilter::DEFAULT_SIGMA_PCT << sigmaM47 << 0;
}

void GearIndicatorTest::testUpdate() {
    QFETCH(QList<qreal>, observed_mph);
    QFETCH(QList<qreal>, observed_rpm);
    QFETCH(QList<int>, true_gear);
    QFETCH(QList<qreal>, gear_ratios);
    QFETCH(qreal, speed_drop_out);
    QFETCH(QString, speed_dropout_units);
    QFETCH(qreal, idle_high_rpm);
    QFETCH(qreal, rear_end_ratio);
    QFETCH(qreal, tire_diameter_inch);
    QFETCH(int, tire_diameter_units);


    SensorConfig::GearIndicatorConfig_t gearConfig;

    gearConfig.gearRatios = gear_ratios;
    gearConfig.idleHighRpm = idle_high_rpm;
    gearConfig.smoothingFilterN = 4;
    gearConfig.speedDropOut = speed_drop_out;
    gearConfig.speedDropOutUnits = Units::getSpeedUnits(speed_dropout_units);
    gearConfig.rearEndRatio = rear_end_ratio;
    gearConfig.tireDiameter = tire_diameter_inch;
    gearConfig.tireDiameterUnits = static_cast<Units::DistanceUnits>(tire_diameter_units);

    GearPredictiveFilter::TransitionProbabilities transition;
    transition.numStates = gear_ratios.size() + 1;

    GearPredictiveFilter filter(transition, gearConfig);
    size_t gear_lag_cnt = 0;
    for (int i = 0; i < observed_mph.size(); i++) {
        auto gear = filter.update(observed_mph.at(i), observed_rpm.at(i));
        if (gear.index == true_gear.at(i)) {
            QCOMPARE(1, 1);
            gear_lag_cnt = 0;
        } else {
            QVERIFY(gear_lag_cnt++ <= 40);
        }
    }
}

void GearIndicatorTest::testUpdate_data() {
    QTest::addColumn<QList<qreal>>("observed_mph");
    QTest::addColumn<QList<qreal>>("observed_rpm");
    QTest::addColumn<QList<int>>("true_gear");
    QTest::addColumn<QList<qreal>>("gear_ratios");
    QTest::addColumn<qreal>("speed_drop_out");
    QTest::addColumn<QString>("speed_dropout_units");
    QTest::addColumn<qreal>("idle_high_rpm");
    QTest::addColumn<qreal>("rear_end_ratio");
    QTest::addColumn<qreal>("tire_diameter_inch");
    QTest::addColumn<int>("tire_diameter_units");

    QList<qreal> mph_starting_in_neutral = {0.000000, 0.025755, 0.000000, 0.000000, 0.000000, 1.429299, 1.744138, 0.828147, 0.000000, 0.302617, 1.010646, 0.000000, 0.000000, 0.696111, 0.000000, 1.536641, 0.000000, 0.000000, 0.589113, 0.000000, 0.000000, 0.192444, 0.000000, 0.000000, 0.000000, 0.943767, 0.000000, 0.000000, 0.615805, 0.000000, 0.731145, 0.271250, 0.000000, 0.213418, 0.550131, 1.632934, 0.935081, 0.388145, 0.000000, 0.535274, 0.370644, 0.521625, 0.183784, 0.364368, 0.000000, 0.584547, 2.342637, 2.753731, 0.963125, 1.082728, 2.685108, 1.539264, 2.822271, 2.054132, 3.323658, 2.985075, 1.565958, 3.559517, 2.278816, 3.361473, 3.256897, 3.470576, 4.006734, 5.461341, 4.583368, 4.809392, 5.094714, 5.128214, 3.798144, 4.607459, 6.080229, 4.925616, 5.616077, 5.779595, 6.352517, 7.262382, 5.897716, 6.208054, 7.050551, 7.430915, 8.641213, 7.863815, 6.760459, 8.264037, 9.604442, 7.285779, 8.591251, 7.922247, 7.292376, 10.038525, 9.345098, 9.453449, 10.432754, 8.601492, 11.534672, 9.742284, 10.774549, 10.664633, 10.280280, 10.020907, 10.608590, 11.618005, 11.905841, 10.714878, 11.916187, 12.747111, 10.396923, 12.664474, 11.349710, 13.327954, 12.379418, 12.039313, 13.687457, 13.609002, 13.511241, 14.410349, 13.980144, 14.979917, 12.909831, 13.920070, 13.431254, 13.957509, 15.187452, 13.341955, 15.613182, 14.747085, 15.722127, 14.864467, 16.488515, 15.201824, 14.838422, 16.507514, 16.935069, 15.916600, 18.214687, 16.004136, 17.475808, 17.593393, 17.938705, 17.341910, 17.678041, 18.327167, 17.883146, 17.646788, 18.166949, 18.505970, 20.155855, 18.470603, 18.208091, 19.414721};
    QList<qreal> rpm_starting_in_neutral = {840.000000, 930.000000, 870.000000, 720.000000, 660.000000, 810.000000, 930.000000, 840.000000, 840.000000, 780.000000, 840.000000, 930.000000, 900.000000, 810.000000, 810.000000, 690.000000, 930.000000, 870.000000, 870.000000, 840.000000, 750.000000, 900.000000, 660.000000, 690.000000, 840.000000, 810.000000, 1140.000000, 870.000000, 780.000000, 870.000000, 720.000000, 870.000000, 810.000000, 960.000000, 810.000000, 930.000000, 780.000000, 930.000000, 840.000000, 720.000000, 720.000000, 930.000000, 960.000000, 630.000000, 840.000000, 900.000000, 990.000000, 780.000000, 840.000000, 750.000000, 900.000000, 810.000000, 840.000000, 1050.000000, 870.000000, 720.000000, 900.000000, 810.000000, 630.000000, 600.000000, 660.000000, 960.000000, 960.000000, 690.000000, 990.000000, 630.000000, 990.000000, 900.000000, 900.000000, 810.000000, 1020.000000, 1110.000000, 1140.000000, 960.000000, 1230.000000, 1290.000000, 1050.000000, 1080.000000, 1140.000000, 1170.000000, 1350.000000, 1320.000000, 1110.000000, 1200.000000, 1290.000000, 1560.000000, 1560.000000, 1680.000000, 1470.000000, 1800.000000, 1590.000000, 1740.000000, 1680.000000, 1650.000000, 1950.000000, 1620.000000, 1800.000000, 1980.000000, 1830.000000, 2070.000000, 2250.000000, 2220.000000, 1950.000000, 1950.000000, 2370.000000, 1950.000000, 2160.000000, 2010.000000, 2250.000000, 2280.000000, 2370.000000, 2190.000000, 2190.000000, 2310.000000, 2520.000000, 2460.000000, 2580.000000, 2670.000000, 2640.000000, 2610.000000, 2460.000000, 2520.000000, 2520.000000, 2610.000000, 2880.000000, 2670.000000, 2730.000000, 2760.000000, 3000.000000, 2760.000000, 2940.000000, 2640.000000, 3000.000000, 3090.000000, 3090.000000, 3000.000000, 2970.000000, 3150.000000, 3150.000000, 3120.000000, 2970.000000, 3240.000000, 3330.000000, 3150.000000, 3300.000000, 3270.000000, 3480.000000, 3120.000000, 3510.000000, 3420.000000};
    QList<int> true_gear_starting_in_neutral = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    QList<qreal> m47_ratios = {4.03, 2.16, 1.37, 1.00, 0.82};
    qreal rear_end_ratio = 3.31;
    qreal tire_diameter_inch = 24.9;
    auto tire_diameter_units = Units::DistanceUnits::INCH;

    QTest::addRow("starting_in_neutral") <<
        mph_starting_in_neutral <<
        rpm_starting_in_neutral <<
        true_gear_starting_in_neutral <<
        m47_ratios <<
        5.0 <<
        "mph" <<
        1000.0 <<
        rear_end_ratio <<
        tire_diameter_inch <<
        static_cast<int>(tire_diameter_units);
}
