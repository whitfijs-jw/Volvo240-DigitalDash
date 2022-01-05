#ifndef MAP_TEST_H
#define MAP_TEST_H

#include <QtTest/QtTest>
#include <QDebug>
#include <map_sensor.h>

class MapTest: public QObject
{
    Q_OBJECT
public:
    static constexpr qreal DELTA = 2.5; //!< Allowable error (in kPa) from table values (which I think are rounded anyway)

private slots:
    void testGetAbsolutePressure();
    void testGetAbsolutePressure_data();
};

#endif // MAP_TEST_H
