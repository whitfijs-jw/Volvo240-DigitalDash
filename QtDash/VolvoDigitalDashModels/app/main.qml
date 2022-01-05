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
            source: "qrc:/BoostGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm

                item.height = smallGaugeSize
                item.width = smallGaugeSize
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
            source: "qrc:/OilPressure.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = smallGaugeSize
                item.width = smallGaugeSize
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
            source: "qrc:/OilTemperature.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = smallGaugeSize
                item.width = smallGaugeSize
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
            source: "qrc:/Volts.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = smallGaugeSize
                item.width = smallGaugeSize
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
            source: "qrc:/Tacho.qml"
            asynchronous: true

            onLoaded: {
                item.maxValue = maxRpm
                item.mRedLine = redLine
                item.height = tachSize
                item.width = tachSize
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
            source: "qrc:/Speedo.qml"
            asynchronous: true
            onLoaded: {
                speed: currentValue
                item.minSpeed = minValue
                item.maxSpeed = maxValue
                item.units = speedUnits
                item.topValue = valueTop
                item.topUnit = valueTopUnits

                item.height = speedoSize
                item.width = speedoSize
            }

            Binding {
                target: item
                property: "speed"
                value: currentValue;
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
                text: qsTr("Loading Dash...")
                fontSizeMode: Text.Fit
                font.pixelSize: 100
                color: "white"
                onVisibleChanged: {
                    console.count("hidden");
                }
                anchors.centerIn: parent
            }
        }
    }

    Item {
        id: gaugeItem
        anchors.fill: parent
        focus: true

        Loader {
            id: currentGauge
            anchors.fill: parent
            source: "qrc:/Original240Layout.qml"
            asynchronous: true
            visible: false
            onStatusChanged: {
                if (status == Loader.Ready) {
                    splashWait.start()
                    console.log("Loader Ready")
                }
            }
            Component.onCompleted: {
                console.log("Component Complete")
            }
        }

        Timer {
            id: splashWait
            interval: 3500
            repeat: false
            running: false
            onTriggered: {
                loadText.visible = false;
                currentGauge.visible = true;
            }
        }

        Keys.onPressed: {
            switch (event.key) {
                case Qt.Key_0:
                    currentGauge.source = "qrc:/BigTachCenter.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    break;
                case Qt.Key_1:
                    currentGauge.source = "qrc:/BigTachLeft.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    break;
                case Qt.Key_2:
                    currentGauge.source = "Original240Layout.qml";
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setTempFuelSize(400);
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
