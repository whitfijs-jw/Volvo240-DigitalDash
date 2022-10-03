#ifndef CONFIG_TEST_H
#define CONFIG_TEST_H

#include <QtTest/QtTest>
#include <QDebug>
#include <config.h>

class ConfigTest: public QObject
{
    Q_OBJECT
public:

private slots:
    void testLoadSensorChannelConfig();
    void testLoadSensorChannelConfig_data();

    void testLoadDashLightsConfig();
    void testLoadDashLightsConfig_data();

    void testLoadMapConfig();
    void testLoadMapConfig_data();

    void testLoadTempSensorConfig();
    void testLoadTempSensorConfig_data();

    void test_getPressureUnits();
    void test_getPressureUnits_data();

    void test_getTemperatureUnits();
    void test_getTemperatureUnits_data();

    void test_getDistanceUnits();
    void test_getDistanceUnits_data();

    void test_getSpeedUnits();
    void test_getSpeedUnits_data();

    void test_loadCanFrameConfig();
    void test_loadCanFrameConfig_data();

    void test_loadOdometerConfig();
    void test_loadOdometerConfig_data();

    void test_writeOdometerConfig();
    void test_writeOdometerConfig_data();

    void test_loadGaugeConfig();
    void test_loadGaugeConfig_data();
};

#endif // CONFIG_TEST_H
