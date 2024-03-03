import QtQuick 2.15

Item {
    id: container

    // 544 style delegates
    SpeedoDelegate544Style {
        id: speedoDelegate544
    }

    TachoDelegate544Style {
        id: rpmDelegate544
    }

    property int spacing: 300
    property int smallGaugeSpacing: 50

    property real speedometerWidth: parent.height * (1100/480)
    property real speedometerHeight: parent.height * (65/480)

    property real tachometerSize: parent.height * 0.575

    property real largeGaugeNeedleWidth: 0.035
    property real largeGaugeNeedleLength: 0.45
    property real largeGaugeNeedleOffset: 0.075
    property real largeGaugeNeedleCenterRadius: 0.15

    property real smallGaugeSize: parent.height * (140/480)
    property real smallGaugeVeritalMargin: parent.height * 0.02

    property real smallGaugeNeedleLength: 0.75
    property real smallGaugeNeedleWidth: 0.05;
    property real smallGaugeNeedleOffset: 0.125
    property real smallGaugeYOffset: 1.0 / 4.0
    property real smallGaugeNeedleCenterRadius: 0.15
    property real smallGaugeTextYOffset: -0.5

    Rectangle {
        width: parent.width
        height: parent.height
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

            AccessoryGaugeDelegate {
                id: voltMeterDelegate

                minAngle: -130
                maxAngle: -55

                imageSource: "qrc:/gauge-faces-544/battery-544.png"
                needleResource: "qrc:/needles/needle-544-140.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset

                textOffset: container.smallGaugeTextYOffset
            }

            ListView {
                model: voltMeterModel
                delegate: voltMeterDelegate.component
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

            AccessoryGaugeDelegate {
                id: coolantTempDelegate

                minAngle: -130
                maxAngle: -55

                imageSource: "qrc:/gauge-faces-544/coolant-temp-544.png"
                needleResource: "qrc:/needles/needle-544-140.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
                textOffset: container.smallGaugeTextYOffset
            }

            ListView {
                model: coolantTempModel
                delegate: coolantTempDelegate.component
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

            AccessoryGaugeDelegate {
                id: oilPressureDelegate

                minAngle: -130
                maxAngle: -55

                imageSource: "qrc:/gauge-faces-544/oil-pressure-544.png"
                needleResource: "qrc:/needles/needle-544-140.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
                textOffset: container.smallGaugeTextYOffset
            }

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate.component
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

            AccessoryGaugeDelegate {
                id: fuelLevelDelegate

                minAngle: -130
                maxAngle: -55

                imageSource: "qrc:/gauge-faces-544/fuel-544.png"
                needleResource: "qrc:/needles/needle-544-140.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
                textOffset: container.smallGaugeTextYOffset
            }

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate.component
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
            width: blinkerSize
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize * 3
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -blinkerSize * 3
            anchors.verticalCenter: rightBlinker.verticalCenter
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }


    }
}
