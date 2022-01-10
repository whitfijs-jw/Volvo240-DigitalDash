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
};

#endif // CONFIG_TEST_H
