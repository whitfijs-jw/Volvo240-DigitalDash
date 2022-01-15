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
                    qDebug() << "Sensor type not supported.  Check config.ini file";
                }
            } else {
                qDebug() << "Sensor Config is not valid: " << QString((int)config.type) << " Check config.ini file";
            }
        }

        // setup oil pressure sensor

        // setup fuel level gauge

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
        qreal oilPressure = oilPressureVolts; // TODO: replace with real sensor calculation
        emit oilPressureUpdate(oilPressure, Config::PressureUnits::BAR);
    }

    void update() {
        auto sensorConf = mSensorConfig;

        // volt meter
        qreal volts = mAnalogInputs.readValue(sensorConf.value(Config::FUSE8_12V_KEY));
        emit voltMeterUpdate(volts); // TODO: replace with real calculation

        // oil temp
        qreal oilVolts = mAnalogInputs.readValue(sensorConf.value(Config::OIL_TEMP_KEY));
        qreal oilTemp = mOilTempSensor->calculateTemp(oilVolts, Config::TemperatureUnits::FAHRENHEIT);
        emit oilTempUpdate(oilTemp, Config::TemperatureUnits::FAHRENHEIT);

        // fuel level
        qreal fuelVolts = mAnalogInputs.readValue(sensorConf.value(Config::FUEL_LEVEL_KEY));
        qreal fuelLevel = (fuelVolts / 5.0) * 100.0; // TODO: replace with real sensor calculation
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
};

#endif // ANALOG_SENSORS_H
