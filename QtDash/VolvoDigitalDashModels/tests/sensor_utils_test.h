#ifndef SENSORUTILSTEST_H
#define SENSORUTILSTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <config.h>

class SensorUtilsTest : public QObject
{
    Q_OBJECT
public:

signals:

private slots:
    void test_isAdcVoltageValid();
    void test_isAdcVoltageValid_data();

    void test_getResistance();
    void test_getResistance_data();

    void test_getOptimalBalanceResistor();
    void test_getOptimalBalanceResistor_data();

    void test_toMeters();
    void test_toMeters_data();

    void test_toMiles();
    void test_toMiles_data();

    void test_toFeet();
    void test_toFeet_data();

    void test_convertDistance();
    void test_convertDistance_data();

    void test_toKelvin();
    void test_toKelvin_data();

    void test_toFahrenheit();
    void test_toFahrenheit_data();

    void test_toCelsius();
    void test_toCelsius_data();

    void test_convertTemperature();
    void test_convertTemperature_data();

    void test_toKpa();
    void test_toKpa_data();

    void test_toPsi();
    void test_toPsi_data();

    void test_toBar();
    void test_toBar_data();

    void test_convertPressure();
    void test_convertPressure_data();

    void test_toMph();
    void test_toMph_data();

    void test_toKph();
    void test_toKph_data();

    void test_toMetersPerSecond();
    void test_toMetersPerSecond_data();

    void test_convertSpeed();
    void test_convertSpeed_data();

    void test_convert();
    void test_convert_data();

    void test_interp();
    void test_interp_data();

    void test_polynomialRegression();
    void test_polynomialRegression_data();

    void test_polynomialValue();
    void test_polynomialValue_data();
};

#endif // SENSORUTILSTEST_H
