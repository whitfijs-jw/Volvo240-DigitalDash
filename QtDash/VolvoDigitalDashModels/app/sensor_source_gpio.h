#ifndef SENSOR_SOURCE_GPIO_H
#define SENSOR_SOURCE_GPIO_H

#include <sensor_source.h>
#include <mcp23017.h>

class GpioSource : public SensorSource {
    GpioSource(QObject * parent, Config * config, QString name = "gpio") :
        SensorSource(parent, config, name) {

    }

    bool init() {
        return true;
    }

    int getNumChannels() {
        return 16;
    }

    QVariant getValue(int channel) {
        uint16_t inputs = getInputs();

        return bitValue(inputs, channel);
    }

    QString getUnits(int channel) {
        (void)channel;
        return "on/off";
    }

public slots:
    void updateAll() {
        uint16_t inputs = getInputs();
        QList<QVariant> vals;
        for (int i = 0; i < mInputs.getNumChannels(); i++) {
            vals.push_back(bitValue(inputs, i));
        }
        emit dataReady(vals);
    }

    void update(int channel) {
        uint16_t inputs = getInputs();

        emit dataReady(bitValue(inputs, channel), channel);
    }

private:
    static constexpr bool bitValue(uint16_t ports, uint8_t channel) {
        return ports & (1 << channel);
    }

    mcp23017 mInputs;

    uint16_t getInputs() {
        mInputs.openDevice();
        uint8_t portA = mInputs.read(mcp23017::RegisterAddr::GPIOA);
        uint8_t portB = mInputs.read(mcp23017::RegisterAddr::GPIOB);
        mInputs.closeDevice();

        uint16_t inputs = (portB << 8) | portA;

        return inputs;
    }
};

#endif // SENSOR_SOURCE_GPIO_H
