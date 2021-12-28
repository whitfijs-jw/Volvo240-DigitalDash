+#ifndef DASHLIGHTS_H
#define DASHLIGHTS_H

#include <stdint.h>

class DashLights {
public:

    enum class LightPositions {
        OIL_PRESSURE_SWITCH = 0,
        OD_LAMP,
        HIGH_BEAM,
        BRAKE_FAILURE,
        BULB_FAILURE,
        CHARGING,
        BLINKER_LEFT,
        BLINKER_RIGHT,
        SPARE0,
        SPARE1,
        CONN_32_PIN_3,
        PARKING_BRAKE,
    };

    typedef struct {
        uint8_t OilPressureSwitch: 1;
        uint8_t ODLamp: 1;
        uint8_t HighBeam: 1;
        uint8_t BrakeFailure: 1;
        uint8_t BulbFailure: 1;
        uint8_t Charging: 1;
        uint8_t BlinkerLeft: 1;
        uint8_t BlinkerRight: 1;
        uint8_t Spare0: 1;
        uint8_t Spare1: 1;
        uint8_t Conn32Pin3: 1;
        uint8_t ParkingBrake: 1;
        uint8_t NC0: 1;
        uint8_t NC1: 1;
        uint8_t NC2: 1;
        uint8_t NC3: 1;
    } DashLightsMap_t;

    union Lights {
        uint16_t ports;
        DashLightsMap_t lights;
    };

    static Lights parse(uint8_t portA, uint8_t portB) {
        Lights dashLights;
        dashLights.ports = (portB << 8 | portA);
        return dashLights;
    }
};


#endif // DASHLIGHTS_H
