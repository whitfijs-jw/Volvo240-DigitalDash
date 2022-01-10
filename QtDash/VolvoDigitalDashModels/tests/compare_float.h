#ifndef COMPARE_FLOAT_H
#define COMPARE_FLOAT_H

#include <QTest>
#include <QDebug>

static void COMPARE_F(qreal actual, qreal expected, qreal delta) {
    qDebug() << "Actual: " << actual << " Expected: " << expected;
    QVERIFY((actual - delta) <= expected && (actual + delta) >=expected);
}

#endif // COMPARE_FLOAT_H
