import QtQuick 2.15

Item {
    property int spacing: 300
    property int smallGaugeSpacing: 50

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"


        property real speedometerSize: parent.height * 0.925
        property real tachometerSize: speedometerSize
        property real centerGaugeXOffset: speedometerSize * 0.575
        property real needleCenterCoverSize: speedometerSize * 0.1955

        property real largeGaugeNeedleWidth: 0.025
        property real largeGaugeNeedleLength: 0.375
        property real largeGaugeNeedleOffset: 0.0
        property real largeGaugeNeedleCenterRadius: 0.125
        property real largeGaugeTestSize: .05

        property real smallGaugeSize: parent.height / 2.4
        property real smallGaugeVeritalMargin: parent.height * (70/480)
        property real smallGaugeXOffset: smallGaugeSize * 0.2
        property real needleCenterCoverSizeSmall: smallGaugeSize * (39.0/200.0)

        property real smallgaugeNeedleWidth: 0.04
        property real smallgaugeNeedleLength: .375
        property real smallgaugeNeedleOffset: 0.0
        property real smallgaugeNeedleCenterRadius: 0.05
        property real smallgaugeNeedleYOffset: 0

        property real centerGaugeHeight: parent.height / 1.2
        property real centerGaugeYOffset: -parent.height / 24
        property real coolantTempYOffset: -parent.height * (95/480)
        property real oilTempYOffset: parent.height * (97/480)

        Rectangle {
            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: container.centerGaugeXOffset
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: 0

                minAngle: -225
                maxAngle: 40

                imageSource: "qrc:/gauge-faces-p1800/speedo-mph-p1800.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                textSize: container.largeGaugeTestSize

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }


            /* Speed: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }

            Image {
                anchors.horizontalCenter: speedoContainer.horizontalCenter
                anchors.verticalCenter: speedoContainer.verticalCenter
                source: "qrc:/gauge-faces-p1800/center-cover-p1800.png"

                width: container.needleCenterCoverSize
                height: container.needleCenterCoverSize
            }
        }

        Rectangle {
            id: tachoContainer
            width: container.tachometerSize
            height: container.tachometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -container.centerGaugeXOffset
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            TachometerDelegate {
                id: tachometerDelegate

                minAngle: -221
                maxAngle: 35

                imageSource: "qrc:/gauge-faces-p1800/tach-p1800.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                textSize: container.largeGaugeTestSize

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            /* rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

            Image {
                anchors.horizontalCenter: tachoContainer.horizontalCenter
                anchors.verticalCenter: tachoContainer.verticalCenter
                source: "qrc:/gauge-faces-p1800/center-cover-p1800.png"

                width: container.needleCenterCoverSize
                height: container.needleCenterCoverSize
            }

        }

        Rectangle {
            id: centerGaugeContainer
            height: container.centerGaugeHeight
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: container.centerGaugeYOffset
            anchors.horizontalCenter: parent.horizontalCenter

            color: "transparent"

            Rectangle {
                height: container.height / 24
                width: container.height / 3.84

                LinearGaugeDelegate {
                    id: coolantTempDelegate

                    minValue: 90
                    maxValue: 230
                }

                ListView {
                    model: coolantTempModel
                    delegate: coolantTempDelegate.component
                }
                rotation: -90
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: container.coolantTempYOffset
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                height: container.height / 24
                width: container.height / 3.84

                LinearGaugeDelegate {
                    id: oilTempDelegate

                    minValue: 140
                    maxValue: 280

                    needleColor: "lightseagreen"

                    textYOffset: -0.7
                }

                ListView {
                    model: oilTModel
                    delegate: oilTempDelegate.component
                }
                rotation: -90
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: container.oilTempYOffset
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/gauge-faces-p1800/oil-coolant-temp-p1800.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Rectangle {
            id: fuelLevelContainer
            width: container.smallGaugeSize
            height: container.smallGaugeSize

            anchors.left: speedoContainer.right
            anchors.leftMargin: -container.smallGaugeXOffset
            anchors.bottom: parent.bottom
            anchors.bottomMargin: container.smallGaugeVeritalMargin

            color: "transparent"

            AccessoryGaugeDelegate {
                id: fuelLevelDelegate

                imageSource: "qrc:/gauge-faces-p1800/fuel-level-p1800.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                minAngle: -145
                maxAngle: -35

                needleWidth: container.smallgaugeNeedleWidth
                needleLength: container.smallgaugeNeedleLength
                needleOffset: container.smallgaugeNeedleOffset
                needleCenterRadius: container.smallgaugeNeedleCenterRadius
                yOffset: container.smallgaugeNeedleYOffset

                significatDigits: 0
            }

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate.component
            }

            Image {
                anchors.centerIn: parent
                source: "qrc:/gauge-faces-p1800/center-cover-small-p1800.png"
                width: container.needleCenterCoverSizeSmall
                height: container.needleCenterCoverSizeSmall
            }


        }

        Rectangle {
            id: oilPressureContainer
            width: container.smallGaugeSize
            height: container.smallGaugeSize

            anchors.right: tachoContainer.left
            anchors.rightMargin: -container.smallGaugeXOffset
            anchors.bottom: parent.bottom
            anchors.bottomMargin: container.smallGaugeVeritalMargin

            color: "transparent"

            AccessoryGaugeDelegate {
                id: oilPressureDelegate

                imageSource: "qrc:/gauge-faces-p1800/oil-pressure-p1800.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                gaugeMax: 6.0

                minAngle: -145
                maxAngle: -35

                needleWidth: container.smallgaugeNeedleWidth
                needleLength: container.smallgaugeNeedleLength
                needleOffset: container.smallgaugeNeedleOffset
                needleCenterRadius: container.smallgaugeNeedleCenterRadius
                yOffset: container.smallgaugeNeedleYOffset
            }

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate.component
            }

            Image {
                anchors.centerIn: parent
                source: "qrc:/gauge-faces-p1800/center-cover-small-p1800.png"
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
            anchors.horizontalCenterOffset: - blinkerSize * 3
            anchors.verticalCenter: rightBlinker.verticalCenter
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }


    }
}
