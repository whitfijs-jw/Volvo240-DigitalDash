import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    id: tempCoolant
    property int maxCoolantTemp
    property int minCoolantTemp
    property int highAlarm

    property int maxFuel: 100
    property int minFuel: 0
    property int lowAlarm

    property real coolantTemp
    property real fuelLevel

    property string units

    Image {
        z: 0;
        source: "qrc:mainCluster/temp_coolant_overlay_small.png"
        anchors.fill: parent
    }

//    Image {
//        z: -2;
//        source: "qrc:mainCluster/temp_coolant.png"
//        anchors.fill: parent
//    }

    Image {
        z: 1;
        source: "qrc:mainCluster/temp_coolant_gas_can.png"
        anchors.fill: parent
        visible: fuelLevel < lowAlarm ? true : false
    }

    Gauge {
        id: coolant
        z: -1

        anchors.fill: parent

        value: tempCoolant.coolantTemp

        lowAlarm: 0
        highAlarm: tempCoolant.highAlarm

        maxValue: tempCoolant.maxCoolantTemp
        minValue: tempCoolant.minCoolantTemp

        minAngle: -205
        maxAngle: -155

        units: "F"
        needleLength: parent.height * 0.4
        needleWidth: parent.height * 0.015
        needleOffset: 0

        imageResource: "qrc:mainCluster/temp_coolant.png"

        textOffset: parent.height / 5
        textSize: parent.height / 16

    }

    Gauge {
        id: fuel
        z: -1
        anchors.fill: parent

        value: tempCoolant.maxFuel - tempCoolant.fuelLevel
        units: ""

        minValue: tempCoolant.minFuel
        maxValue: tempCoolant.maxFuel

        highAlarm: tempCoolant.maxFuel
        lowAlarm: tempCoolant.lowAlarm

        minAngle: -27
        maxAngle: 25

        needleLength: parent.height * 0.40
        needleWidth: parent.height * 0.015
        needleOffset: 0

        imageResource: ""

        textEnabled: false
    }
}

