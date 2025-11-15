#include "gear_indicator_test.h"

using namespace ConfigKeys;

void GearIndicatorTest::init() {

}

void GearIndicatorTest::cleanup() {

}

void GearIndicatorTest::initTestCase() {
}


/**
 * @brief GearIndicatorTest::initTestCase_data
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
void GearIndicatorTest::initTestCase_data() {
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

    for (float dRpm = -rpmDelta; dRpm < rpmDelta; dRpm += (rpmDelta / 1.0)) {
        for(float dSpeed = -speedDelta; dSpeed < speedDelta; dSpeed += (speedDelta / 1.0)) {
            qreal currentSpeed = speed + dSpeed;
            qreal currentRpm = rpm + dRpm;

            int gearEst = mGearSensor->estimateGear(
                currentRpm,
                currentSpeed,
                Units::getSpeedUnits(units)
            );
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
    QTest::addRow("1500_1st_gear") << 1500.0 << 8.33 << "mph" << 100.0 << 2.0 << 1;
    QTest::addRow("2000_1st_gear") << 2000.0 << 11.11 << "mph" << 100.0 << 2.0 << 1;
    QTest::addRow("2500_1st_gear") << 2500.0 << 13.88 << "mph" << 100.0 << 2.0 << 1;
    QTest::addRow("3000_1st_gear") << 3000.0 << 16.66 << "mph" << 100.0 << 2.0 << 1;
    QTest::addRow("3500_1st_gear") << 3500.0 << 19.44 << "mph" << 100.0 << 2.0 << 1;
    QTest::addRow("4000_1st_gear") << 4000.0 << 22.21 << "mph" << 100.0 << 2.0 << 1;

    QTest::addRow("1500_2nd_gear") << 1500.0 << 15.54 << "mph" << 100.0 << 2.0 << 2;
    QTest::addRow("2000_2nd_gear") << 2000.0 << 20.72 << "mph" << 100.0 << 2.0 << 2;
    QTest::addRow("2500_2nd_gear") << 2500.0 << 25.90 << "mph" << 100.0 << 2.0 << 2;
    QTest::addRow("3000_2nd_gear") << 3000.0 << 31.08 << "mph" << 100.0 << 2.0 << 2;
    QTest::addRow("3500_2nd_gear") << 3500.0 << 36.26 << "mph" << 100.0 << 2.0 << 2;
    QTest::addRow("4000_2nd_gear") << 4000.0 << 41.44 << "mph" << 100.0 << 2.0 << 2;

    QTest::addRow("1500_3rd_gear") << 1500.0 << 24.50 << "mph" << 100.0 << 2.0 << 3;
    QTest::addRow("2000_3rd_gear") << 2000.0 << 32.67 << "mph" << 100.0 << 2.0 << 3;
    QTest::addRow("2500_3rd_gear") << 2500.0 << 40.84 << "mph" << 100.0 << 2.0 << 3;
    QTest::addRow("3000_3rd_gear") << 3000.0 << 49.01 << "mph" << 100.0 << 2.0 << 3;
    QTest::addRow("3500_3rd_gear") << 3500.0 << 57.17 << "mph" << 100.0 << 2.0 << 3;
    QTest::addRow("4000_3rd_gear") << 4000.0 << 65.34 << "mph" << 100.0 << 2.0 << 3;

    QTest::addRow("1500_4th_gear") << 1500.0 << 33.57 << "mph" << 100.0 << 2.0 << 4;
    QTest::addRow("2000_4th_gear") << 2000.0 << 44.76 << "mph" << 100.0 << 2.0 << 4;
    QTest::addRow("2500_4th_gear") << 2500.0 << 55.95 << "mph" << 100.0 << 2.0 << 4;
    QTest::addRow("3000_4th_gear") << 3000.0 << 67.14 << "mph" << 100.0 << 2.0 << 4;
    QTest::addRow("3500_4th_gear") << 3500.0 << 78.33 << "mph" << 100.0 << 2.0 << 4;
    QTest::addRow("4000_4th_gear") << 4000.0 << 89.52 << "mph" << 100.0 << 2.0 << 4;

    QTest::addRow("1500_5th_gear") << 1500.0 << 40.94 << "mph" << 100.0 << 2.0 << 5;
    QTest::addRow("2000_5th_gear") << 2000.0 << 54.59 << "mph" << 100.0 << 2.0 << 5;
    QTest::addRow("2500_5th_gear") << 2500.0 << 68.23 << "mph" << 100.0 << 2.0 << 5;
    QTest::addRow("3000_5th_gear") << 3000.0 << 81.88 << "mph" << 100.0 << 2.0 << 5;
    QTest::addRow("3500_5th_gear") << 3500.0 << 95.52 << "mph" << 100.0 << 2.0 << 5;
    QTest::addRow("4000_5th_gear") << 4000.0 << 109.17 << "mph" << 100.0 << 2.0 << 5;
}
