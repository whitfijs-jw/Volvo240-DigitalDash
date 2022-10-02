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

void SensorUtilsTest::test_toKelvin() {
    QFETCH(qreal, temp);
    QFETCH(qint32, units);
    QFETCH(qreal, kelvin);

    Config::TemperatureUnits unit = static_cast<Config::TemperatureUnits>(units);

    COMPARE_F(SensorUtils::toKelvin(temp, unit), kelvin, 1e-3);
}
void SensorUtilsTest::test_toKelvin_data() {
    QTest::addColumn<qreal>("temp");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("kelvin");

    QTest::addRow("100F | 310.928K ")
        << 100.0
        << static_cast<qint32>(Config::TemperatureUnits::FAHRENHEIT)
        << 310.928;
    QTest::addRow("100K | 100K ")
        << 100.0
        << static_cast<qint32>(Config::TemperatureUnits::KELVIN)
        << 100.0;
    QTest::addRow("76C | 349.15K ")
        << 76.0
        << static_cast<qint32>(Config::TemperatureUnits::CELSIUS)
        << 349.15;
}

void SensorUtilsTest::test_toFahrenheit() {
    QFETCH(qreal, temp);
    QFETCH(qint32, units);
    QFETCH(qreal, fahrenheit);

    Config::TemperatureUnits unit = static_cast<Config::TemperatureUnits>(units);

    COMPARE_F(SensorUtils::toFahrenheit(temp, unit), fahrenheit, 1e-3);
}
void SensorUtilsTest::test_toFahrenheit_data() {
    QTest::addColumn<qreal>("temp");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("fahrenheit");

    QTest::addRow("100F | 100F ")
        << 100.0
        << static_cast<qint32>(Config::TemperatureUnits::FAHRENHEIT)
        << 100.0;
    QTest::addRow("57K | -357.07F ")
        << 57.0
        << static_cast<qint32>(Config::TemperatureUnits::KELVIN)
        << -357.07;
    QTest::addRow("38C | 100.4F ")
        << 38.0
        << static_cast<qint32>(Config::TemperatureUnits::CELSIUS)
        << 100.4;
}

void SensorUtilsTest::test_toCelsius() {
    QFETCH(qreal, temp);
    QFETCH(qint32, units);
    QFETCH(qreal, celsius);

    Config::TemperatureUnits unit = static_cast<Config::TemperatureUnits>(units);

    COMPARE_F(SensorUtils::toCelsius(temp, unit), celsius, 1e-3);
}
void SensorUtilsTest::test_toCelsius_data() {
    QTest::addColumn<qreal>("temp");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("celsius");

    QTest::addRow("183F | 83.8889C ")
        << 183.0
        << static_cast<qint32>(Config::TemperatureUnits::FAHRENHEIT)
        << 83.8889;
    QTest::addRow("380K | 106.85C ")
        << 380.0
        << static_cast<qint32>(Config::TemperatureUnits::KELVIN)
        << 106.85;
    QTest::addRow("38C | 38C ")
        << 38.0
        << static_cast<qint32>(Config::TemperatureUnits::CELSIUS)
        << 38.0;
}

void SensorUtilsTest::test_convertTemperature() {
    QFETCH(qreal, temp);
    QFETCH(qint32, to);
    QFETCH(qint32, from);
    QFETCH(qreal, convertedTemperature);

    Config::TemperatureUnits toUnits = static_cast<Config::TemperatureUnits>(to);
    Config::TemperatureUnits fromUnits = static_cast<Config::TemperatureUnits>(from);

    COMPARE_F(SensorUtils::convertTemperature(temp, toUnits, fromUnits), convertedTemperature, 1e-3);
}
void SensorUtilsTest::test_convertTemperature_data() {
    QTest::addColumn<qreal>("temp");
    QTest::addColumn<qint32>("to");
    QTest::addColumn<qint32>("from");
    QTest::addColumn<qreal>("convertedTemperature");

    QTest::addRow("183F to C | 83.8889C ")
        << 183.0
        << static_cast<qint32>(Config::TemperatureUnits::CELSIUS)
        << static_cast<qint32>(Config::TemperatureUnits::FAHRENHEIT)
        << 83.8889;
    QTest::addRow("57K to F | -357.07F ")
        << 57.0
        << static_cast<qint32>(Config::TemperatureUnits::FAHRENHEIT)
        << static_cast<qint32>(Config::TemperatureUnits::KELVIN)
        << -357.07;
    QTest::addRow("380K to C | 106.85C ")
        << 380.0
        << static_cast<qint32>(Config::TemperatureUnits::CELSIUS)
        << static_cast<qint32>(Config::TemperatureUnits::KELVIN)
        << 106.85;
}

void SensorUtilsTest::test_toKpa() {
    QFETCH(qreal, pressure);
    QFETCH(qint32, units);
    QFETCH(qreal, kpa);

    Config::PressureUnits unit = static_cast<Config::PressureUnits>(units);

    COMPARE_F(SensorUtils::toKpa(pressure, unit), kpa, 1e-3);
}
void SensorUtilsTest::test_toKpa_data() {
    QTest::addColumn<qreal>("pressure");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("kpa");

    QTest::addRow("14 psi | 96.5266 kPa")
        << 14.0 << static_cast<qint32>(Config::PressureUnits::PSI) << 96.5266;
    QTest::addRow("2 bar | 200 kPa")
        << 2.0 << static_cast<qint32>(Config::PressureUnits::BAR) << 200.0;
    QTest::addRow("300 kPa | 300 kPa")
        << 300.0 << static_cast<qint32>(Config::PressureUnits::KPA) << 300.0;
}

void SensorUtilsTest::test_toPsi() {
    QFETCH(qreal, pressure);
    QFETCH(qint32, units);
    QFETCH(qreal, psi);

    Config::PressureUnits unit = static_cast<Config::PressureUnits>(units);

    COMPARE_F(SensorUtils::toPsi(pressure, unit), psi, 1e-3);
}
void SensorUtilsTest::test_toPsi_data() {
    QTest::addColumn<qreal>("pressure");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("psi");

    QTest::addRow("14 psi | 14 psi")
        << 14.0 << static_cast<qint32>(Config::PressureUnits::PSI) << 14.0;
    QTest::addRow("1.5 bar | 21.7557 psi")
        << 1.5 << static_cast<qint32>(Config::PressureUnits::BAR) << 21.7557;
    QTest::addRow("48 kPa | 6.96181 psi")
        << 48.0 << static_cast<qint32>(Config::PressureUnits::KPA) << 6.96181;
}

void SensorUtilsTest::test_toBar() {
    QFETCH(qreal, pressure);
    QFETCH(qint32, units);
    QFETCH(qreal, bar);

    Config::PressureUnits unit = static_cast<Config::PressureUnits>(units);

    COMPARE_F(SensorUtils::toBar(pressure, unit), bar, 1e-3);
}
void SensorUtilsTest::test_toBar_data() {
    QTest::addColumn<qreal>("pressure");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("bar");

    QTest::addRow("10 psi | 0.689476 bar")
        << 10.0 << static_cast<qint32>(Config::PressureUnits::PSI) << 0.689476;
    QTest::addRow("1.5 bar | 1.5 bar")
        << 1.5 << static_cast<qint32>(Config::PressureUnits::BAR) << 1.5;
    QTest::addRow("57 kPa | .57 bar")
        << 57.0 << static_cast<qint32>(Config::PressureUnits::KPA) << 0.57;
}

void SensorUtilsTest::test_convertPressure() {
    QFETCH(qreal, pressure);
    QFETCH(qint32, to);
    QFETCH(qint32, from);
    QFETCH(qreal, convertedPressure);

    Config::PressureUnits toUnits = static_cast<Config::PressureUnits>(to);
    Config::PressureUnits fromUnits = static_cast<Config::PressureUnits>(from);

    COMPARE_F(SensorUtils::convertPressure(pressure, toUnits, fromUnits), convertedPressure, 1e-3);
}
void SensorUtilsTest::test_convertPressure_data() {
    QTest::addColumn<qreal>("pressure");
    QTest::addColumn<qint32>("to");
    QTest::addColumn<qint32>("from");
    QTest::addColumn<qreal>("convertedPressure");

    QTest::addRow("48 kPa to psi| 6.96181 psi")
        << 48.0
        << static_cast<qint32>(Config::PressureUnits::PSI)
        << static_cast<qint32>(Config::PressureUnits::KPA)
        << 6.96181;
    QTest::addRow("2 bar to kPa | 200 kPa")
        << 2.0
        << static_cast<qint32>(Config::PressureUnits::KPA)
        << static_cast<qint32>(Config::PressureUnits::BAR)
        << 200.0;
    QTest::addRow("10 psi to bar | 0.689476 bar")
        << 10.0
        << static_cast<qint32>(Config::PressureUnits::BAR)
        << static_cast<qint32>(Config::PressureUnits::PSI)
        << 0.689476;
}

void SensorUtilsTest::test_toMph() {
    QFETCH(qreal, speed);
    QFETCH(qint32, units);
    QFETCH(qreal, mph);

    Config::SpeedUnits unit = static_cast<Config::SpeedUnits>(units);

    COMPARE_F(SensorUtils::toMph(speed, unit), mph, 1.0e-3);
}
void SensorUtilsTest::test_toMph_data() {
    QTest::addColumn<qreal>("speed");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("mph");

    QTest::addRow("100 kph | 62mph ")
        << 100.0 << static_cast<qint32>(Config::SpeedUnits::KPH) << 62.137;
    QTest::addRow("14 m/s | 31.3171 mph ")
        << 14.0 << static_cast<qint32>(Config::SpeedUnits::METER_PER_SECOND) << 31.3171;
    QTest::addRow("34 mph | 34 mph ")
        << 34.0 << static_cast<qint32>(Config::SpeedUnits::MPH) << 34.0;
}

void SensorUtilsTest::test_toKph() {
    QFETCH(qreal, speed);
    QFETCH(qint32, units);
    QFETCH(qreal, kph);

    Config::SpeedUnits unit = static_cast<Config::SpeedUnits>(units);

    COMPARE_F(SensorUtils::toKph(speed, unit), kph, 1.0e-3);
}
void SensorUtilsTest::test_toKph_data() {
    QTest::addColumn<qreal>("speed");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("kph");

    QTest::addRow("100 kph | 100 kph ")
        << 100.0 << static_cast<qint32>(Config::SpeedUnits::KPH) << 100.0;
    QTest::addRow("18.1 m/s | 65.16 kph ")
        << 18.1 << static_cast<qint32>(Config::SpeedUnits::METER_PER_SECOND) << 65.16;
    QTest::addRow("34 mph | 54.7177 kph ")
        << 34.0 << static_cast<qint32>(Config::SpeedUnits::MPH) << 54.7177;
}

void SensorUtilsTest::test_toMetersPerSecond() {
    QFETCH(qreal, speed);
    QFETCH(qint32, units);
    QFETCH(qreal, mps);

    Config::SpeedUnits unit = static_cast<Config::SpeedUnits>(units);

    COMPARE_F(SensorUtils::toMetersPerSecond(speed, unit), mps, 1.0e-3);
}
void SensorUtilsTest::test_toMetersPerSecond_data() {
    QTest::addColumn<qreal>("speed");
    QTest::addColumn<qint32>("units");
    QTest::addColumn<qreal>("mps");

    QTest::addRow("25.6 kph | 7.111111 m/s ")
        << 25.6 << static_cast<qint32>(Config::SpeedUnits::KPH) << 7.111111;
    QTest::addRow("18.1 m/s | 18.1 m/s ")
        << 18.1 << static_cast<qint32>(Config::SpeedUnits::METER_PER_SECOND) << 18.1;
    QTest::addRow("24 mph | 10.729 m/s ")
        << 24.0 << static_cast<qint32>(Config::SpeedUnits::MPH) << 10.729;
}

void SensorUtilsTest::test_convertSpeed() {
    QFETCH(qreal, speed);
    QFETCH(qint32, to);
    QFETCH(qint32, from);
    QFETCH(qreal, convertedSpeed);

    Config::SpeedUnits toUnits = static_cast<Config::SpeedUnits>(to);
    Config::SpeedUnits fromUnits = static_cast<Config::SpeedUnits>(from);

    COMPARE_F(SensorUtils::convertSpeed(speed, toUnits, fromUnits), convertedSpeed, 1.0e-3);
}
void SensorUtilsTest::test_convertSpeed_data() {
    QTest::addColumn<qreal>("speed");
    QTest::addColumn<qint32>("to");
    QTest::addColumn<qint32>("from");
    QTest::addColumn<qreal>("convertedSpeed");

    QTest::addRow("25.6 kph to m/s | 7.111111 m/s ")
        << 25.6
        << static_cast<qint32>(Config::SpeedUnits::METER_PER_SECOND)
        << static_cast<qint32>(Config::SpeedUnits::KPH)
        << 7.111111;
    QTest::addRow("34 mph to kph| 54.7177 kph ")
        << 34.0
        << static_cast<qint32>(Config::SpeedUnits::KPH)
        << static_cast<qint32>(Config::SpeedUnits::MPH)
        << 54.7177;
    QTest::addRow("18.1 m/s to kph | 65.16 kph ")
        << 18.1
        << static_cast<qint32>(Config::SpeedUnits::KPH)
        << static_cast<qint32>(Config::SpeedUnits::METER_PER_SECOND)
        << 65.16;
}

void SensorUtilsTest::test_convert() {
    QFETCH(qreal, value);
    QFETCH(QString, to);
    QFETCH(QString, from);
    QFETCH(qreal, convertedValue);

    COMPARE_F(SensorUtils::convert(value, to, from), convertedValue, 1.0e-3);
}
void SensorUtilsTest::test_convert_data() {
    QTest::addColumn<qreal>("value");
    QTest::addColumn<QString>("to");
    QTest::addColumn<QString>("from");
    QTest::addColumn<qreal>("convertedValue");

    // Pressure
    QTest::addRow("14 psi to kPa | 96.5266 kPa")
        << 14.0
        << Config::UNITS_KPA
        << Config::UNITS_PSI
        << 96.5266;
    // change case of inputs
    QTest::addRow("14 psi to kPa (case change) | 96.5266 kPa")
        << 14.0
        << QString(Config::UNITS_KPA).toUpper()
        << QString(Config::UNITS_PSI).toLower()
        << 96.5266;
    QTest::addRow("10 psi to bar | 0.689476 bar")
        << 10.0
        << Config::UNITS_BAR
        << Config::UNITS_PSI
        << 0.689476;
    QTest::addRow("10 psi to bar (case change) | 0.689476 bar")
        << 10.0
        << QString(Config::UNITS_BAR).toUpper()
        << QString(Config::UNITS_PSI).toUpper()
        << 0.689476;

    // Temperature
    QTest::addRow("183F to C | 83.8889C ")
        << 183.0
        << QString(Config::UNITS_C).toLower()
        << QString(Config::UNITS_F).toUpper()
        << 83.8889;
    QTest::addRow("57K to F | -357.07F ")
        << 57.0
        << QString(Config::UNITS_F).toLower()
        << QString(Config::UNITS_K).toUpper()
        << -357.07;
    QTest::addRow("380K to C | 106.85C ")
        << 380.0
        << QString(Config::UNITS_C).toUpper()
        << QString(Config::UNITS_K).toUpper()
        << 106.85;
}

void SensorUtilsTest::test_interp() {
    QFETCH(qreal, x);
    QFETCH(qreal, x0);
    QFETCH(qreal, y0);
    QFETCH(qreal, x1);
    QFETCH(qreal, y1);
    QFETCH(qreal, y);

    COMPARE_F(SensorUtils::interp(x, x0, y0, x1, y1), y, 1.0e-3);
}
void SensorUtilsTest::test_interp_data() {
    QTest::addColumn<qreal>("x");
    QTest::addColumn<qreal>("x0");
    QTest::addColumn<qreal>("y0");
    QTest::addColumn<qreal>("x1");
    QTest::addColumn<qreal>("y1");
    QTest::addColumn<qreal>("y");

    QTest::addRow("1.0 | (0.0, 0.0), (2.0, 2.0) | 1.0")
            << 1.0
            << 0.0 << 0.0
            << 2.0 << 2.0
            << 1.0;
    QTest::addRow("3.0 | (-1.0, 1.0), (5.0, 12.0) | 8.3333")
            << 3.0
            << -1.0 << 1.0
            << 5.0 << 12.0
            << 8.333;
    QTest::addRow("180.0 | (150.0, 2100.0), (210.0, 200.0) | 1150.0")
            << 180.0
            << 150.0 << 2100.0
            << 210.0 << 200.0
            << 1150.0;
}

void SensorUtilsTest::test_polynomialRegression() {
    QFETCH(QList<qreal>, x);
    QFETCH(QList<qreal>, y);
    QFETCH(qint32, order);
    QFETCH(QList<qreal>, coeff);

    QList<qreal> calculatedCoeff = SensorUtils::polynomialRegression(x, y, order);

    for (int i = 0; i < calculatedCoeff.size(); i++) {
        COMPARE_F(calculatedCoeff[i], coeff[i], 1e-3);
    }
}
void SensorUtilsTest::test_polynomialRegression_data() {
    QTest::addColumn<QList<qreal>>("x");
    QTest::addColumn<QList<qreal>>("y");
    QTest::addColumn<qint32>("order");
    QTest::addColumn<QList<qreal>>("coeff");

    QList<qreal> x = {1.0, 2.0, 3.0, 4.0};
    QList<qreal> y = {2.0, 3.0, 4.0, 5.0};
    QList<qreal> coeff {1.0, 1.0};
    QTest::addRow("first order fit")
            << x << y << 1 << coeff;


    QList<qreal> x1 = {10.0,48.0,82.0,116.0,184.0};
    QList<qreal> y1 = {0.0,1.0,2.0,3.0,5.0};
    QList<qreal> coeff1 = {-0.246228917, 0.023918711, 0.000053419, -0.000000155};
    QTest::addRow("cubic fit (oil pressure sensor)")
            << x1 << y1 << 3 << coeff1;
}

void SensorUtilsTest::test_polynomialValue() {
    QFETCH(qreal, x);
    QFETCH(QList<qreal>, coeff);
    QFETCH(qreal, output);

    COMPARE_F(SensorUtils::polynomialValue(x, coeff), output, 1e-3);
}
void SensorUtilsTest::test_polynomialValue_data() {
    QTest::addColumn<qreal>("x");
    QTest::addColumn<QList<qreal>>("coeff");
    QTest::addColumn<qreal>("output");

    QList<qreal> coeff2 = {5.0, 1.5, 0.1};
    QTest::addRow("5.0x^2 + 1.5x + 0.1 | x = 2.4 | y = 9.1760")
            << 2.4 << coeff2 << 9.1760;

    QList<qreal> coeff3 = {1.4, 0.5, 4.0, 100.4};
    QTest::addRow("1.4x^3 + 0.5x^2 + 4.0x + 100.4 | x = 0.25 | y = 9.1760")
            << 0.25 << coeff3 << 3.3438;
}
