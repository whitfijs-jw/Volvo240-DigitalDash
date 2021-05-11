import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

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
                if (event.key === Qt.Key_Right) {
                   if(swipeView.currentIndex + 1 < swipeView.count) {
                        swipeView.incrementCurrentIndex();
                   } else if (event.key === Qt.Key_Escape) {
                        rootWindow.close();
                   }else {
                       swipeView.setCurrentIndex(0);
                   }

                    event.accepted = true;
                }
            }

        Page {
            BigTachLeft {
                Component.onCompleted: {
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
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
        }
    }
}
