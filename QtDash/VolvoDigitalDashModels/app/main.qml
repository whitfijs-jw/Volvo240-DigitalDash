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

    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8

    property int speedoMax: 120;

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

                item.needleWidth = smallGaugeSize * 0.03
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

                item.needleWidth = smallGaugeSize * 0.03
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

                item.needleWidth = smallGaugeSize * 0.03
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

                item.needleWidth = smallGaugeSize * 0.03
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

                item.needleWidth = smallGaugeSize * 0.05
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

                item.needleColor = "red"

                item.needleWidth = tachSize * 0.03
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

                item.needleWidth = speedoSize * 0.015
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

                item.needleColor = "red"

                item.needleWidth = speedoSize * 0.025
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
                item.lowAlarm = gaugeMin

                item.minAngle = -115
                item.maxAngle = -65

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/gauge-faces-740-940/740_coolant_temp.png"

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

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

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

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

                item.needleColor = "red"

                item.needleWidth = smallGaugeSize * 0.05
                item.needleLength = smallGaugeSize * 0.75
                item.needleOffset = smallGaugeSize * 0.25 / 2
                item.offset = smallGaugeSize / 4.5

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
        property bool initialLoad: true

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
