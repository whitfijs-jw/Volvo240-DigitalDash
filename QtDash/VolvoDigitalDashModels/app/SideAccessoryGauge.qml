import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var initalModel: boostModel
    property Component initialDelegate: boostDelegate240

    Rectangle {
        id: gaugeContainer
        anchors.fill: parent
        color: "transparent"
        z:0

        ListView {
            id: gaugeTop
            model: initalModel
            delegate: initialDelegate
            z:0
        }

        MouseArea {
            anchors.fill: parent
            onPressAndHold: {
                selectionMenu.x = mouse.x;
                selectionMenu.y = mouse.y;
                selectionMenu.visible = true;
            }
            Column {
                id: selectionMenu

                width: parent.width / 2
                height: parent.width / 2

                spacing: 2
                visible: false;

                Rectangle {
                    id: firstButton
                    width: parent.width
                    height: parent.height / 5;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("boost")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = boostModel;
                            gaugeTop.delegate = boostDelegate240;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 5;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("oil temp")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = oilTModel
                            gaugeTop.delegate = oilTemperatureDelegate240
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 5;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("oil pressure")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = oilPModel
                            gaugeTop.delegate = oilPressureDelegate240
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 5;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("voltmeter")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = voltMeterModel;
                            gaugeTop.delegate = voltMeterDelegate240;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / 5;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("clock")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = boostModel;
                            gaugeTop.delegate = clockDelegate240;
                            selectionMenu.visible = false;
                        }
                    }
                }
            }
        }
    }
}
