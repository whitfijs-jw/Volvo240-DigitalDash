import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item {
    id: container
    width: 1280
    height: 480

    Rectangle {
        id: background
        color: "black"
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            id: row1
            height: parent.height/2
            width: parent.width

            BoostGauge {
                id: boost

                height: parent.height
                width: parent.height

                anchors.left: parent.left
                anchors.leftMargin: 40

                minValue: -20.0
                maxValue: 30.0
            }

            OilPressure {
                id: oilP

                height: parent.height
                width: parent.height

                anchors.left : boost.right

                minValue: 0
                maxValue: 5.0
            }

            OilTemperature {
                id: oilT

                height: parent.height
                width: parent.height

                anchors.left : oilP.right

                minValue: 120
                maxValue: 300
            }

            Volts {
                id: voltmeter

                height: parent.height
                width: parent.height

                anchors.left : oilT.right

                minValue: 10.0
                maxValue: 16.0
            }

            Clock {
                id: clock

                height: parent.height
                width: parent.height

                anchors.left: voltmeter.right
            }

//            AmbientTemp {
//                id: ambientTemperature

//                height: parent.height
//                width: parent.height

//                anchors.left: clock.right

//                minValue: 0
//                maxValue: 100
//            }
        }

        RowLayout {
            id: row2
            height: parent.height/2
            width: parent.width

//            Volts {
//                id: voltmeter

//                height: parent.height
//                width: parent.height

//                anchors.left : parent.left

//                minValue: 10.0
//                maxValue: 16.0
//            }

//            Clock {
//                id: clock

//                height: parent.height
//                width: parent.height

//                anchors.left: voltmeter.right
//            }

//            AmbientTemp {
//                id: ambientTemperature

//                height: parent.height
//                width: parent.height

//                anchors.left: clock.right

//                minValue: 0
//                maxValue: 100
//            }
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

//    function setAmbientTemperature(temp) {
//        ambientTemperature.value = temp;
//    }
}
