#include <config_test.h>

void ConfigTest::testLoadSensorChannelConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);

    Config * testConfig = new Config(this, config);

    QCOMPARE(testConfig->isSensorConfigValid(), result);
}

void ConfigTest::testLoadSensorChannelConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");

    QSettings * dummyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    dummyConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
    dummyConfig->setValue(Config::COOLANT_TEMP_KEY, "");
    dummyConfig->setValue(Config::FUEL_LEVEL_KEY, "");
    dummyConfig->setValue(Config::OIL_PRESSURE_KEY, "");
    dummyConfig->setValue(Config::OIL_TEMP_KEY, "");
    dummyConfig->setValue(Config::MAP_SENSOR_KEY, "");
    dummyConfig->setValue(Config::AMBIENT_TEMP_KEY, "");
    dummyConfig->setValue(Config::DIMMER_VOLTAGE_KEY, "");
    dummyConfig->setValue(Config::FUSE8_12V_KEY, "");
    dummyConfig->endGroup();

    QTest::addRow("empty_config") << "emptyConfig.ini" << false;

    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);

    validConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
    validConfig->setValue(Config::COOLANT_TEMP_KEY, 0);
    validConfig->setValue(Config::FUEL_LEVEL_KEY, 1);
    validConfig->setValue(Config::OIL_PRESSURE_KEY, 2);
    validConfig->setValue(Config::OIL_TEMP_KEY, 3);
    validConfig->setValue(Config::MAP_SENSOR_KEY, 4);
    validConfig->setValue(Config::AMBIENT_TEMP_KEY, 5);
    validConfig->setValue(Config::DIMMER_VOLTAGE_KEY, 6);
    validConfig->setValue(Config::FUSE8_12V_KEY, 7);
    validConfig->endGroup();

    QTest::addRow("valid_config") << "validConfig.ini" << true;


    for (int i = 0; i < 8; i++) {
        QString configName;
        QTextStream(&configName) << "invalidValueConfig" << i << ".ini";
        QSettings * invalidValueConfig = new QSettings(configName, QSettings::IniFormat);

        invalidValueConfig->beginGroup(Config::SENSOR_CHANNEL_GROUP);
        invalidValueConfig->setValue(Config::COOLANT_TEMP_KEY, i == 0 ? -1 : 0);
        invalidValueConfig->setValue(Config::FUEL_LEVEL_KEY,i == 1 ? -1 : 1);
        invalidValueConfig->setValue(Config::OIL_PRESSURE_KEY, i == 2 ? -1 : 2);
        invalidValueConfig->setValue(Config::OIL_TEMP_KEY, i == 3 ? -1 : 3);
        invalidValueConfig->setValue(Config::MAP_SENSOR_KEY, i == 4 ? -1 : 4);
        invalidValueConfig->setValue(Config::AMBIENT_TEMP_KEY, i == 5 ? -1 : 5);
        invalidValueConfig->setValue(Config::DIMMER_VOLTAGE_KEY, i == 6 ? -1 : 6);
        invalidValueConfig->setValue(Config::FUSE8_12V_KEY, i == 7 ? -1 : 7);
        invalidValueConfig->endGroup();

        QTest::addRow(configName.toStdString().c_str()) << configName << false;
    }
 }


void ConfigTest::testLoadDashLightsConfig() {
    QFETCH(QString, config);
    QFETCH(bool, result);

    Config * testConfig = new Config(this, config);

    QCOMPARE(testConfig->isDashLightConfigValid(), result);
}

void ConfigTest::testLoadDashLightsConfig_data() {
    QTest::addColumn<QString>("config");
    QTest::addColumn<bool>("result");

    QSettings * emptyConfig = new QSettings("emptyConfig.ini", QSettings::IniFormat);

    emptyConfig->beginGroup(Config::DASH_LIGHT_GROUP);
    emptyConfig->setValue(Config::OIL_PRESSURE_SW_KEY, "");
    emptyConfig->setValue(Config::OD_LAMP_KEY, "");
    emptyConfig->setValue(Config::HIGH_BEAM_KEY, "");
    emptyConfig->setValue(Config::BRAKE_FAILURE_KEY, "");
    emptyConfig->setValue(Config::BULB_FAILURE_KEY, "");
    emptyConfig->setValue(Config::CHARGING_LIGHT_KEY, "");
    emptyConfig->setValue(Config::BLINKER_LEFT_KEY, "");
    emptyConfig->setValue(Config::BLINKER_RIGHT_KEY, "");
    emptyConfig->setValue(Config::OD_LAMP_AUTO, "");
    emptyConfig->setValue(Config::CHECK_ENGINE_KEY, "");
    emptyConfig->setValue(Config::CONN_32_PIN3, "");
    emptyConfig->endGroup();

    QTest::addRow("empty_config") << "emptyConfig.ini" << false;

    QSettings * validConfig = new QSettings("validConfig.ini", QSettings::IniFormat);

    validConfig->beginGroup(Config::DASH_LIGHT_GROUP);
    validConfig->setValue(Config::OIL_PRESSURE_SW_KEY, 0);
    validConfig->setValue(Config::OD_LAMP_KEY, 1);
    validConfig->setValue(Config::HIGH_BEAM_KEY, 2);
    validConfig->setValue(Config::BRAKE_FAILURE_KEY, 3);
    validConfig->setValue(Config::BULB_FAILURE_KEY, 4);
    validConfig->setValue(Config::CHARGING_LIGHT_KEY, 5);
    validConfig->setValue(Config::BLINKER_LEFT_KEY, 6);
    validConfig->setValue(Config::BLINKER_RIGHT_KEY, 7);
    validConfig->setValue(Config::OD_LAMP_AUTO, 8);
    validConfig->setValue(Config::CHECK_ENGINE_KEY, 9);
    validConfig->setValue(Config::CONN_32_PIN3, 10);
    validConfig->endGroup();

    QTest::addRow("valid_config") << "validConfig.ini" << true;
}
