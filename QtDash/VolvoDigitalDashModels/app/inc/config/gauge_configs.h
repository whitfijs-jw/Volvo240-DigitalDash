#ifndef GAUGE_CONFIGS_H
#define GAUGE_CONFIGS_H

namespace GaugeConfig {

    /**
     * @struct GaugeConfig
     */
    using GaugeConfig = struct gaugeConfig {
        qreal min; //!< minimum gauge value
        qreal max; //!< maxuimum gauge value
        qreal lowAlarm; //!< low alarm
        qreal highAlarm; //!< high alarm
        QString displayUnits; //!< display units
    };

    /**
     * @struct SpeedoConfig
     */
    using SpeedoConfig = struct speedoConfig {
        GaugeConfig gaugeConfig; //!< Gauge config
        QString topSource; //!< secondary display source
        QString topUnits; //!< secondary display units
    };

    /**
     * @struct TachoConfig
     */
    using TachoConfig = struct tachConfig {
        qreal maxRpm; //!< maximum rpm -- lowest possible value will help filter out noisier data
        qreal redline; //!< defines when numerical RPM indication will turn red
    };

}

#endif // GAUGE_CONFIGS_H
