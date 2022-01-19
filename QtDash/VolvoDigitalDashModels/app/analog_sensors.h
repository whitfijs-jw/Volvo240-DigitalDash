#ifndef ANALOG_SENSORS_H
#define ANALOG_SENSORS_H

#include <QObject>
#include <QMap>
#include <QAbstractListModel>
#include <QDebug>

#include <config.h>
#include <adc.h>
#include <ntc.h>
#include <map_sensor.h>
#include <sensor_utils.h>
#include <analog_12v_input.h>

class AnalogSensors : public QObject {
    Q_OBJECT
public:
    AnalogSensors(QObject * parent, Config * conf) :
        QObject(parent), mSensorConfig(conf->getSensorConfig()){

        // setup coolant temp sensors
        QList<Config::TempSensorConfig_t> * tempSensorConfigs = conf->getTempSensorConfigs();
        for (Config::TempSensorConfig_t config : *tempSensorConfigs) {
            if (config.isValid()) {
                if (config.type == Config::TemperatureSensorType::COOLANT) {
                    mCoolantTempSensor = new Ntc(config);
                } else if (config.type == Config::TemperatureSensorType::OIL) {
                    mOilTempSensor = new Ntc(config);
                } else if (config.type == Config::TemperatureSensorType::AMBIENT) {
                    mAmbientTempSensor = new Ntc(config);
                } else {
                    qDebug() << "Temperature Sensor type not supported.  Check config.ini file";
                }
            } else {
                qDebug() << "Temperature Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
            }
        }

        QList<Config::ResistiveSensorConfig_t> resSensorConfig = conf->getResistiveSensorConfig();
        for (Config::ResistiveSensorConfig_t config : resSensorConfig) {
            if (config.isValid()) {
                if (config.type == Config::RES_SENSOR_TYPE_OIL_PRESSURE) {
                    mOilPressureSensor = config;
                    if (config.fitType == Config::ResistiveSensorType::POLYNOMIAL) {
                        mOilPressureSensor.coeff = SensorUtils::polynomialRegression(
                                    mOilPressureSensor.x,
                                    mOilPressureSensor.y,
                                    mOilPressureSensor.order
                                    );
                    }
                } else if (config.type == Config::RES_SENSOR_TYPE_FUEL_LEVEL) {
                    mFuelLevelSensor = config;
                    if (config.fitType == Config::ResistiveSensorType::POLYNOMIAL) {
                        mFuelLevelSensor.coeff = SensorUtils::polynomialRegression(
                                    mFuelLevelSensor.x,
                                    mFuelLevelSensor.y,
                                    mFuelLevelSensor.order
                                    );

                        qDebug() << "Fuel Coeff: " << mFuelLevelSensor.x.length() << " " << mFuelLevelSensor.y.length();
                    }
                }
            }
        }

        // setup voltmeter and rheostat voltage
        mVoltmeter = new Analog12VInput(
                    conf->getAnalog12VInputConfig(Config::ANALOG_INPUT_12V_VOLTMETER));

        mRheostat = new Analog12VInput(
                    conf->getAnalog12VInputConfig(Config::ANALOG_INPUT_12V_RHEOSTAT));

        // setup map sensor
        mMapSensor = new MapSensor(
                    conf->getMapSensorConfig().p0V,
                    conf->getMapSensorConfig().p5V,
                    conf->getMapSensorConfig().units
                    );

    }

    void init() {

    }
signals:
    void voltMeterUpdate(qreal volts);
    void oilTempUpdate(qreal temp, Config::TemperatureUnits units);
    void boostPressureUpdate(qreal pressure, Config::PressureUnits units);
    void oilPressureUpdate(qreal pressure, Config::PressureUnits units);
    void fuelLevelUpdate(qreal level);
    void coolantTempUpdate(qreal temp, Config::TemperatureUnits units);
    void ambientTempUpdate(qreal temp, Config::TemperatureUnits units);

public slots:
    void updateFast() {
        auto sensorConf = mSensorConfig;

        // boost gauge
        qreal mapVoltage = mAnalogInputs.readValue(sensorConf.value(Config::MAP_SENSOR_KEY));
        qreal psi = mMapSensor->getAbsolutePressure(mapVoltage, Config::PressureUnits::PSI) - 14.5038;// will need real atm measurement
        emit boostPressureUpdate(psi, Config::PressureUnits::PSI);

        // oil pressure
        qreal oilPressureVolts = mAnalogInputs.readValue(sensorConf.value(Config::OIL_PRESSURE_KEY));
        qreal oilPRes = SensorUtils::getResistance(oilPressureVolts, 5.0, mOilPressureSensor.rBalance);
        qreal oilPressure = SensorUtils::polynomialValue(oilPRes, mOilPressureSensor.coeff);
        emit oilPressureUpdate(oilPressure, Config::PressureUnits::BAR);
    }

    void update() {
        auto sensorConf = mSensorConfig;

        // volt meter
        qreal volts = mAnalogInputs.readValue(sensorConf.value(Config::FUSE8_12V_KEY));
        qreal voltMeterVolts = mVoltmeter->getVoltage(volts);
        emit voltMeterUpdate(voltMeterVolts);

        //rheostat voltage (maybe use for screen dimming?)
        qreal rheoVolts = mAnalogInputs.readValue(sensorConf.value(Config::DIMMER_VOLTAGE_KEY));
        qreal rheoFullVolts = mRheostat->getVoltage(rheoVolts);
        // TODO: hook this up somewhere?

        // oil temp
        qreal oilVolts = mAnalogInputs.readValue(sensorConf.value(Config::OIL_TEMP_KEY));
        qreal oilTemp = mOilTempSensor->calculateTemp(oilVolts, Config::TemperatureUnits::FAHRENHEIT);
        emit oilTempUpdate(oilTemp, Config::TemperatureUnits::FAHRENHEIT);

        // fuel level
        qreal fuelVolts = mAnalogInputs.readValue(sensorConf.value(Config::FUEL_LEVEL_KEY));
        qreal fuelRes = SensorUtils::getResistance(fuelVolts, 5.0, mFuelLevelSensor.rBalance);
        qreal fuelLevel = SensorUtils::polynomialValue(fuelRes, mFuelLevelSensor.coeff);
        emit fuelLevelUpdate(fuelLevel);

        qreal coolantTempVolts = mAnalogInputs.readValue(sensorConf.value(Config::COOLANT_TEMP_KEY));
        qreal coolantTemp = mCoolantTempSensor->calculateTemp(coolantTempVolts, Config::TemperatureUnits::FAHRENHEIT);
        emit coolantTempUpdate(coolantTemp, Config::TemperatureUnits::FAHRENHEIT);

        //ambient temp
        qreal ambientTempVolts = mAnalogInputs.readValue(sensorConf.value(Config::AMBIENT_TEMP_KEY));
        qreal ambientTemp = mAmbientTempSensor->calculateTemp(ambientTempVolts, Config::TemperatureUnits::FAHRENHEIT);
        emit ambientTempUpdate(ambientTemp, Config::TemperatureUnits::FAHRENHEIT);
    }
private:
    QMap<QString, int> mSensorConfig;

    Adc mAnalogInputs;

    Ntc * mCoolantTempSensor;
    Ntc * mOilTempSensor;
    Ntc * mAmbientTempSensor;
    MapSensor * mMapSensor;
    Config::ResistiveSensorConfig_t mOilPressureSensor;
    Config::ResistiveSensorConfig_t mFuelLevelSensor;
    Config::Analog12VInputConfig_t mVoltMeterInput;
    Analog12VInput * mVoltmeter;
    Analog12VInput * mRheostat;


};

#endif // ANALOG_SENSORS_H
