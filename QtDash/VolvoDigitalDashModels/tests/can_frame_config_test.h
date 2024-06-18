#ifndef CANFRAMECONFIGTEST_H
#define CANFRAMECONFIGTEST_H

#include <QtTest/QtTest>
#include <QObject>

class CanFrameConfigTest : public QObject
{
    Q_OBJECT
private slots:
    void testLoadValidConfig();
    void testLoadValidConfig_data();
};

#endif // CANFRAMECONFIGTEST_H
