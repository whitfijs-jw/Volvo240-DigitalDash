import QtQuick 2.15

Item {
    property int spacing: 300
    property int smallGaugeSpacing: 50

    Rectangle {
        id: container
        width: 1280
        height: 480
        color: "transparent"


        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: width * 0.575
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            /* Speed: */
            ListView {
                model: speedoModel
                delegate: speedoDelegateP1800
            }

            Image {
                anchors.horizontalCenter: speedoContainer.horizontalCenter
                anchors.verticalCenter: speedoContainer.verticalCenter
                source: "qrc:/gauge-faces-p1800/center-cover-p1800.png"
            }
        }

        Rectangle {
            id: tachoContainer
            width: speedoSize
            height: speedoSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -width * 0.575
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            /* rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegateP1800
            }

            Image {
                anchors.horizontalCenter: tachoContainer.horizontalCenter
                anchors.verticalCenter: tachoContainer.verticalCenter
                source: "qrc:/gauge-faces-p1800/center-cover-p1800.png"
            }

        }

        Rectangle {
            id: centerGaugeContainer
            height: 400
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -20
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            Rectangle {
                ListView {
                    model: coolantTempModel
                    delegate: coolantTempDelegateP1800
                }
                rotation: -90
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -33
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -12
            }

            Rectangle {
                ListView {
                    model: oilTModel
                    delegate: oilTempDelegateP1800
                }
                rotation: -90
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 160
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.horizontalCenterOffset: -11
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/gauge-faces-p1800/oil-coolant-temp-p1800.png"
            }
        }

        Rectangle {
            id: fuelLevelContainer
            width: 200
            height: 200

            anchors.horizontalCenter: speedoContainer.horizontalCenter
            anchors.left: speedoContainer.right
            anchors.leftMargin: -30

            color: "transparent"

            Image {
                source: "qrc:/gauge-faces-p1800/fuel-level-p1800.png"
            }


        }

        Rectangle {
            id: oilPressureContainer
            width: 200
            height:200

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.right: container.right

            color: "transparent"

            Image {
                width: 200
                height:200
                source: "qrc:/gauge-faces-p1800/oil-pressure-p1800.png"
            }

        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize * 2
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width / 8
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -parent.width / 8 + (blinkerSize)
            anchors.verticalCenter: rightBlinker.verticalCenter
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }


    }
}
