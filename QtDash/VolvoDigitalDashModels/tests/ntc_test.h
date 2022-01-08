#ifndef NTC_TEST_H
#define NTC_TEST_H

#include <QtTest/QtTest>
#include <QDebug>
#include <config.h>

class NtcTest : public QObject
{
    Q_OBJECT

    static constexpr qreal COEFF_DELTA = 1.0e-5;
    static constexpr qreal TEMP_DELTA = 1e-2;

    static constexpr qreal rBalance = 1000;
    static constexpr qreal vSupply = 5.0;

public:

signals:

private slots:
    void testNtcConstructor();
    void testNtcConstructor_data();

    void testCalculateTemperature();
    void testCalculateTemperature_data();
};

#endif // NTC_TEST_H
