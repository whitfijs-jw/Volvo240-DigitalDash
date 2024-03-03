import QtQuick 2.15

Item {

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height / 1.2
        property real tachometerSize: parent.height * 0.73

        property real largeGaugeNeedleWidth: 0.035
        property real largeGaugeNeedleLength: 0.45
        property real largeGaugeNeedleOffset: 0.075
        property real largeGaugeNeedleCenterRadius: 0.15

        property real smallGaugeSize: parent.height / 2.4
        property real smallgaugeXOffset: smallGaugeSize * 0.325
        property real smallgaugeYOffset: smallGaugeSize * 0.4

        property real smallgaugeNeedleWidth: 0.05
        property real smallgaugeNeedleLength: 0.5
        property real smallgaugeNeedleOffset: 0.125
        property real smallgaugeNeedleCenterRadius: .25
        property real smallgaugeNeedleYOffset: 0

        property bool speedoMph: speedoModel.units === "mph"

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: container.speedoMph ? 2 : 8

                minAngle: container.speedoMph ? -227 : -232
                maxAngle: container.speedoMph ? 45 : 46

                imageSource: container.speedoMph ?
                                 "qrc:/gauge-faces-740-940/740_speedo.png" :
                                 "qrc:/gauge-faces-740-940/740_speedo_kph.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }
        }


        Rectangle {
            TachometerDelegate {
                id: tachometerDelegate

                imageSource: "qrc:/gauge-faces-740-940/740_tach.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }


            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.left: speedoContainer.right
            anchors.leftMargin: container.tachometerSize / 8
            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: container.tachometerSize * 0.10

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            width: container.tachometerSize
            height: container.tachometerSize
            anchors.right: speedoContainer.left
            anchors.rightMargin: container.tachometerSize / 8
            anchors.verticalCenter: tachContainer.verticalCenter
            anchors.verticalCenterOffset: -container.smallGaugeSize * 0.1
            color: "transparent"

            Rectangle {
                AccessoryGaugeDelegate {
                    id: boostDelegate

                    imageSource: "qrc:/gauge-faces-850/850_boost.png"
                    needleResource: "qrc:/needles/needle-740-940.png"

                    minAngle: -140
                    maxAngle: -41

                    needleWidth: container.smallgaugeNeedleWidth
                    needleLength: container.smallgaugeNeedleLength
                    needleOffset: container.smallgaugeNeedleOffset
                    needleCenterRadius: container.smallgaugeNeedleCenterRadius
                    yOffset: container.smallgaugeNeedleYOffset

                    textOffset: 0.75
                }

                id: boostContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -container.smallgaugeYOffset
                height: container.smallGaugeSize
                width: container.smallGaugeSize
                color: "transparent"

                ListView {
                    model: boostModel
                    delegate: boostDelegate.component
                }
            }

            Rectangle {
                AccessoryGaugeDelegate {
                    id: coolantTempDelegate

                    imageSource: "qrc:/gauge-faces-850/850_coolant.png"
                    needleResource: "qrc:/needles/needle-740-940.png"

                    clockwise: false

                    minAngle: -45
                    maxAngle: 45

                    needleWidth: container.smallgaugeNeedleWidth
                    needleLength: container.smallgaugeNeedleLength
                    needleOffset: container.smallgaugeNeedleOffset
                    needleCenterRadius: container.smallgaugeNeedleCenterRadius
                    yOffset: container.smallgaugeNeedleYOffset

                    significatDigits: 0
                }

                id: coolantTempContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: container.smallgaugeXOffset
                height: container.smallGaugeSize
                width: container.smallGaugeSize
                color: "transparent"

                ListView {
                    model: coolantTempModel
                    delegate: coolantTempDelegate.component
                }
            }

            Rectangle {
                AccessoryGaugeDelegate {
                    id: fuelLevelDelegate

                    imageSource: "qrc:/gauge-faces-850/850_fuel_level.png"
                    needleResource: "qrc:/needles/needle-740-940.png"

                    minAngle: -225
                    maxAngle: -135

                    needleWidth: container.smallgaugeNeedleWidth
                    needleLength: container.smallgaugeNeedleLength
                    needleOffset: container.smallgaugeNeedleOffset
                    needleCenterRadius: container.smallgaugeNeedleCenterRadius
                    yOffset: container.smallgaugeNeedleYOffset

                    significatDigits: 0
                }

                id: fuelLevelContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: -container.smallgaugeXOffset
                height: container.smallGaugeSize
                width: container.smallGaugeSize
                color: "transparent"

                ListView {
                    model: fuelLevelModel
                    delegate: fuelLevelDelegate.component
                }
            }


        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -parent.width / 8
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width / 6
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }


    }
}
