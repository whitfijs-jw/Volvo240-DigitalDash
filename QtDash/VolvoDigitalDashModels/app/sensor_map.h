#ifndef SENSOR_MAP_H
#define SENSOR_MAP_H

#include <sensor.h>
#include <sensor_source_adc.h>
#include <map_sensor.h>

/**
 * @brief The Map_Sensor class
 */
class Map_Sensor : public Sensor {
public:
    static constexpr qreal DEFAULT_P_ATM_PSI = 14.5038;

    /**
     * @brief Map_Sensor constructor
     * @param parent: parent object
     * @param config: dash config
     * @param source: adc sensor source
     * @param channel: adc channel
     */
    Map_Sensor(QObject * parent, Config * config,
               AdcSource * source, int channel) :
    Sensor(parent, config, source, channel) {
        // setup map sensor
        mMapSensor = new MapSensor(
                    mConfig->getMapSensorConfig().p0V,
                    mConfig->getMapSensorConfig().p5V,
                    source->getVRef(), // vref from source
                    mConfig->getMapSensorConfig().units
                    );
        // check that a valid atm pressure is available
        if (mConfig->getMapSensorConfig().pAtm > 0) {
            // convert atm pressure to PSI to be used internally
            SensorUtils::convertPressure(
                mConfig->getMapSensorConfig().pAtm,
                Config::PressureUnits::PSI,
                mConfig->getMapSensorConfig().units);
        }
    }

    QString getUnits() override {
        return Config::UNITS_PSI;
    }

public slots:
    /**
     * @brief transform adc voltage into pressure
     * @param data: data from ADC source
     * @param channel: adc channel
     */
    void transform(QVariant data, int channel) override {
        if (channel == getChannel()) {
            qreal volts = data.toReal();
            qreal pressure = mMapSensor->getAbsolutePressure(volts, Config::PressureUnits::PSI) - mPressureAtm;
            emit sensorDataReady(pressure);
        }
    }

private:
    MapSensor * mMapSensor;
    qreal mPressureAtm = DEFAULT_P_ATM_PSI;
};

#endif // SENSOR_MAP_H
