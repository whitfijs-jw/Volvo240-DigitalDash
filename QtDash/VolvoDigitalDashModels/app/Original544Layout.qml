import QtQuick 2.15

Item {
    property int spacing: 300
    property int smallGaugeSpacing: 50

    Rectangle {
        width: 1280
        height: 480
        color: "transparent"


        Rectangle {
            id: speedoContainer
            width: linearSpeedoWidth
            height: linearSpeedoHeight
            anchors.top: parent.top
            anchors.topMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            /* Speed: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate544
            }

            Image {
                source: "qrc:/gauge-faces-544/speedo-544-outer.png"
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

            }

        }

        Rectangle {
            id: voltContainer544
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -spacing

            anchors.top: speedoContainer.bottom
            anchors.topMargin: 50

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: voltMeterModel
                delegate: voltMeterDelegate544
            }

            Rectangle {
                width: parent.width
                height: parent.height / 3.0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                color: "black"
            }

            Image {
                source: "qrc:/gauge-faces-544/small-gauge-shroud-544.png"
                anchors.top: parent.top
                anchors.topMargin: 17
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: coolantTempContainer544
            anchors.verticalCenter: voltContainer544.verticalCenter

            anchors.right: voltContainer544.left
            anchors.rightMargin: smallGaugeSpacing

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: coolantTempModel
                delegate: coolantTempDelegate544
            }

            Rectangle {
                width: parent.width
                height: parent.height / 3.0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                color: "black"
            }

            Image {
                source: "qrc:/gauge-faces-544/small-gauge-shroud-544.png"
                anchors.top: parent.top
                anchors.topMargin: 17
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: oilPressureContainer544
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: spacing

            anchors.verticalCenter: voltContainer544.verticalCenter

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate544
            }

            Rectangle {
                width: parent.width
                height: parent.height / 3.0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                color: "black"
            }

            Image {
                source: "qrc:/gauge-faces-544/small-gauge-shroud-544.png"
                mirror: true
                anchors.top: parent.top
                anchors.topMargin: 17
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: fuelLevelContainer544

            anchors.verticalCenter: voltContainer544.verticalCenter

            anchors.left: oilPressureContainer544.right
            anchors.leftMargin: smallGaugeSpacing

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate544
            }

            Rectangle {
                width: parent.width
                height: parent.height / 3.0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 15
                color: "black"
            }

            Image {
                source: "qrc:/gauge-faces-544/small-gauge-shroud-544.png"
                mirror: true
                anchors.top: parent.top
                anchors.topMargin: 17
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Rectangle {
            id: tachoContainer
            width: 600
            height: 64
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: voltContainer544.bottom
            anchors.topMargin: -40

            color: "transparent"

            /* rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegate544
            }


            Image {
                source: "qrc:/gauge-faces-544/tachometer-544-outer.png"
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

            }

        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize * 2
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width / 6
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
            anchors.horizontalCenterOffset: -parent.width / 8
            anchors.verticalCenter: rightBlinker.verticalCenter
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }


    }
}
