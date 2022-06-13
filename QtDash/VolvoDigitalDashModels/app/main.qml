import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: rootWindow
    visible: true
    width: 1280
    height: 480

    title: qsTr("Lolvo")


    property int smallGaugeSize: 140
    property int tachSize: 400
    property int speedoSize: 440
    property int tempFuelSize: 400
    property int blinkerSize: 50;
    property int linearSpeedoWidth: 1100
    property int linearSpeedoHeight: 65

    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8

    property int speedoMax: 120;

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04

    property var msg: [
        "You thought this\nwas going to work?",
        "Come back later...",
        "Just crush this\nthing already",
        "Can this thing\neven hit 60?",
        "Have fun with your\nM cam",
        "I bet you could get\n$500 on BaT for this",
        "404 Not Found",
        "I heard you like\nFWD Volvos",

    ]



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

    function setSpeedoMax(max) {
        speedoMax = max;
    }

    function boundedAngle(angle, min, max) {
        if (angle > max) {
            angle = max;
        } else if (angle < min) {
            angle = min;
        }

        return angle;
    }

    Component {
        id: odometerDelegate

        Loader {
            source: "qrc:/Odometer.qml"
            asynchronous: true
            onLoaded: {
                item.odometerValue = odometerValue
                item.tripAValue = tripAValue
                item.tripBValue = tripBValue
            }

            Binding {
                target: item
                property: "odometerValue"
                value: odometerValue
            }

            Binding {
                target: item
                property: "tripAValue"
                value: tripAValue
            }

            Binding {
                target: item
                property: "tripBValue"
                value: tripBValue
            }

            Binding {
                target: item
                property: "width"
                value: warningLightWideWidth
            }

            Binding {
                target: item
                property: "height"
                value: warningLightHeight
            }
        }
    }

    Component {
        id: boostDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeMin
                item.initialValueOffset = gaugeMin

                item.minAngle = -226
                item.maxAngle = 45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/accCluster/boost_black_no_numbers.png"

                item.needleColor = "orange"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * 0.55
                item.needleOffset = smallGaugeSize * .25 / 2

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: boostDelegate740

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeMin
                item.initialValueOffset = gaugeMin

                item.minAngle = -228
                item.maxAngle = 45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_boost.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.55
                item.needleOffset = smallGaugeSize * .25 / 2

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: boostDelegate850

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeMin
                item.initialValueOffset = gaugeMin

                item.minAngle = -140
                item.maxAngle = -41

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-850/850_boost.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.50
                item.needleOffset = smallGaugeSize * .25 / 2

                item.needleCenterRadius = 0.25


                item.textOffset = smallGaugeSize * 0.75
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: oilPressureDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeMax
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -136
                item.maxAngle = -45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/accCluster/oil_pressure_black.png"

                item.needleColor = "orange"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * .25 / 2

                item.offset = smallGaugeSize / 4.5

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: oilTemperatureDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -136
                item.maxAngle = -43

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/accCluster/oil_temp_black.png"

                item.needleColor = "orange"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * .25 / 2

                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 0

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: voltMeterDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -136
                item.maxAngle = -45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/accCluster/volt_black.png"

                item.needleColor = "orange"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * .25 / 2

                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 2

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: clockDelegate
        Loader {
            source: "qrc:/Clock.qml"
            asynchronous: true
            onLoaded: {
                item.height = smallGaugeSize
                item.width = smallGaugeSize
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: rpmDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = maxRpm
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.initialValueOffset = 200

                item.minAngle = -221
                item.maxAngle = 32

                item.height = tachSize
                item.width = tachSize

                item.imageResource = "qrc:/mainCluster/tacho.png"

                item.needleColor = "orange"

                item.needleWidth = tachSize * 0.02
                item.needleLength = tachSize * 0.45
                item.needleOffset = tachSize * 0.15 / 2

                item.needleCenterRadius = 0.10

                item.textSize = tachSize * 0.15 / 2
                item.textOffset = tachSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: tachSize
            }

            Binding {
                target: item
                property: "height"
                value: tachSize
            }
        }
    }

    Component {
        id: rpmDelegate740

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = maxRpm
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0
                item.initialValueOffset = 200

                item.minAngle = -220
                item.maxAngle = 40

                item.height = tachSize
                item.width = tachSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_tach.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = tachSize * 0.035
                item.needleLength = tachSize * 0.45
                item.needleOffset = tachSize * 0.15 / 2

                item.needleCenterRadius = 0.15

                item.textSize = 20
                item.textOffset = tachSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: tachSize
            }

            Binding {
                target: item
                property: "height"
                value: tachSize
            }
        }
    }

    Component {
        id: speedoDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = speedoMax
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = speedoMax

                item.initialValueOffset = 4

                item.topValue = valueTop
                item.topUnits = valueTopUnits
                item.topValueEnabled = true
                item.topTextOffset = -speedoSize / 6
                item.topTextSize = speedoSize / 20.0

                item.minAngle = -233
                item.maxAngle = 43

                item.height = speedoSize
                item.width = speedoSize

                item.imageResource = "qrc:mainCluster/early120mphspeedolo.png"

                item.needleColor = "orange"

                item.needleWidth = speedoSize * 0.02
                item.needleLength = speedoSize * 0.45
                item.needleOffset = speedoSize * 0.15 / 2

                item.needleCenterRadius = 0.10

                item.textSize = speedoSize * .15 / 2
                item.textOffset = speedoSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoMax
            }

            Binding {
                target: item
                property: "topValue"
                value: valueTop
            }

            Binding {
                target: item
                property: "width"
                value: speedoSize
            }

            Binding {
                target: item
                property: "height"
                value: speedoSize
            }
        }
    }

    Component {
        id: speedoDelegate740

        Loader {

            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = speedoMax
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = speedoMax

                item.initialValueOffset = 2

                item.topValue = valueTop
                item.topUnits = valueTopUnits
                item.topValueEnabled = true
                item.topTextOffset = -speedoSize / 6
                item.topTextSize = speedoSize / 20.0

                item.minAngle = -227
                item.maxAngle = 45

                item.height = speedoSize
                item.width = speedoSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_speedo.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = speedoSize * 0.0325
                item.needleLength = speedoSize * 0.45
                item.needleOffset = speedoSize * 0.15 / 2

                item.needleCenterRadius = 0.15

                item.textSize = speedoSize * .15 / 2
                item.textOffset = speedoSize / 6
                item.significantDigits = 0
            }


            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoMax
            }

            Binding {
                target: item
                property: "topValue"
                value: valueTop
            }

            Binding {
                target: item
                property: "width"
                value: speedoSize
            }

            Binding {
                target: item
                property: "height"
                value: speedoSize
            }
        }
    }

    Component {
        id: tempFuelDelegate
        Loader {
            source: "qrc:/TempCoolant.qml"
            asynchronous: true
            onLoaded: {
                item.maxCoolantTemp = tempMax
                item.minCoolantTemp = tempMin
                item.units = tempUnits

                item.highAlarm = alarmHighTemp
                item.lowAlarm = alarmLowFuel

                item.height = tempFuelSize
                item.width = tempFuelSize
            }

            Binding {
                target: item
                property: "coolantTemp"
                value: currentTemp;
            }

            Binding {
                target: item
                property: "fuelLevel"
                value: currentFuelLevel
            }

            Binding {
                target: item
                property: "width"
                value: tempFuelSize
            }

            Binding {
                target: item
                property: "height"
                value: tempFuelSize
            }
        }
    }

    Component {
        id: coolant740Delegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -115
                item.maxAngle = -65

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_coolant_temp.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 0

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: fuelLevel740Delegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeMax
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -115
                item.maxAngle = -65

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_fuel.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 0

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: voltMeterDelegate740

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -130
                item.maxAngle = -55

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_voltmeter.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 2

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: coolantDelegate850

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = false

                item.minAngle = -45
                item.maxAngle = 45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-850/850_coolant.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.50
                item.needleOffset = smallGaugeSize * .25 / 2

                item.significantDigits = 0

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: fuelLevelDelegate850


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeMax
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -225
                item.maxAngle = -135

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-850/850_fuel_level.png"
                item.needleResource = "qrc:/needles/needle-740-940.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.50
                item.needleOffset = smallGaugeSize * .25 / 2

                item.significantDigits = 0

                item.needleCenterRadius = 0.25
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: fuelLevelDelegateRSport


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeMax
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = false

                item.minAngle = -40
                item.maxAngle = 40

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_fuel.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = smallGaugeSize * 0.035
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offsetX = -smallGaugeSize / 7.4

                item.significantDigits = 0

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: coolantDelegateRSport


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = false

                item.minAngle = -35
                item.maxAngle = 38

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_coolant_fahrenhet.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = smallGaugeSize * 0.035
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offsetX = -smallGaugeSize / 7.4

                item.significantDigits = 0

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: oilPressureDelegateRSport


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeMax
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = false

                item.minAngle = -48
                item.maxAngle = 48

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_oil_pressure_5bar.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = smallGaugeSize * 0.035
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offsetX = -smallGaugeSize / 4.65

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: voltMeterDelegateRSport


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 8.0
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = false

                item.minAngle = -48
                item.maxAngle = 48

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_voltmeter.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = smallGaugeSize * 0.035
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offsetX = -smallGaugeSize / 4.65

                item.significantDigits = 2

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: speedoDelegateRSport

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = speedoMax
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = speedoMax

                item.initialValueOffset = 10

                item.topValue = valueTop
                item.topUnits = valueTopUnits
                item.topValueEnabled = true
                item.topTextOffset = -speedoSize / 6
                item.topTextSize = speedoSize / 20.0

                item.minAngle = -148
                item.maxAngle = 128

                item.height = speedoSize
                item.width = speedoSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_speedo_mph.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = speedoSize * 0.025
                item.needleLength = speedoSize * 0.525
                item.needleOffset = speedoSize * 0.2 / 2

                item.needleCenterRadius = 0.125

                item.textSize = speedoSize * .15 / 2
                item.textOffset = speedoSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoMax
            }

            Binding {
                target: item
                property: "topValue"
                value: valueTop
            }

            Binding {
                target: item
                property: "width"
                value: speedoSize
            }

            Binding {
                target: item
                property: "height"
                value: speedoSize
            }
        }
    }

    Component {
        id: rpmDelegateRSport

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = 8000
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.initialValueOffset = 400

                item.minAngle = -140
                item.maxAngle = 126

                item.height = tachSize
                item.width = tachSize

                item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_tachometer.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = tachSize * 0.025
                item.needleLength = tachSize * 0.525
                item.needleOffset = tachSize * 0.2 / 2

                item.needleCenterRadius = 0.125

                item.textSize = tachSize * 0.15 / 2
                item.textOffset = tachSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: tachSize
            }

            Binding {
                target: item
                property: "height"
                value: tachSize
            }
        }
    }

    Component {
        id: speedoDelegate544

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = speedoMax
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = speedoMax

                item.height = linearSpeedoHeight
                item.width = linearSpeedoWidth

                item.imageResource = "qrc:/gauge-faces-544/speedo-544-large.png"

                item.needleColor = "red"

                item.needleWidth = item.height * 0.4
                item.needleLength = item.width * 0.9

                item.offset = item.height * .675
                item.offsetX = item.width * 0.035

                item.textSize = speedoSize * .15 / 2
                item.textOffset = speedoSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoMax
            }

            Binding {
                target: item
                property: "width"
                value: linearSpeedoWidth
            }

            Binding {
                target: item
                property: "height"
                value: linearSpeedoHeight
            }
        }
    }

    Component {
        id: rpmDelegate544

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = maxRpm
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.height = 64
                item.width = 600

                item.imageResource = "qrc:/gauge-faces-544/tachometer-544.png"

                item.needleColor = "red"

                item.needleWidth = item.height * 0.4
                item.needleLength = item.width * 0.775

                item.offset = item.height * .625
                item.offsetX = item.width * 0.15

                item.textSize = speedoSize * .15 / 2
                item.textOffset = - speedoSize / 8
                item.significantDigits = 0

                item.blockWidth = item.width * 0.15

            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: 600
            }

            Binding {
                target: item
                property: "height"
                value: 64
            }
        }
    }

    Component {
        id: voltMeterDelegate544


        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = true

                item.minAngle = -130
                item.maxAngle = -55

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-544/battery-544.png"
                item.needleResource = "qrc:/needles/needle-544-140.png"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.0

                item.textOffset = -item.height / 2.0

                item.significantDigits = 2

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: fuelLevelDelegate544

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = true

                item.minAngle = -130
                item.maxAngle = -55

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-544/fuel-544.png"
                item.needleResource = "qrc:/needles/needle-544-140.png"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.0

                item.textOffset = -item.height / 2.0

                item.significantDigits = 1

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: coolantTempDelegate544

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = true

                item.minAngle = -130
                item.maxAngle = -55

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-544/coolant-temp-544.png"
                item.needleResource = "qrc:/needles/needle-544-140.png"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.0

                item.textOffset = -item.height / 2.0

                item.significantDigits = 1

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: oilPressureDelegate544

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.clockwise = true

                item.minAngle = -130
                item.maxAngle = -55

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-544/oil-pressure-544.png"
                item.needleResource = "qrc:/needles/needle-544-140.png"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.0


                item.textOffset = -item.height / 2.0

                item.significantDigits = 1

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: speedoDelegateP1800

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = speedoMax
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = speedoMax

                item.initialValueOffset = 0

                item.topValue = valueTop
                item.topUnits = valueTopUnits
                item.topValueEnabled = true
                item.topTextOffset = -speedoSize / 6
                item.topTextSize = speedoSize / 20.0

                item.minAngle = -225
                item.maxAngle = 40

                item.height = speedoSize
                item.width = speedoSize

                item.imageResource = "qrc:/gauge-faces-p1800/speedo-mph-p1800.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = item.width * 0.025
                item.needleLength = item.width * 0.375
                item.needleOffset = 0

                item.needleCenterRadius = 0.125

                item.textSize = speedoSize * .15 / 2
                item.textOffset = speedoSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoMax
            }

            Binding {
                target: item
                property: "topValue"
                value: valueTop
            }

            Binding {
                target: item
                property: "width"
                value: speedoSize
            }

            Binding {
                target: item
                property: "height"
                value: speedoSize
            }
        }
    }

    Component {
        id: rpmDelegateP1800

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = 7000
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.initialValueOffset = 0

                item.minAngle = -221
                item.maxAngle = 35

                item.height = speedoSize
                item.width = speedoSize

                item.imageResource = "qrc:/gauge-faces-p1800/tach-p1800.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleColor = "burlywood"

                item.needleWidth = item.width * 0.025
                item.needleLength = item.width * 0.375
                item.needleOffset = 0

                item.needleCenterRadius = 0.125

                item.textSize = tachSize * 0.15 / 2
                item.textOffset = tachSize / 6
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: speedoSize
            }

            Binding {
                target: item
                property: "height"
                value: speedoSize
            }
        }
    }

    Component {
        id: coolantTempDelegateP1800

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 90
                item.maxValue = 230
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = 20
                item.width = 125

                item.imageResource = ""

                item.needleColor = "goldenrod"

                item.needleWidth = item.height
                item.needleLength = item.width

                item.offset = 0
                item.offsetX = 0

                item.textSize = item.width * 0.2
                item.textOffsetY = item.width * 0.70
                item.textRotation = 90
                item.significantDigits = 0

                item.blockWidth = 0
                item.shear = 0
                item.barRadius = 2
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: 80
            }

            Binding {
                target: item
                property: "height"
                value: 15
            }
        }
    }

    Component {
        id: oilTempDelegateP1800

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 140
                item.maxValue = 280
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = 20
                item.width = 125

                item.imageResource = ""

                item.needleColor = "lightseagreen"

                item.needleWidth = item.height
                item.needleLength = item.width

                item.offset = 0
                item.offsetX = 0

                item.textSize = item.width * 0.2
                item.textOffsetY = - item.width * 0.70
                item.textRotation = 90
                item.significantDigits = 0

                item.blockWidth = 0
                item.shear = 0
                item.barRadius = 2
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: 80
            }

            Binding {
                target: item
                property: "height"
                value: 15
            }
        }
    }

    Component {
        id: oilPressureDelegateP1800

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = 6
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -145
                item.maxAngle = -35

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-p1800/oil-pressure-p1800.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = item.width * 0.375
                item.needleOffset = 0

                item.offset = 0

                item.textSize = item.width * 0.1
                item.significantDigits = 2

                item.needleCenterRadius = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: fuelLevelDelegateP1800

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -145
                item.maxAngle = -35

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-p1800/fuel-level-p1800.png"
                item.needleResource = "qrc:/needles/needle-rsport.png"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = item.width * 0.375
                item.needleOffset = 0

                item.significantDigits = 1
                item.textSize = item.width * 0.1

                item.needleCenterRadius = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
        }
    }

    Component {
        id: leftBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = false
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Component {
        id: rightBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = true
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Component {
        id: parkingBrakeLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWideWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: brakeFailureLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWideWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: bulbFailureLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
                item.imageSource = "qrc:/warningLights/Bulb_failure_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: shiftUpLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: highBeamLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "lightcyan"
                item.width = warningLightWidth
                item.imageSource = "qrc:/warningLights/high_beam_icon.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: srsWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: oilWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
                item.imageSource = "qrc:warningLights/oil_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: batteryWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
                item.imageSource = "qrc:warningLights/battery_charge_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: absWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: checkEngineLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: serviceLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Item {
        id: loading
        anchors.fill: parent
        rotation: if (RASPBERRY_PI) {
                      180
                  } else {
                      0
                  }
        Rectangle {
            anchors.fill: parent
            color: "black"

            Text {
                id: loadText
                text: qsTr(rootWindow.msg[Math.floor(Math.random() * rootWindow.msg.length)])
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.Fit
                font.pixelSize: 100
                color: "white"
                onVisibleChanged: {
                    console.count("hidden");
                    var txt = qsTr(rootWindow.msg[Math.floor(Math.random() * rootWindow.msg.length)]);
                    if (loadText.text === txt) {
                        loadText.text = qsTr(rootWindow.msg[Math.floor(Math.random() * rootWindow.msg.length)]);
                    } else {
                        loadText.text = txt;
                    }
                }
                anchors.centerIn: parent
            }
        }
    }

    Item {
        id: gaugeItem
        anchors.fill: parent
        focus: true
        rotation: if (RASPBERRY_PI) {
                      180
                  } else {
                      0
                  }
        property bool initialLoad: true
        antialiasing: true
        smooth: true

        Loader {
            id: currentGauge
            anchors.fill: parent
            source: "qrc:/Original240Layout.qml"
            asynchronous: true
            visible: false
            onStatusChanged: {
                if (status == Loader.Ready) {
                    console.log("Loader Ready")
                    if (!gaugeItem.initialLoad) {
                        visible = true;
                        loadText.visible = false;
                    } else {
                        bootTimer.start();
                        gaugeItem.initialLoad = false
                    }
                } else if (status == Loader.Loading) {
                    currentGauge.visible = false;
                    loadText.visible = true;
                    console.log("Loader Loading")
                }
            }
        }

        Timer {
            id: bootTimer
            interval: 2000
            running: false
            repeat: false
            onTriggered: {
                currentGauge.visible = true;
                loadText.visible = false;
            }
        }

        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_0:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/BigTachCenter.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setSpeedoMax(120);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    break;
                case Qt.Key_1:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/BigTachLeft.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setSpeedoMax(120);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    break;
                case Qt.Key_2:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original240Layout.qml";
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    break;
                case Qt.Key_3:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original740Layout.qml"
                    setSmallGaugeSize(140);
                    setTachSize(275);
                    setSpeedoSize(350);
                    setSpeedoMax(140);
                    setTempFuelSize(300);
                break;
                case Qt.Key_4:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original240LayoutClock.qml";
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    break;
                case Qt.Key_5:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original850R.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(440);
                    setSpeedoMax(140);
                    //setTempFuelSize(300);
                    break;
                case Qt.Key_6:
                    currentGauge.source = "qrc:/OriginalRSportLayout.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(350);
                    setSpeedoMax(130);
                    break;

                case Qt.Key_7:
                    currentGauge.source = "qrc:/Original544Layout.qml"
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    break;
                case Qt.Key_8:
                    currentGauge.source = "qrc:/OriginalP1800Layout.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    break;
                case Qt.Key_Escape:
                    Qt.quit();
                    break;
                default:
                    break;
                }
                event.accepted = true;
            }

        Loader {
            source: "WarningLightBar.qml"
            asynchronous: true
        }
    }
}
