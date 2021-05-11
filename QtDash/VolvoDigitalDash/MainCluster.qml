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

    ColumnLayout {
        id:dashLayout
        spacing: 0
//        width: parent.width
//        height: parent.height

        anchors.fill: parent

        RowLayout {
            id:gaugeLayout
            width: parent.width
            height: parent.height
            spacing: 0


            Tacho {
                id: tachometer

                width: parent.width/3
                height: parent.height

                anchors.left: parent.left

                maxValue: 7000
                minValue: 0
            }


            Speedo {
                id: speedometer

                width: parent.width/3
                height: parent.height

                anchors.left: tachometer.right

                maxValue: 120
                minValue: 0

                bottomValue: value
                bottomUnit: " mph"
            }

            TempCoolant {
                id: tempCoolant

                width: parent.width/3
                height: parent.height - parent.height/8

                anchors.verticalCenter: parent.verticalCenter

                anchors.left: speedometer.right

                maxCoolantTemp: 250
                minCoolantTemp: 120
            }
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
}
