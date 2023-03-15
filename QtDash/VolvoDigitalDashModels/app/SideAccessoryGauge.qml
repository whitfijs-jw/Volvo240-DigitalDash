import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var initalModel: boostModel
    property Component initialDelegate: boostDelegate240

    Rectangle {
        id: gaugeContainer
        anchors.fill: parent
        color: "transparent"

        ListView {
            id: gaugeTop
            model: initalModel
            delegate: initialDelegate
        }

        MouseArea {
            anchors.fill: parent
            onPressAndHold: {
                contextMenu.popup()
            }

            Menu {
                id: contextMenu
                MenuItem {
                    text: "boost"
                    onTriggered: {
                        gaugeTop.model = boostModel
                        gaugeTop.delegate = boostDelegate240
                    }
                }
                MenuItem {
                    text: "oil temp"
                    onTriggered: {
                        gaugeTop.model = oilTModel
                        gaugeTop.delegate = oilTemperatureDelegate240
                    }
                }
                MenuItem {
                    text: "oil pressure"
                    onTriggered: {
                        gaugeTop.model = oilPModel
                        gaugeTop.delegate = oilPressureDelegate240
                    }
                }
                MenuItem {
                    text: "voltmeter"
                    onTriggered: {
                        gaugeTop.model = voltMeterModel
                        gaugeTop.delegate = voltMeterDelegate240
                    }
                }

                MenuItem {
                    text: "clock"
                    onTriggered: {
                        gaugeTop.model = boostModel
                        gaugeTop.delegate = clockDelegate240
                    }
                }
            }
        }
    }
}
