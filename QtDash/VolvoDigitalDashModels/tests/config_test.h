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
    void testLoadDashLightConfig();
    void testLoadDashLightConfig_data();
};

#endif // CONFIG_TEST_H
