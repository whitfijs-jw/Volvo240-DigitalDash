#include "sensor_test.h"
#include "qsignalspy.h"

void SensorTest::initTestCase() {
    Config * testConfig = new Config(this, "validConfig.ini");
    testSource = new TestSource(this->parent(), testConfig, "test");
    testSensor = new TestSensor(this->parent(), testConfig, (SensorSource *)testSource, 0);
    testSensor1 = new TestSensor1(this->parent(), testConfig, (SensorSource *)testSource, 1);
}

void SensorTest::test_sensorSourceConstructor() {
    QCOMPARE(testSource->getNumChannels(), 4);
    QCOMPARE(testSource->getUnits(0), Units::UNITS_FOOT);
    QCOMPARE(testSource->getUnits(1), Units::UNITS_INCH);
    QCOMPARE(testSource->getUnits(2), Units::UNITS_CENTIMETER);
    QCOMPARE(testSource->getUnits(3), Units::UNITS_METER);
    QCOMPARE(testSource->getUnits(10), Units::UNITS_FOOT);

}

void SensorTest::test_sensorConstructor() {
    QCOMPARE(testSensor->getUnits(), "inch");
}

void SensorTest::test_sensor1Constructor() {
    QCOMPARE(testSensor1->getUnits(), "foot");
}

void SensorTest::test_channelUpdate() {
    QSignalSpy spy(testSensor, SIGNAL(sensorDataReady(QVariant)));
    QSignalSpy sourceSpy(testSource, SIGNAL(dataReady(QVariant,int)));
    QSignalSpy spy1(testSensor1, SIGNAL(sensorDataReady(QVariant)));

    //update sensor source
    testSource->update(0);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(sourceSpy.count(), 1);
    QList<QVariant> args = spy.takeFirst();

    // channel 0 -> feet, sensor -> inch
    QCOMPARE(args.at(0).toReal(), 288.0);

    // check source
    args = sourceSpy.takeFirst();
    QCOMPARE(args.at(0), 24.0);
    QCOMPARE(args.at(1), 0);

    testSource->update(1);
    QCOMPARE(spy1.count(), 1);
    args = spy1.takeFirst();

    // channel 1 --> inch, sensor --> feet
    QCOMPARE(args.at(0).toReal(), 2.0);

    // check source
    args = sourceSpy.takeFirst();
    QCOMPARE(args.at(0), 24.0);
    QCOMPARE(args.at(1), 1);
}

void SensorTest::cleanupTestCase() {
    delete(testSource);
    delete(testSensor);
    delete(testSensor1);
}
