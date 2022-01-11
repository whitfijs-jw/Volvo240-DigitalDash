#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QFont>
#include <QFile>
#include <QColor>
#include <QTextStream>
#include <QFontDatabase>
#include <QString>
#include <QtMath>
#include <QList>

#include <QNmeaPositionInfoSource>
#include <QGeoPositionInfoSource>

#include <tachometer_model.h>
#include <accessory_gauge_model.h>
#include <speedometer_model.h>
#include <temp_and_fuel_gauge_model.h>
#include <indicator_model.h>
#include <warning_light_model.h>

#include <config.h>
#include <mcp23017.h>
#include <adc.h>
#include <gps_helper.h>
#include <ntc.h>
#include <map_sensor.h>
#include <tach_input.h>

static TachometerModel tachModel;
static SpeedometerModel speedoModel;
static TempAndFuelGaugeModel tempFuelModel;
static AccessoryGaugeModel oilPressureModel;
static AccessoryGaugeModel oilTemperatureModel;
static AccessoryGaugeModel boostModel;
static AccessoryGaugeModel voltMeterModel;
static AccessoryGaugeModel coolantTempModel;
static AccessoryGaugeModel fuelLevelModel;
static IndicatorModel leftBlinkerModel;
static IndicatorModel rightBlinkerModel;
static WarningLightModel parkingBrakeLightModel;
static WarningLightModel brakeFailureLightModel;
static WarningLightModel bulbFailureLightModel;
static WarningLightModel shiftUpLightModel;
static WarningLightModel highBeamLightModel;
static WarningLightModel srsWarningLightModel;
static WarningLightModel oilWarningLightModel;
static WarningLightModel batteryWarningLightModel;
static WarningLightModel absWarningLightModel;
static WarningLightModel checkEngineLightModel;
static WarningLightModel serviceLightModel;

Config * conf;
MapSensor * map;
Ntc * coolantTempSensor;
Ntc * oilTempSensor;
Ntc * ambientTempSensor;

#ifdef RASPBERRY_PI
static mcp23017 dashLightInputs;
static Adc analogInputs;
static TachInput * tachInput;
#else
#endif


void initializeModels()
{
    /** Init tach **/
    tachModel.setMaxRpm(7000);
    tachModel.setRedLine(6000);
    tachModel.setRpm(0);

    /** Init Speedo **/
    speedoModel.setMaxValue(120);
    speedoModel.setMinValue(0);
    speedoModel.setUnits("mph");
    speedoModel.setCurrentValue(0);
    speedoModel.setTopValue(0);
    speedoModel.setTopUnits("°F");

    /** Init temp/fuel gauge **/
    tempFuelModel.setMinTemp(120);
    tempFuelModel.setMaxTemp(250);
    tempFuelModel.setCurrentTemp(0);
    tempFuelModel.setTempUnits("°F");
    tempFuelModel.setFuelLevel(0);
    tempFuelModel.setHighTempAlarm(220.0);
    tempFuelModel.setLowFuelAlarm(10);

    coolantTempModel.setMinValue(120);
    coolantTempModel.setMaxValue(250);
    coolantTempModel.setUnits("°F");
    coolantTempModel.setHighAlarm(220.0);
    coolantTempModel.setCurrentValue(0.0);

    fuelLevelModel.setMinValue(0);
    fuelLevelModel.setMaxValue(100);
    fuelLevelModel.setCurrentValue(0.0);
    fuelLevelModel.setLowAlarm(10.0);
    fuelLevelModel.setUnits("%");

    /** Init accessory gauges **/
    oilPressureModel.setMinValue(0.0);
    oilPressureModel.setMaxValue(5.0);
    oilPressureModel.setUnits("bar");
    oilPressureModel.setCurrentValue(0.0);
    oilPressureModel.setHighAlarm(4.5);
    oilPressureModel.setLowAlarm(1.0);

    oilTemperatureModel.setMinValue(120.0);
    oilTemperatureModel.setMaxValue(300.0);
    oilTemperatureModel.setUnits("°F");
    oilTemperatureModel.setCurrentValue(0.0);
    oilTemperatureModel.setHighAlarm(260.0);

    boostModel.setMinValue(-20.0);
    boostModel.setMaxValue(30.0);
    boostModel.setUnits("psi");
    boostModel.setCurrentValue(0.0);
    boostModel.setHighAlarm(18.0);

    voltMeterModel.setMinValue(10.0);
    voltMeterModel.setMaxValue(16.0);
    voltMeterModel.setUnits("V");
    voltMeterModel.setCurrentValue(0.0);
    voltMeterModel.setLowAlarm(12.0);
    voltMeterModel.setHighAlarm(15.0);

    /** Init blinkers */
    leftBlinkerModel.setOn(false);
    rightBlinkerModel.setOn(false);

    /** Init Warning Lights **/
    parkingBrakeLightModel.setText("PARKING\nBRAKE");
    brakeFailureLightModel.setText("BRAKE\nFAILURE");
    bulbFailureLightModel.setText("");
    shiftUpLightModel.setText("SHIFT\nUP");
    highBeamLightModel.setText("");
    srsWarningLightModel.setText("SRS");
    oilWarningLightModel.setText("");
    batteryWarningLightModel.setText("");
    absWarningLightModel.setText("ABS");
    checkEngineLightModel.setText("CHECK\nENGINE");
    serviceLightModel.setText("SER-\nVICE");

#ifdef RASPBERRY_PI
#else
    leftBlinkerModel.setOn(true);
    rightBlinkerModel.setOn(true);

    parkingBrakeLightModel.setOn(true);
    brakeFailureLightModel.setOn(true);
    bulbFailureLightModel.setOn(true);
    shiftUpLightModel.setOn(true);
    highBeamLightModel.setOn(true);
    srsWarningLightModel.setOn(true);
    oilWarningLightModel.setOn(true);
    batteryWarningLightModel.setOn(true);
    absWarningLightModel.setOn(true);
    checkEngineLightModel.setOn(true);
    serviceLightModel.setOn(true);
#endif
}

void updateGaugesRPi()
{
#ifdef RASPBERRY_PI
    dashLightInputs.openDevice();
    uint8_t portA = dashLightInputs.read(mcp23017::RegisterAddr::GPIOA);
    uint8_t portB = dashLightInputs.read(mcp23017::RegisterAddr::GPIOB);
    dashLightInputs.closeDevice();

    uint16_t inputs = (portB << 8) | portA;

    auto lightConf = conf->getDashLightConfig();

    leftBlinkerModel.setOn(inputs & (1 << lightConf->value(Config::BLINKER_LEFT_KEY)));
    rightBlinkerModel.setOn(inputs & (1 << lightConf->value(Config::BLINKER_RIGHT_KEY)));
    highBeamLightModel.setOn(inputs & (1 << lightConf->value(Config::HIGH_BEAM_KEY)));
    parkingBrakeLightModel.setOn(inputs & (1 << lightConf->value(Config::PARKING_BRAKE_KEY)));
    brakeFailureLightModel.setOn(inputs & (1 << lightConf->value(Config::BRAKE_FAILURE_KEY)));
    bulbFailureLightModel.setOn(inputs & (1 << lightConf->value(Config::BULB_FAILURE_KEY)));
    shiftUpLightModel.setOn(0);
    srsWarningLightModel.setOn(inputs & (1 << lightConf->value(Config::OD_LAMP_KEY)));
    oilWarningLightModel.setOn(inputs & (1 << lightConf->value(Config::OIL_PRESSURE_KEY)));
    batteryWarningLightModel.setOn(inputs & (1 << lightConf->value(Config::CHARGING_LIGHT_KEY)));
    absWarningLightModel.setOn(inputs & (1 << lightConf->value(Config::CONN_32_PIN3)));
    checkEngineLightModel.setOn(inputs & (1 << lightConf->value(Config::CHECK_ENGINE_KEY)));
    serviceLightModel.setOn(0);

    auto sensorConf = conf->getSensorConfig();

    // volt meter
    qreal volts = analogInputs.readValue(sensorConf->value(Config::FUSE8_12V_KEY));
    voltMeterModel.setCurrentValue(volts);

    // oil temp
    qreal oilVolts = analogInputs.readValue(sensorConf->value(Config::OIL_TEMP_KEY));
    qreal oilTemp = oilTempSensor->calculateTemp(oilVolts, Config::TemperatureUnits::FAHRENHEIT);
    oilTemperatureModel.setCurrentValue(oilTemp);

    // boost gauge
    qreal mapVoltage = analogInputs.readValue(sensorConf->value(Config::MAP_SENSOR_KEY));
    qreal psi = map->getAbsolutePressure(mapVoltage, Config::PressureUnits::PSI) - 14.5038;// will need real atm measurement
    boostModel.setCurrentValue(psi);

    // oil pressure
    qreal oilPressureVolts = analogInputs.readValue(sensorConf->value(Config::OIL_PRESSURE_KEY));
    oilPressureModel.setCurrentValue(oilPressureVolts); // TODO: replace with real sensor calculation

    // fuel level
    qreal fuelVolts = analogInputs.readValue(sensorConf->value(Config::FUEL_LEVEL_KEY));

    qreal coolantTempVolts = analogInputs.readValue(sensorConf->value(Config::COOLANT_TEMP_KEY));
    qreal coolantTemp = coolantTempSensor->calculateTemp(coolantTempVolts, Config::TemperatureUnits::FAHRENHEIT);

    tempFuelModel.setFuelLevel(fuelVolts); // TODO: replace with real sensor calculation
    tempFuelModel.setCurrentTemp(coolantTemp);
    fuelLevelModel.setCurrentValue(fuelVolts);
    coolantTempModel.setCurrentValue(coolantTemp);

    //ambient temp
    qreal ambientTempVolts = analogInputs.readValue(sensorConf->value(Config::AMBIENT_TEMP_KEY));
    qreal ambientTemp = ambientTempSensor->calculateTemp(ambientTempVolts, Config::TemperatureUnits::FAHRENHEIT);
    speedoModel.setTopValue(ambientTemp);

    tachModel.setRpm(tachInput->getRpm());
#endif

}

void updateGauges() {
    QString tempPath = "/sys/class/hwmon/hwmon0/temp1_input";
    QString rpmPath = "/sys/class/hwmon/hwmon3/fan1_input";
    QString battPath = "/sys/class/power_supply/BAT0/voltage_now";
    QString fuelLevelPath = "/sys/class/power_supply/BAT0/capacity";

    QFile tempFile(tempPath);
    QFile rpmFile(rpmPath);
    QFile battFile(battPath);
    QFile fuelFile(fuelLevelPath);

    QTextStream tempStream(&tempFile);
    QTextStream rpmStream(&rpmFile);
    QTextStream battStream(&battFile);
    QTextStream fuelStream(&fuelFile);

    tempFile.open(QIODevice::ReadOnly);
    rpmFile.open(QIODevice::ReadOnly);
    battFile.open(QIODevice::ReadOnly);
    fuelFile.open(QIODevice::ReadOnly);

    //dashLightInputs.openDevice();
    uint8_t portA = 0xAA;//dashLightInputs.read(mcp23017::RegisterAddr::GPIOA);
    uint8_t portB = 0x0F;//dashLightInputs.read(mcp23017::RegisterAddr::GPIOB);
    //dashLightInputs.closeDevice();

    if(tempFile.isOpen())
    {
        QString coreTemp = tempStream.readLine();
        float temp = coreTemp.toFloat();
        qreal tempF = ((temp/1000.0) * 9.0/5.0)+32.0;
        oilTemperatureModel.setCurrentValue(tempF);
        tempFuelModel.setCurrentTemp(tempF * 2);
        speedoModel.setTopValue(tempF);
        coolantTempModel.setCurrentValue(tempF * 2);
    }

    if(rpmFile.isOpen())
    {
        QString rpmString = rpmStream.readLine();
        int rpm = rpmString.toInt();
        tachModel.setRpm(rpm);
        boostModel.setCurrentValue( ((float)rpm/1000.0) * 5.0 );
        oilPressureModel.setCurrentValue( ((float)rpm / 1000.0 * 3) );
    }

    if(battFile.isOpen())
    {
        QString voltage = battStream.readLine();
        float volts = voltage.toInt();
        voltMeterModel.setCurrentValue(volts/1.0e6);
    }

    if(fuelFile.isOpen())
    {
        QString fuelLevel = fuelStream.readLine();
        int level = fuelLevel.toInt();
        tempFuelModel.setFuelLevel(level);
        fuelLevelModel.setCurrentValue(level);
    }

    tempFile.close();
    rpmFile.close();
    battFile.close();
    fuelFile.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

#ifdef RASPBERRY_PI
    conf = new Config(&app);

    tachInput = new TachInput(conf->getTachInputConfig());
#else
    conf = new Config(&app, "/home/whitfijs/git/Volvo240-DigitalDash/QtDash/config.ini");    
#endif
    map = new MapSensor(conf->getMapSensorConfig()->p0V, conf->getMapSensorConfig()->p5V, Config::PressureUnits::KPA);

    QList<Config::TempSensorConfig_t> * tempSensorConfigs = conf->getTempSensorConfigs();
    for (Config::TempSensorConfig_t config : *tempSensorConfigs) {
        if (config.isValid()) {
            if (config.type == Config::TemperatureSensorType::COOLANT) {
                coolantTempSensor = new Ntc(config);
            } else if (config.type == Config::TemperatureSensorType::OIL) {
                oilTempSensor = new Ntc(config);
            } else if (config.type == Config::TemperatureSensorType::AMBIENT) {
                ambientTempSensor = new Ntc(config);
            } else {
                qDebug() << "Sensor type not supported.  Check config.ini file";
            }
        } else {
            qDebug() << "Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
        }
    }

#ifndef RASPBERRY_PI
    QFontDatabase::addApplicationFont(":/fonts/HandelGothReg.ttf");
    QFont mFont;
    mFont.setFamily("Handel Gothic");
    app.setFont(mFont);
#else
    QFontDatabase::addApplicationFont(":/fonts/HandelGothReg.ttf");
    QFont mFont;
    mFont.setFamily("Handel Gothic");
    app.setFont(mFont);
#endif


    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("rpmModel", &tachModel);
    ctxt->setContextProperty("speedoModel", &speedoModel);
    ctxt->setContextProperty("tempFuelModel", &tempFuelModel);
    ctxt->setContextProperty("coolantTempModel", &coolantTempModel);
    ctxt->setContextProperty("fuelLevelModel", &fuelLevelModel);
    ctxt->setContextProperty("oilPModel", &oilPressureModel);
    ctxt->setContextProperty("oilTModel", &oilTemperatureModel);
    ctxt->setContextProperty("boostModel", &boostModel);
    ctxt->setContextProperty("voltMeterModel", &voltMeterModel);
    ctxt->setContextProperty("leftBlinkerModel", &leftBlinkerModel);
    ctxt->setContextProperty("rightBlinkerModel", &rightBlinkerModel);
    ctxt->setContextProperty("parkingBrakeLightModel", &parkingBrakeLightModel);
    ctxt->setContextProperty("brakeFailureLightModel", &brakeFailureLightModel);
    ctxt->setContextProperty("bulbFailureLightModel", &bulbFailureLightModel);
    ctxt->setContextProperty("shiftUpLightModel", &shiftUpLightModel);
    ctxt->setContextProperty("highBeamLightModel", &highBeamLightModel);
    ctxt->setContextProperty("srsWarningLightModel", &srsWarningLightModel);
    ctxt->setContextProperty("oilWarningLightModel", &oilWarningLightModel);
    ctxt->setContextProperty("batteryWarningLightModel", &batteryWarningLightModel);
    ctxt->setContextProperty("absWarningLightModel", &absWarningLightModel);
    ctxt->setContextProperty("checkEngineLightModel", &checkEngineLightModel);
    ctxt->setContextProperty("serviceLightModel", &serviceLightModel);

    initializeModels();

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    std::cout << "Starting GPS" << std::endl;
    GpsHelper * loc = new GpsHelper(&app);

    QObject::connect(loc, SIGNAL(speedUpdateMilesPerHour(qreal)), &speedoModel, SLOT(setCurrentValue(qreal)));

    loc->init();

    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(lastWindowClosed()), loc, SLOT(close()));

#ifndef RASPBERRY_PI
    QTimer rpmTimer;
    rpmTimer.setInterval(100);
    QObject::connect(&rpmTimer, &QTimer::timeout, &app, &updateGauges);
    rpmTimer.start();
#else
    QTimer rpmTimer;
    rpmTimer.setInterval(100);
    QObject::connect(&rpmTimer, &QTimer::timeout, &app, &updateGaugesRPi);
    rpmTimer.start();
#endif

    return app.exec();
}
