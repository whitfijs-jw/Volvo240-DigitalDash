import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml 2.12

ApplicationWindow {
    id: rootWindow
    visible: true
    width: 1280
    height: 480
    title: qsTr("Lolvo")

    property int smallGaugeSize: 140
    property int tachSize: 440
    property int speedoSize: tachSize - smallGaugeSize - 10
    property int tempFuelSize: tachSize - smallGaugeSize - 10
    property int blinkerSize: 50;

    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8


    function setSmallGaugeSize(size) {
        smallGaugeSize = size;
    }

    function setTachSize(size) {
        tachSize = size;
    }

    function setSpeedoSize(size) {
        speedoSize = size;
    }

    function setTempFuelSize(size) {
        tempFuelSize = size;
    }

    Component {
        id: boostDelegate
        BoostGauge {
            minValue: gaugeMin
            maxValue: gaugeMax
            value: currentValue
            units: gaugeUnits
            highAlarm: gaugeHighAlarm

            height: smallGaugeSize
            width: smallGaugeSize
        }

    }

    Component {
        id: oilPressureDelegate
        OilPressure {
            minValue: gaugeMin
            maxValue: gaugeMax
            value: currentValue
            units: gaugeUnits
            highAlarm: gaugeHighAlarm
            lowAlarm: gaugeLowAlarm

            height: smallGaugeSize
            width: smallGaugeSize
        }
    }

    Component {
        id: oilTemperatureDelegate
        OilTemperature {
            minValue: gaugeMin
            maxValue: gaugeMax
            value: currentValue
            units: gaugeUnits
            highAlarm: gaugeHighAlarm
            lowAlarm: gaugeLowAlarm

            height: smallGaugeSize
            width: smallGaugeSize
        }
    }

    Component {
        id: voltMeterDelegate
        Volts {
            minValue: gaugeMin
            maxValue: gaugeMax
            value: currentValue
            units: gaugeUnits
            highAlarm: gaugeHighAlarm
            lowAlarm: gaugeLowAlarm

            height: smallGaugeSize
            width: smallGaugeSize
        }
    }

    Component {
        id: clockDelegate
        Clock {
            height: smallGaugeSize
            width: smallGaugeSize
        }
    }

    Component {
        id: rpmDelegate
        Tacho {
            value: rpm
            maxValue: maxRpm
            mRedLine: redLine
            height: tachSize
            width: tachSize
        }
    }

    Component {
        id: speedoDelegate
        Speedo {
            speed: currentValue
            minSpeed: minValue
            maxSpeed: maxValue
            units: speedUnits
            topValue: valueTop
            topUnit: valueTopUnits
            height: speedoSize
            width: speedoSize
        }
    }

    Component {
        id: tempFuelDelegate
        TempCoolant {
            maxCoolantTemp: tempMax
            minCoolantTemp: tempMin
            coolantTemp: currentTemp
            units: tempUnits
            fuelLevel: currentFuelLevel
            highAlarm: alarmHighTemp
            lowAlarm: alarmLowFuel

            height: tempFuelSize
            width: tempFuelSize
        }
    }

    Component {
        id: leftBlinkerDelegate
        Blinker {
            on: indicatorOn
            flipped: false

            width: blinkerSize
            height: 3 * blinkerSize / 4
        }
    }

    Component {
        id: rightBlinkerDelegate
        Blinker {
            on: indicatorOn
            flipped: true

            width: blinkerSize
            height: 3 * blinkerSize / 4
        }
    }

    Component {
        id: parkingBrakeLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"

            width: warningLightWideWidth
        }
    }

    Component {
        id: brakeFailureLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"

            width: warningLightWideWidth
        }
    }

    Component {
        id: bulbFailureLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "orange"
            imageSource: "qrc:/warningLights/Bulb_failure_icon_no_background.png"

            width: warningLightWidth
        }
    }

    Component {
        id: shiftUpLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "orange"

            width: warningLightWidth
        }
    }

    Component {
        id: highBeamLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "lightcyan"
            imageSource: "qrc:/warningLights/high_beam_icon.png"

            width: warningLightWidth
        }
    }

    Component {
        id: srsWarningLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"

            width: warningLightWidth
        }
    }

    Component {
        id: oilWarningLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"
            imageSource: "qrc:warningLights/oil_icon_no_background.png"

            width: warningLightWidth
        }
    }

    Component {
        id: batteryWarningLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"
            imageSource: "qrc:warningLights/battery_charge_icon_no_background.png"

            width: warningLightWidth
        }
    }

    Component {
        id: absWarningLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "red"

            width: warningLightWidth
        }
    }

    Component {
        id: checkEngineLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "orange"

            width: warningLightWidth
        }
    }

    Component {
        id: serviceLightDelegate

        WarningLight {
            on: warningLightOn
            warningText: warningLightText
            lightColor: "orange"

            width: warningLightWidth
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        focus: true

        onCurrentIndexChanged: {
            switch( swipeView.currentIndex )
            {
            case 0:
                setSmallGaugeSize(140);
                setTachSize(440);
                setSpeedoSize(tachSize - smallGaugeSize - 10);
                setTempFuelSize(tachSize - smallGaugeSize - 10);
                break;
            case 1:
                setSmallGaugeSize(140);
                setTachSize(440);
                setSpeedoSize(tachSize - smallGaugeSize - 10);
                setTempFuelSize(tachSize - smallGaugeSize - 10);
                break;
            case 2:
                setSmallGaugeSize(140);
                setTachSize(400);
                setSpeedoSize(440);
                setTempFuelSize(400);
                break;
            default:
                setSmallGaugeSize(140);
                setTachSize(440);
                setSpeedoSize(tachSize - smallGaugeSize - 10);
                setTempFuelSize(tachSize - smallGaugeSize - 10);
                break;
            }
        }

        Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Right:
                    if(swipeView.currentIndex + 1 < swipeView.count) {
                        swipeView.incrementCurrentIndex();
                    } else {
                        swipeView.setCurrentIndex(0);
                    }

                    break;
                case Qt.Key_Escape:
                    rootWindow.close();
                    break;
                case Qt.Key_L:
                    break;
                case Qt.Key_R:
                    break;
                default:
                    swipeView.setCurrentIndex(0);
                    break;
                }
                event.accepted = true;
            }

        Page {
            BigTachLeft {
                id: bigTach
                Component.onCompleted: {
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                }

                WarningLightBar {
                }
            }
        }

        Page {
            BigTachCenter {
                Component.onCompleted: {
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                }
            }

            WarningLightBar {
            }
        }

        Page {
            Original240Layout {
                Component.onCompleted: {
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setTempFuelSize(400);
                }
            }

            WarningLightBar {
            }
        }
    }
}
