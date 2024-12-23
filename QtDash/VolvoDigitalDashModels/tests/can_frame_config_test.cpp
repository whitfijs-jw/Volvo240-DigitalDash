#include "can_frame_config_test.h"

#include <QSettings>

#include <config.h>
#include <config_keys.h>

void CanFrameConfigTest::testLoadValidConfig() {
    QFETCH(QString, canConfig);
    QFETCH(bool, use);
    QFETCH(int, frame_id);
    QFETCH(int, frame_offset);
    QFETCH(int, frame_data_size);
    QFETCH(bool, frame_signed);
    QFETCH(QString, frame_name);
    QFETCH(QString, frame_units);
    QFETCH(qreal, frame_multiply);
    QFETCH(qreal, frame_divide);
    QFETCH(qreal, frame_add);
    QFETCH(QString, frame_gauge);

    Config * config = new Config(this,
                               "",
                               "",
                               "",
                               canConfig);

    CanFrameConfig * mapConfig = config->getCanFrameConfig(frame_name);
    CanFrameConfig * nullConfig = config->getCanFrameConfig("null");

    if (mapConfig == nullptr) {
        goto exit;
    }
    QCOMPARE(mapConfig->getFrameId(), frame_id);
    QCOMPARE(mapConfig->getOffset(), frame_offset);
    QCOMPARE(mapConfig->getSize(), frame_data_size);
    QCOMPARE(mapConfig->getName(), frame_name);
    QCOMPARE(mapConfig->getUnits(), frame_units);
    QCOMPARE(mapConfig->isSigned(), frame_signed);
    QCOMPARE(mapConfig->getGauge(), frame_gauge);

    QVERIFY(nullConfig == nullptr);

exit:
    delete config;
}

/**
 * @brief CanFrameConfigTest::testLoadValidConfig_data
 *
 *  [start]
    use=false
    [can_frame]
    size=7
    [can_frame/1]
    frame_id=1512
    offset=0
    data_size=2
    signed=true
    name="map"
    units="kPa"
    multiply=1
    divide=10
    add=0
    gauge="boost"
 */

void CanFrameConfigTest::testLoadValidConfig_data() {
    QTest::addColumn<QString>("canConfig");
    QTest::addColumn<bool>("use");
    QTest::addColumn<int>("frame_id");
    QTest::addColumn<int>("frame_offset");
    QTest::addColumn<int>("frame_data_size");
    QTest::addColumn<bool>("frame_signed");
    QTest::addColumn<QString>("frame_name");
    QTest::addColumn<QString>("frame_units");
    QTest::addColumn<qreal>("frame_multiply");
    QTest::addColumn<qreal>("frame_divide");
    QTest::addColumn<qreal>("frame_add");
    QTest::addColumn<QString>("frame_gauge");

    QSettings * validConfig = new QSettings("validCanConfig.ini", QSettings::IniFormat);

    validConfig->beginGroup(ConfigKeys::CAN_CONFIG_START);
    validConfig->setValue(ConfigKeys::CAN_CONFIG_ENABLE, true);
    validConfig->endGroup();

    validConfig->beginGroup(ConfigKeys::CAN_FRAME);
    validConfig->setValue("size", 1);
    validConfig->endGroup();

    validConfig->beginWriteArray(ConfigKeys::CAN_FRAME);
    validConfig->setArrayIndex(0);
    validConfig->setValue(ConfigKeys::CAN_FRAME_ID, 0x05e8);
    validConfig->setValue(ConfigKeys::CAN_FRAME_OFFSET, 0);
    validConfig->setValue(ConfigKeys::CAN_FRAME_SIZE, 2);
    validConfig->setValue(ConfigKeys::CAN_FRAME_SIGNED, true);
    validConfig->setValue(ConfigKeys::CAN_FRAME_NAME, "map");
    validConfig->setValue(ConfigKeys::CAN_FRAME_UNITS, "kpa");
    validConfig->setValue(ConfigKeys::CAN_FRAME_MULTIPLY, 1.0);
    validConfig->setValue(ConfigKeys::CAN_FRAME_DIVIDE, 10.0);
    validConfig->setValue(ConfigKeys::CAN_FRAME_ADD, 0.0);
    validConfig->setValue(ConfigKeys::CAN_FRAME_GAUGE, "boost");
    validConfig->endArray();

    QTest::addRow("valid can config") <<
        "validCanConfig.ini" <<
        true <<
        0x5e8 <<
        0 <<
        2 <<
        true <<
        "map" <<
        "kpa" <<
        1.0 <<
        10.0 <<
        0.0 <<
        "boost";

    delete validConfig;
}
