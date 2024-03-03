import QtQuick 2.15

Item {

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height * 0.73
        property real tachometerSize: parent.height * 0.575
        property real centerGaugeXOffset: speedometerSize * 0.5
        property real centerGaugeYOffset: -speedometerSize * 0.1

        property real largeGaugeNeedleWidth: 0.035
        property real largeGaugeNeedleLength: 0.45
        property real largeGaugeNeedleOffset: 0.075
        property real largeGaugeNeedleCenterRadius: 0.15

        property real smallGaugeSize: parent.height / 3
        property real smallGaugeVeritalMargin: parent.height * 0.02

        property real smallGaugeNeedleLength: 0.75
        property real smallGaugeNeedleWidth: 0.05;
        property real smallGaugeNeedleOffset: 0.125
        property real smallGaugeYOffset: 1.0 / 4.5
        property real smallGaugeNeedleCenterRadius: 0.25

        property bool speedoMph: speedoModel.units === "mph"

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

            id: tachContainer740
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.left: speedoContainer740.right
            anchors.verticalCenter: speedoContainer740.verticalCenter

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            id: clockContainer740
            anchors.right: speedoContainer740.left
            anchors.verticalCenter: speedoContainer740.verticalCenter
            height: container.tachometerSize
            width: container.tachometerSize
            color: "transparent"

            ClockLarge {
                anchors.fill: parent
                imageSource: "qrc:gauge-faces-740-940/740_clock.png"
                needleResource: "qrc:needles/needle-740-940.png"
            }
        }


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

            id: speedoContainer740
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }
        }


        Rectangle {
            AccessoryGaugeDelegate {
                id: boostDelegate
                imageSource: "qrc:/gauge-faces-740-940/740_boost.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                minAngle: -228
                maxAngle: 45


                needleWidth: container.smallGaugeNeedleWidth
                needleLength: 0.55
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: 0.0
            }


            id: boostContainer
            anchors.left: tachContainer740.right
            anchors.bottom: speedoContainer740.verticalCenter
            anchors.bottomMargin: container.smallGaugeVeritalMargin
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

                minAngle: -115
                maxAngle: -65

                imageSource: "qrc:/gauge-faces-740-940/740_coolant_temp.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
            }

            id: coolantTempContainer
            anchors.left: tachContainer740.right
            anchors.top: speedoContainer740.verticalCenter
            anchors.topMargin: container.smallGaugeVeritalMargin
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

                minAngle: -115
                maxAngle: -65

                imageSource: "qrc:/gauge-faces-740-940/740_fuel.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
            }

            id: fuelLevelContainer
            anchors.right: clockContainer740.left
            anchors.top: speedoContainer740.verticalCenter
            anchors.topMargin: container.smallGaugeVeritalMargin
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate.component
            }
        }



        Rectangle {
            AccessoryGaugeDelegate {
                id: voltMeterDelegate

                minAngle: -130
                maxAngle: -55

                imageSource: "qrc:/gauge-faces-740-940/740_voltmeter.png"
                needleResource: "qrc:/needles/needle-740-940.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
            }

            id: voltContainer740
            anchors.right: clockContainer740.left
            anchors.bottom: speedoContainer740.verticalCenter
            anchors.bottomMargin: container.smallGaugeVeritalMargin
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: voltMeterModel
                delegate: voltMeterDelegate.component
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize
            anchors.top: speedoContainer740.top
            anchors.topMargin: container.smallGaugeVeritalMargin
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -blinkerSize * 4
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize
            anchors.top: speedoContainer740.top
            anchors.topMargin: container.smallGaugeVeritalMargin
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize * 4
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }


    }
}
