#ifndef SENSOR_SOURCE_ADC_H
#define SENSOR_SOURCE_ADC_H

#include <sensor_source.h>
#include <adc.h>

/**
 * @brief The AdcSource class
 */
class AdcSource : public SensorSource {
    Q_OBJECT
public:
    /**
     * @brief AdcSource constructor
     * @param parent: parent object
     * @param config: dash config
     * @param name: name
     */
    AdcSource(QObject * parent, Config * config, QString name = "adc") :
        SensorSource(parent, config, name) {
    }

    /**
     * @brief init
     * @return true if successful
     */
    bool init() {
        return true;
    }

    /**
     * @brief get number of channels
     * @return number of ADC channels
     */
    int getNumChannels() {
        return mAdc.getNumChannels();
    }

    /**
     * @brief get ADC units
     * @param channel: adc channel
     * @return ADC output units (volts)
     */
    QString getUnits(int channel) {
        (void)channel;
        return "volts";
    }

public slots:
    /**
     * @brief update all channels and emit dataReady
     */
    void updateAll() {
        for (int i = 0; i < mAdc.getNumChannels(); i++) {
            update(i);
        }

    }

    /**
     * @brief update given channel
     * @param channel: adc channel
     */
    void update(int channel) {
        qreal volts = mAdc.readValue(channel);
        emit dataReady(volts, channel);
    }

private:
    Adc mAdc; //!< ADC object
};

#endif // SENSOR_SOURCE_ADC_H
