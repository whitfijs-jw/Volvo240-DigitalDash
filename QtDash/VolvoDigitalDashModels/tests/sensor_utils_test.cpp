#include "sensor_utils_test.h"
#include "sensor_utils.h"
#include <compare_float.h>

void SensorUtilsTest::test_isAdcVoltageValid() {
    QFETCH(qreal, voltage);
    QFETCH(qreal, vsupply);
    QFETCH(bool, isValid);

    QCOMPARE(SensorUtils::isValid(voltage, vsupply), isValid);
}
void SensorUtilsTest::test_isAdcVoltageValid_data() {
    // inputs
    QTest::addColumn<qreal>("voltage");
    QTest::addColumn<qreal>("vsupply");

    // output
    QTest::addColumn<bool>("isValid");


    // test data
    QTest::addRow("2.5Vin | 5.0Vsupply")
        << 2.5 << 5.0 << true;

    QTest::addRow("5.0Vin | 5.0Vsupply -- (floating input)")
        << 5.0 << 5.0 << false;

    QTest::addRow("0.0Vin | 5.0Vsupply -- (shorted input)")
        << 0.0 << 5.0 << false;

    QTest::addRow("2.5Vin | 3.3Vsupply")
        << 2.5 << 3.3 << true;

    QTest::addRow("5.0Vin | 3.3Vsupply -- (overvoltage)")
        << 5.0 << 3.3 << false;

}

void SensorUtilsTest::test_getResistance() {
    QFETCH(qreal, voltage);
    QFETCH(qreal, vsupply);
    QFETCH(qreal, rBalance);
    QFETCH(qreal, resistance);

    COMPARE_F(SensorUtils::getResistance(voltage, vsupply, rBalance), resistance, 1e-3);
}
void SensorUtilsTest::test_getResistance_data() {
    QTest::addColumn<qreal>("voltage");
    QTest::addColumn<qreal>("vsupply");
    QTest::addColumn<qreal>("rBalance");
    QTest::addColumn<qreal>("resistance");

    QTest::addRow("3.0Vin | 3.3VSupply | 10 ohm rBalance | 100 ohm resistance out")
        << 3.00000 << 3.3 << 10.0 << 100.0;
    QTest::addRow("2.7Vin | 3.3VSupply | 100 ohm rBalance | 450 ohm resistance out")
        << 2.7 << 3.3 << 100.0 << 450.0;
    QTest::addRow("2.5Vin | 3.3VSupply | 1k ohm rBalance | 3125 ohm resistance out")
        << 2.5 << 3.3 << 1.0e3 << 3125.0;
    QTest::addRow("2.3Vin | 3.3VSupply | 10k ohm rBalance | 23k ohm resistance out")
        << 2.3 << 3.3 << 1.0e4 << 23000.0;
    QTest::addRow("2.1Vin | 3.3VSupply | 100k ohm rBalance | 175k ohm resistance out")
        << 2.1 << 3.3 << 1.0e5 << 175000.0;
    QTest::addRow("1.9Vin | 3.3VSupply | 1M ohm rBalance | 1357142.85714 ohm resistance out")
        << 1.9 << 3.3 << 1.0e6 << 1357142.85714;
    QTest::addRow("3.3Vin | 3.3VSupply | 1k ohm rBalance | INVALID resistance out")
        << 3.3 << 3.3 << 1.0e3 << SensorUtils::INVALID_RESISTANCE;
    QTest::addRow("0.0Vin | 3.3VSupply | 1k ohm rBalance | INVALID resistance out")
        << 0.0 << 3.3 << 1.0e3 << SensorUtils::INVALID_RESISTANCE;
}

void SensorUtilsTest::test_getOptimalBalanceResistor() {
    QFETCH(qreal, rLow);
    QFETCH(qreal, rHigh);
    QFETCH(qreal, optimalResistance);

    COMPARE_F(SensorUtils::estimateOptimalBalanceResistor(rLow, rHigh), optimalResistance, 1e-1);
}
void SensorUtilsTest::test_getOptimalBalanceResistor_data() {
    QTest::addColumn<qreal>("rLow");
    QTest::addColumn<qreal>("rHigh");
    QTest::addColumn<qreal>("optimalResistance");

    QTest::addRow("100 ohm rLow | 100 ohm rHigh | 100 ohm output")
        << 100.0 << 100.0 << 100.0;
    QTest::addRow("100 ohm rLow | 1000 ohm rHigh | 316.228 ohm output")
        << 100.0 << 1000.0 << 316.2278;
    QTest::addRow("100 ohm rLow | 1000 ohm rHigh | 316.228 ohm output")
        << 100.0 << 1000.0 << 316.2278;
    QTest::addRow("220 ohm rLow | 2100 ohm rHigh | 679.71 ohm output")
        << 220.0 << 2100.0 << 679.7058;
    QTest::addRow("0 ohm rLow | 2100 ohm rHigh | INVALID ohm output")
        << 0.0 << 2100.0 << SensorUtils::INVALID_RESISTANCE;
    QTest::addRow("220 ohm rLow | 0 ohm rHigh | INVALID ohm output")
        << 220.0 << 0.0 << SensorUtils::INVALID_RESISTANCE;
}

void SensorUtilsTest::test_toMeters() {
    QFETCH(qreal, distance);
    QFETCH(qint32, units);
    QFETCH(qreal, meters);

    Config::DistanceUnits unit = static_cast<Config::DistanceUnits>(units);

    COMPARE_F(SensorUtils::toMeters(distance, unit), meters, 1e-3);
}
void SensorUtilsTest::test_toMeters_data() {
    QTest::addColumn<qreal>("distance");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("meters");

    QTest::addRow("1000 mm | 1 m ")
        << 1000.0 << static_cast<qint32>(Config::DistanceUnits::MILLIMETER) << 1.0;
    QTest::addRow("10 cm | .1 m ")
        << 10.0 << static_cast<qint32>(Config::DistanceUnits::CENTIMETER) << 0.1;
    QTest::addRow("10 m | 10 m ")
        << 10.0 << static_cast<qint32>(Config::DistanceUnits::METER) << 10.0;
    QTest::addRow("10 km | 10000 m ")
        << 10.0 << static_cast<qint32>(Config::DistanceUnits::KILOMETER) << 10000.0;
    QTest::addRow("10 inch | 0.254 m ")
        << 10.0 << static_cast<qint32>(Config::DistanceUnits::INCH) << 0.254;
    QTest::addRow("1 foot | 0.3048 m ")
        << 1.0 << static_cast<qint32>(Config::DistanceUnits::FOOT) << 0.3048;
    QTest::addRow("12 yard | 10.9728 m ")
        << 12.0 << static_cast<qint32>(Config::DistanceUnits::YARD) << 10.9728;
    QTest::addRow("12 miles | 19312.1 m ")
        << 12.0 << static_cast<qint32>(Config::DistanceUnits::MILE) << 19312.1280;

}

void SensorUtilsTest::test_toMiles() {
    QFETCH(qreal, distance);
    QFETCH(qint32, units);
    QFETCH(qreal, miles);

    Config::DistanceUnits unit = static_cast<Config::DistanceUnits>(units);

    COMPARE_F(SensorUtils::toMiles(distance, unit), miles, 1e-3);
}
void SensorUtilsTest::test_toMiles_data() {
    QTest::addColumn<qreal>("distance");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("miles");

    QTest::addRow("1000 mm | 0.000621371 miles ")
        << 1000.0 << static_cast<qint32>(Config::DistanceUnits::MILLIMETER) << 0.000621371;
    QTest::addRow("10 cm | 6.2137e-5 miles ")
        << 10.0 << static_cast<qint32>(Config::DistanceUnits::CENTIMETER) << 6.2137e-5;
    QTest::addRow("46 m | 0.0285831 miles ")
        << 46.0 << static_cast<qint32>(Config::DistanceUnits::METER) << 0.0285831;
    QTest::addRow("13 km | 8.07783 miles ")
        << 13.0 << static_cast<qint32>(Config::DistanceUnits::KILOMETER) << 8.07783;
    QTest::addRow("5028 inch | 0.07935606 miles ")
        << 5028.0 << static_cast<qint32>(Config::DistanceUnits::INCH) << 0.07935606;
    QTest::addRow("1000 feet | 0.189394 miles ")
        << 1000.0 << static_cast<qint32>(Config::DistanceUnits::FOOT) << 0.189394;
    QTest::addRow("1200 yard | 0.6818182 miles ")
        << 1200.0 << static_cast<qint32>(Config::DistanceUnits::YARD) << 0.6818182;
    QTest::addRow("12 miles | 12 miles ")
        << 12.0 << static_cast<qint32>(Config::DistanceUnits::MILE) << 12.0;
}

void SensorUtilsTest::test_toFeet() {
    QFETCH(qreal, distance);
    QFETCH(qint32, units);
    QFETCH(qreal, feet);

    Config::DistanceUnits unit = static_cast<Config::DistanceUnits>(units);

    COMPARE_F(SensorUtils::toFeet(distance, unit), feet, 1e-3);
}
void SensorUtilsTest::test_toFeet_data() {
    QTest::addColumn<qreal>("distance");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("feet");

    QTest::addRow("1000 mm | 3.28084 feet ")
        << 1000.0 << static_cast<qint32>(Config::DistanceUnits::MILLIMETER) << 3.28084;
    QTest::addRow("56 cm | 1.83727 feet ")
        << 56.0 << static_cast<qint32>(Config::DistanceUnits::CENTIMETER) << 1.83727;
    QTest::addRow("46 m | 150.919 feet ")
        << 46.0 << static_cast<qint32>(Config::DistanceUnits::METER) << 150.919;
    QTest::addRow(".5028 km | 1649.6063 feet ")
        << 0.5028 << static_cast<qint32>(Config::DistanceUnits::KILOMETER) << 1649.6063;
    QTest::addRow("5028 inch | 419 feet ")
        << 5028.0 << static_cast<qint32>(Config::DistanceUnits::INCH) << 419.0;
    QTest::addRow("28 feet | 28 feet ")
        << 28.0 << static_cast<qint32>(Config::DistanceUnits::FOOT) << 28.0;
    QTest::addRow("13 yard | 39 feet ")
        << 13.0 << static_cast<qint32>(Config::DistanceUnits::YARD) << 39.0;
    QTest::addRow("1.25 miles | 6600 feet ")
        << 1.250 << static_cast<qint32>(Config::DistanceUnits::MILE) << 6600.0;
}

void SensorUtilsTest::test_convertDistance() {
    QFETCH(qreal, distance);
    QFETCH(qint32, to);
    QFETCH(qint32, from);
    QFETCH(qreal, convertedDistance);

    Config::DistanceUnits toUnits = static_cast<Config::DistanceUnits>(to);
    Config::DistanceUnits fromUnits = static_cast<Config::DistanceUnits>(from);

    COMPARE_F(SensorUtils::convertDistance(distance, toUnits, fromUnits), convertedDistance, 1e-3);
}
void SensorUtilsTest::test_convertDistance_data() {
    QTest::addColumn<qreal>("distance");
    QTest::addColumn<qint32>("to");
    QTest::addColumn<qint32>("from");
    QTest::addColumn<qreal>("convertedDistance");

    QTest::addRow("12 yards to meter | 10.9728 m ")
        << 12.0
        << static_cast<qint32>(Config::DistanceUnits::METER)
        << static_cast<qint32>(Config::DistanceUnits::YARD)
        << 10.9728;
    QTest::addRow("1.25 miles to feet | 6600 feet ")
        << 1.250
        << static_cast<qint32>(Config::DistanceUnits::FOOT)
        << static_cast<qint32>(Config::DistanceUnits::MILE)
        << 6600.0;
    QTest::addRow("13 km to miles | 8.07783 miles ")
        << 13.0
        << static_cast<qint32>(Config::DistanceUnits::MILE)
        << static_cast<qint32>(Config::DistanceUnits::KILOMETER)
        << 8.07783;
    QTest::addRow("5028 inch to inch | 419 feet ")
        << 5028.0
        << static_cast<qint32>(Config::DistanceUnits::FOOT)
        << static_cast<qint32>(Config::DistanceUnits::INCH)
        << 419.0;
}

void SensorUtilsTest::test_toKelvin() {}
void SensorUtilsTest::test_toKelvin_data() {}

void SensorUtilsTest::test_toFahrenheit() {}
void SensorUtilsTest::test_toFahrenheit_data() {}

void SensorUtilsTest::test_toCelsius() {}
void SensorUtilsTest::test_toCelsius_data() {}

void SensorUtilsTest::test_convertTemperature() {}
void SensorUtilsTest::test_convertTemperature_data() {}

void SensorUtilsTest::test_toKpa() {}
void SensorUtilsTest::test_toKpa_data() {}

void SensorUtilsTest::test_toPsi() {}
void SensorUtilsTest::test_toPsi_data() {}

void SensorUtilsTest::test_toBar() {}
void SensorUtilsTest::test_toBar_data() {}

void SensorUtilsTest::test_convertPressure() {}
void SensorUtilsTest::test_convertPressure_data() {}

void SensorUtilsTest::test_toMph() {}
void SensorUtilsTest::test_toMph_data() {}

void SensorUtilsTest::test_toKph() {}
void SensorUtilsTest::test_toKph_data() {}

void SensorUtilsTest::test_toMetersPerSecond() {}
void SensorUtilsTest::test_toMetersPerSecond_data() {}

void SensorUtilsTest::test_convertSpeed() {}
void SensorUtilsTest::test_convertSpeed_data() {}

void SensorUtilsTest::test_convert() {}
void SensorUtilsTest::test_convert_data() {}

void SensorUtilsTest::test_interp() {}
void SensorUtilsTest::test_interp_data() {}

void SensorUtilsTest::test_polynomialRegression() {}
void SensorUtilsTest::test_polynomialRegression_data() {}

void SensorUtilsTest::test_polynomialValue() {}
void SensorUtilsTest::test_polynomialValue_data() {}
