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

static TachometerModel tachModel;
static SpeedometerModel speedoModel;
static TempAndFuelGaugeModel tempFuelModel;
static AccessoryGaugeModel oilPressureModel;
static AccessoryGaugeModel oilTemperatureModel;
static AccessoryGaugeModel ambientTemperatureModel;
static AccessoryGaugeModel boostModel;
static AccessoryGaugeModel voltMeterModel;
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

#ifdef RASPBERRY_PI
static mcp23017 dashLightInputs;
static Adc analogInputs;
static Ntc oilTempSensor(3700.0, 5.0, 10000.0, 0.75);
#else
static Adc analogInputs("mcp3208", "/home/whitfijs/git/dummy_sys/bus/iio/devices/");
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
    voltMeterModel.setLowAlarm(11.0);
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
    //auto analogInputs = new AnalogInput("mcp3208", "/home/whitfijs/git/dummy_sys/bus/iio/devices/");
    //analogInputs.setVoltageRef(5.0);
#endif
}

void updateGaugesRPi()
{
    static double oilPressure = 0.0;
    static double boost = 0.0;
    static double volts = 13.0;
    static double fuel = 100.0;
    static double rpm = 0;

    QString tempPath = "/sys/class/thermal/thermal_zone0/temp";
    //QString adcPath = "/sys/class/i2c-adapter/i2c-1/1-0048/iio:device0";
    QFile tempFile(tempPath);
    QTextStream tempStream(&tempFile);
    tempFile.open(QIODevice::ReadOnly);



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

    volts = analogInputs.readValue(0);
    voltMeterModel.setCurrentValue(volts);

    qreal oilVolts = analogInputs.readValue(1);

    oilTemperatureModel.setCurrentValue(
                oilTempSensor.calculateAvgTemp(oilVolts)
                );
#endif

    if(tempFile.isOpen())
    {
        QString coreTemp = tempStream.readLine();
        float temp = coreTemp.toFloat();
        tempFuelModel.setCurrentTemp(((temp/1000.0) * 9.0/5.0)+32.0);
    }

    boostModel.setCurrentValue((boost*8.94)-14.53);
    boost += 0.005;
    if( boost > 5.0 )
    {
        boost = 0.0;
    }

    oilPressureModel.setCurrentValue(oilPressure);
    oilPressure += 0.005;
    if( oilPressure > 5.0)
    {
        oilPressure = 0.0;
    }

    tempFuelModel.setFuelLevel(fuel);
    fuel -= 0.05;
    if( fuel < 0.0 )
    {
        fuel = 100.0;
    }

    tachModel.setRpm(rpm);
    rpm += 10;
    if( rpm > 7200 )
    {
        rpm = 0.0;
    }

    tempFile.close();
}

void updateGauges() {
    QString tempPath = "/sys/class/thermal/thermal_zone1/temp";
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
        oilTemperatureModel.setCurrentValue(((temp/1000.0) * 9.0/5.0)+32.0);
        tempFuelModel.setCurrentTemp(((temp/1000.0) * 9.0/5.0)+32.0);
    }

    if(rpmFile.isOpen())
    {
        QString rpmString = rpmStream.readLine();
        int rpm = rpmString.toInt();
        tachModel.setRpm(rpm);
        boostModel.setCurrentValue( ((float)rpm/1000.0)*2.0 );
        oilPressureModel.setCurrentValue( ((float)rpm / 1000.0) );
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

    conf = new Config(&app, "/home/whitfijs/git/Volvo240-DigitalDash/QtDash/VolvoDigitalDashModels/config.ini");


#ifndef RASPBERRY_PI
    QFontDatabase::addApplicationFont(":/fonts/aribkl.ttf");
    QFont mFont;
    mFont.setFamily("Arial Black");
    app.setFont(mFont);
#else
    QFontDatabase::addApplicationFont(":/fonts/aribkl.ttf");
    QFont font;
    font.setFamily("Arial Black");
    app.setFont(font);
#endif


    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("rpmModel", &tachModel);
    ctxt->setContextProperty("speedoModel", &speedoModel);
    ctxt->setContextProperty("tempFuelModel", &tempFuelModel);
    ctxt->setContextProperty("oilPModel", &oilPressureModel);
    ctxt->setContextProperty("oilTModel", &oilTemperatureModel);
    ctxt->setContextProperty("outsideTempModel", &ambientTemperatureModel);
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

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    std::cout << "Starting GPS" << std::endl;
    GpsHelper * loc = new GpsHelper(&app);

    QObject::connect(loc, SIGNAL(speedUpdateMilesPerHour(qreal)), &speedoModel, SLOT(setCurrentValue(qreal)));

    loc->init();

    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(lastWindowClosed()), loc, SLOT(close()));

    return app.exec();
}
