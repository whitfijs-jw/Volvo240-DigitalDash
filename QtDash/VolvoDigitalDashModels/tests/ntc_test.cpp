#include "ntc_test.h"
#include <ntc.h>
#include <compare_float.h>

void NtcTest::testNtcConstructor() {
    QFETCH(qreal, t1);
    QFETCH(qreal, t2);
    QFETCH(qreal, t3);
    QFETCH(qreal, r1);
    QFETCH(qreal, r2);
    QFETCH(qreal, r3);
    QFETCH(int, units);
    QFETCH(int, type);

    QFETCH(qreal, A);
    QFETCH(qreal, B);
    QFETCH(qreal, C);



    // Assemble the config structure
    SensorConfig::TempSensorConfig config;
    config.r1 = r1;
    config.r2 = r2;
    config.r3 = r3;
    config.t1 = t1;
    config.t2 = t2;
    config.t3 = t3;
    config.rBalance = rBalance;
    config.vSupply = vSupply;
    config.type = static_cast<SensorConfig::TemperatureSensorType>(type);
    config.units = static_cast<Units::TemperatureUnits>(units);

    // make new object
    Ntc * testSensor = new Ntc(config);

    COMPARE_F(testSensor->getCoefficients().A, A, COEFF_DELTA);
    COMPARE_F(testSensor->getCoefficients().B, B, COEFF_DELTA);
    COMPARE_F(testSensor->getCoefficients().C, C, COEFF_DELTA);

    delete testSensor;
}

void NtcTest::testNtcConstructor_data() {
    QTest::addColumn<qreal>("t1");
    QTest::addColumn<qreal>("r1");
    QTest::addColumn<qreal>("t2");
    QTest::addColumn<qreal>("r2");
    QTest::addColumn<qreal>("t3");
    QTest::addColumn<qreal>("r3");
    QTest::addColumn<int>("units");
    QTest::addColumn<int>("type");

    /* coefficients were generated independently using :
    * https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
    **/
    QTest::addColumn<qreal>("A");
    QTest::addColumn<qreal>("B");
    QTest::addColumn<qreal>("C");

    // make up some NTCs
    QTest::newRow("2C-30k|25C-10k|100C-300R")
            << 2.0 << 30000.0
            << 25.0 << 10000.0
            << 100.0 << 300.0
            << static_cast<int>(Units::TemperatureUnits::CELSIUS)
            << static_cast<int>(SensorConfig::TemperatureSensorType::COOLANT)
            << 2.007961057e-3 << 1.001723351e-4 << 5.419494308e-7;

    QTest::newRow("1C-29.5k|25C-10k|37C-6.2k")
            << 1.0 << 29500.0
            << 25.0 << 10000.0
            << 37.0 << 6200.0
            << static_cast<int>(Units::TemperatureUnits::CELSIUS)
            << static_cast<int>(SensorConfig::TemperatureSensorType::COOLANT)
            << 0.8521912125e-3 << 2.717226313e-4 << -0.01065764181e-7;

    QTest::newRow("0C-9.6k|37C-1.6k|100C-185R")
            << 0.0 << 9600.0
            << 37.0 << 1600.0
            << 100.0 << 185.0
            << static_cast<int>(Units::TemperatureUnits::CELSIUS)
            << static_cast<int>(SensorConfig::TemperatureSensorType::COOLANT)
            << 1.314314314e-3 << 2.643027107e-4 << -0.9968011359e-7;
}


void NtcTest::testCalculateTemperature() {
    QFETCH(qreal, t1);
    QFETCH(qreal, t2);
    QFETCH(qreal, t3);
    QFETCH(qreal, r1);
    QFETCH(qreal, r2);
    QFETCH(qreal, r3);
    QFETCH(int, units);
    QFETCH(int, type);
    QFETCH(qreal, test_temp_C);
    QFETCH(qreal, test_input);

    // Assemble the config structure
    SensorConfig::TempSensorConfig config;
    config.r1 = r1;
    config.r2 = r2;
    config.r3 = r3;
    config.t1 = t1;
    config.t2 = t2;
    config.t3 = t3;
    config.rBalance = NtcTest::rBalance;
    config.vSupply = NtcTest::vSupply;
    config.type = static_cast<SensorConfig::TemperatureSensorType>(type);
    config.units = static_cast<Units::TemperatureUnits>(units);

    // make new object
    Ntc * testSensor = new Ntc(config);

    COMPARE_F(testSensor->calculateTemp(test_input, Units::TemperatureUnits::CELSIUS),
              test_temp_C,
              TEMP_DELTA);

    delete testSensor;
}

void NtcTest::testCalculateTemperature_data() {
    QTest::addColumn<qreal>("t1");
    QTest::addColumn<qreal>("r1");
    QTest::addColumn<qreal>("t2");
    QTest::addColumn<qreal>("r2");
    QTest::addColumn<qreal>("t3");
    QTest::addColumn<qreal>("r3");
    QTest::addColumn<int>("units");
    QTest::addColumn<int>("type");
    QTest::addColumn<qreal>("test_temp_C");
    QTest::addColumn<qreal>("test_input");

    // make up some NTCs
    QTest::newRow("2C-30k|25C-10k|100C-300R")
            << 2.0 << 30000.0
            << 25.0 << 10000.0
            << 100.0 << 300.0
            << static_cast<int>(Units::TemperatureUnits::CELSIUS)
            << static_cast<int>(SensorConfig::TemperatureSensorType::COOLANT)
            << 65.5439 << NtcTest::vSupply * (1500 / (NtcTest::rBalance + 1500));
}
