import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item{
    id: dashItem
    height: 480
    width: 1280

    Rectangle {
        id: background
        color: "black"
        anchors.fill: parent
    }

    Blinker {
        id: leftTurn

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -200
        z: 2

        width: 50
        height: 40
    }

    Blinker {
        id: rightTurn

        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 200
        z: 2
        rotation: 180

        width: 50
        height: 40
    }


    Tacho {
        id: tachometer

        width: parent.width/3
        height: parent.height

        anchors.left: parent.left
        anchors.leftMargin: 20

        maxValue: 7000
        minValue: 0
    }


    Speedo {
        id: speedometer

        width: parent.width/3
        height: parent.height * (2/3)

        anchors.left: tachometer.right

        maxValue: 120
        minValue: 0

        bottomValue: value
        bottomUnit: " mph"
    }

    TempCoolant {
        id: tempCoolant

        width: (parent.width/3) * (2/3)
        height: (parent.height) * (2/3)

        anchors.verticalCenter: speedometer.verticalCenter

        anchors.left: speedometer.right
        anchors.leftMargin: 50

        maxCoolantTemp: 250
        minCoolantTemp: 120
    }

    Rectangle {
        height: parent.height/3
        width: parent.width
        anchors.top: speedometer.bottom
        anchors.topMargin: -40
        color: "transparent"

        BoostGauge {
            id: boost

            height: parent.height
            width: parent.height

            anchors.right: oilP.left

            minValue: -20.0
            maxValue: 30.0
        }

        OilPressure {
            id: oilP

            height: parent.height
            width: parent.height

            anchors.right : oilT.left

            minValue: 0
            maxValue: 5.0
        }

        OilTemperature {
            id: oilT

            height: parent.height
            width: parent.height

            anchors.right: voltmeter.left

            minValue: 120
            maxValue: 300
        }

        Volts {
            id: voltmeter

            height: parent.height
            width: parent.height

            anchors.right : clock.left

            minValue: 10.0
            maxValue: 16.0
        }

        Clock {
            id: clock

            height: parent.height
            width: parent.height

            anchors.right: parent.right
            anchors.rightMargin: 20
        }
    }

    function setSpeedoTopValue(value, unit) {
        speedometer.topValue = value;
        speedometer.topUnit = unit;
    }

    function setSpeed(speed) {
        speedometer.value = speed;
    }

    function setRpm(rpm) {
        tachometer.value = rpm;
    }

    function setCoolantTemp(temp) {
        tempCoolant.coolantTemp = temp;
    }

    function setFuelLevel(level) {
        tempCoolant.fuelLevel = level;
    }

    function leftBlink(enable) {
        if( enable ) {
            leftTurn.startBlinker();
        }else{
            leftTurn.stopBlinker();
        }
    }

    function rightBlink(enable) {
        if( enable ) {
            rightTurn.startBlinker();
        }else{
            rightTurn.stopBlinker();
        }
    }

    function setBoost(pressure) {
        boost.value = pressure;
    }

    function setOilPressure(pressure) {
        oilP.value = pressure;
    }

    function setOilTemperature(temp) {
        oilT.value = temp;
    }

    function setVoltage(volts) {
        voltmeter.value = volts;
    }
}
