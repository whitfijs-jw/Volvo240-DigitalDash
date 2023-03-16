import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property var initalModel: boostModel
    property Component initialDelegate: boostDelegate740
    property int numGauges: 6

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
                selectionMenu.x = mouse.x - selectionMenu.width / 2.0;
                selectionMenu.y = mouse.y - selectionMenu.height / 2.0;
                selectionMenu.visible = true;
            }
            Column {
                id: selectionMenu

                width: parent.width / 1.5
                height: parent.width / 1.5

                spacing: 2
                visible: false;


                Rectangle {
                    id: firstButton
                    width: parent.width
                    height: parent.height / numGauges;
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
                            gaugeTop.delegate = boostDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / numGauges;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("oil temp")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = oilTModel;
                            gaugeTop.delegate = oilTempDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / numGauges;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("oil pressure")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = oilPModel;
                            gaugeTop.delegate = oilPressureDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / numGauges;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("coolant temp")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = coolantTempModel;
                            gaugeTop.delegate = coolantDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / numGauges;
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
                            gaugeTop.delegate = voltMeterDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
                Rectangle {
                    width: parent.width
                    height: parent.height / numGauges;
                    color: "white"
                    z: 100
                    Text {
                        text: qsTr("fuel level")
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            gaugeTop.model = fuelLevelModel;
                            gaugeTop.delegate = fuelLevelDelegate740;
                            selectionMenu.visible = false;
                        }
                    }
                }
            }
        }
    }
}
