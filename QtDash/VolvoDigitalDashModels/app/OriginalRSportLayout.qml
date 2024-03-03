import QtQuick 2.15

Item {

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height * 0.73
        property real tachometerSize: speedometerSize
        property real centerGaugeXOffset: speedometerSize * 0.5
        property real centerGaugeYOffset: -speedometerSize * 0.1

        property real largeGaugeNeedleWidth: 0.025
        property real largeGaugeNeedleLength: 0.525
        property real largeGaugeNeedleOffset: 0.1
        property real largeGaugeNeedleCenterRadius: 0.125


        property real smallGaugeSize: parent.height / 2.4
        property real lowerSmallGaugeYOffset: smallGaugeSize * 0.45
        property real upperSmallGaugeYOffset: smallGaugeSize * 0.5
        property real lowerSmallGaugeXOffset: smallGaugeSize * 0.15
        property real upperSmallGaugeXOffset: smallGaugeSize * 0.25

        property real smallGaugeNeedleLength: 0.65
        property real smallGaugeNeedleWidth: 0.035;
        property real smallGaugeNeedleOffset: 0.125
        property real smallGaugeYOffset: 0.0
        property real smallGaugeXOffset: -(1 / 7.4)
        property real smallUnshroudedXOffset: -(1 / 4.65)
        property real smallGaugeNeedleCenterRadius: 0.15

        property bool speedoMph: speedoModel.units === "mph"

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: container.speedoMph? 10 : 20

                minAngle: -148
                maxAngle: 128

                imageSource: container.speedoMph ?
                                 "qrc:/gauge-faces-r-sport/r_sport_speedo_mph.png" :
                                 "qrc:/gauge-faces-r-sport/r_sport_speedo_kph.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: container.centerGaugeXOffset
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: container.centerGaugeYOffset
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

                initialValueOffset: 400

                minAngle: -140
                maxAngle: 126

                imageSource: "qrc:/gauge-faces-r-sport/r_sport_tachometer.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }


            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -container.centerGaugeXOffset
            anchors.verticalCenter: speedoContainer.verticalCenter

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            height: container.smallGaugeSize
            width: container.smallGaugeSize

            anchors.right: tachContainer.left
            anchors.rightMargin: -container.upperSmallGaugeXOffset

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: container.lowerSmallGaugeYOffset

            color: "transparent"

            Rectangle {
                AccessoryGaugeDelegate {
                    id: coolantTempDelegate

                    minAngle: -35
                    maxAngle: 38

                    clockwise: false

                    imageSource: "qrc:/gauge-faces-r-sport/r_sport_coolant_fahrenhet.png"
                    needleResource: "qrc:/needles/needle-rsport.png"

                    needleWidth: container.smallGaugeNeedleWidth
                    needleLength: container.smallGaugeNeedleLength
                    needleOffset: container.smallGaugeNeedleOffset
                    needleCenterRadius: container.smallGaugeNeedleCenterRadius
                    yOffset: container.smallGaugeYOffset
                    xOffset: container.smallGaugeXOffset

                    significatDigits: 0
                }

                id: coolantTempContainer
                anchors.fill: parent
                color: "transparent"

                ListView {
                    model: coolantTempModel
                    delegate: coolantTempDelegate.component
                }
            }

            Image {
                anchors.fill: parent
                source: "qrc:/gauge-faces-r-sport/r_sport_coolant_fahrenheit_shroud.png"
                cache: true
            }
        }

        Rectangle {
            anchors.left: speedoContainer.right
            anchors.leftMargin: -container.upperSmallGaugeXOffset

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: container.lowerSmallGaugeYOffset

            height: container.smallGaugeSize
            width: container.smallGaugeSize

            color: "transparent"

            Rectangle {
                id: fuelLevelContainer
                AccessoryGaugeDelegate {
                    id: fuelLevelDelegate

                    minAngle: -40
                    maxAngle: 40

                    clockwise: false

                    imageSource: "qrc:/gauge-faces-r-sport/r_sport_fuel.png"
                    needleResource: "qrc:/needles/needle-rsport.png"

                    needleWidth: container.smallGaugeNeedleWidth
                    needleLength: container.smallGaugeNeedleLength
                    needleOffset: container.smallGaugeNeedleOffset
                    needleCenterRadius: container.smallGaugeNeedleCenterRadius
                    yOffset: container.smallGaugeYOffset
                    xOffset: container.smallGaugeXOffset


                    significatDigits: 0
                }


                anchors.fill: parent
                color: "transparent"

                ListView {
                    model: fuelLevelModel
                    delegate: fuelLevelDelegate.component
                }
            }

            Image {
                anchors.fill: parent
                source: "qrc:/gauge-faces-r-sport/r_sport_fuel_shroud.png"
                cache: true
            }
        }

        Rectangle {
            id: oilPContainer

            AccessoryGaugeDelegate {
                id: oilPressureDelegate

                minAngle: -48
                maxAngle: 48

                clockwise: false

                imageSource: "qrc:/gauge-faces-r-sport/r_sport_oil_pressure_5bar.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
                xOffset: container.smallUnshroudedXOffset


                significatDigits: 1
            }


            anchors.left: speedoContainer.right
            anchors.leftMargin: container.upperSmallGaugeXOffset

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: -container.upperSmallGaugeYOffset

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate.component
            }
        }

        Rectangle {
            id: voltContainer

            AccessoryGaugeDelegate {
                id: voltmeterDelegate

                minAngle: -48
                maxAngle: 48

                clockwise: false

                imageSource: "qrc:/gauge-faces-r-sport/r_sport_voltmeter.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.smallGaugeNeedleWidth
                needleLength: container.smallGaugeNeedleLength
                needleOffset: container.smallGaugeNeedleOffset
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset
                xOffset: container.smallUnshroudedXOffset


                significatDigits: 1
            }

            anchors.right: tachContainer.left
            anchors.rightMargin: container.upperSmallGaugeXOffset

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: -container.upperSmallGaugeYOffset

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                id: gaugeVolt
                model: voltMeterModel
                delegate: voltmeterDelegate.component
            }
        }


        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -10
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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize+10
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }


    }
}
