import QtQuick 2.15

Item {

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height * 0.73
        property real tachometerSize: speedometerSize

        property real centerGaugeXOffset: -speedometerSize / 1.85
        property real centerGaugeYOffset: -speedometerSize / 10

        property real largeGaugeNeedleWidth: 0.0325
        property real largeGaugeNeedleLength: 0.55
        property real largeGaugeNeedleOffset: 0.1
        property real largeGaugeNeedleCenterRadius: 0.2

        property real smallGaugeSize: parent.height / 2.4

        property real smallGaugeNeedleLength: 0.7
        property real smallGaugeNeedleWidth: 0.05;
        property real smallGaugeNeedleOffset: 0.175
        property real smallGaugeYOffset: 0.25
        property real smallGaugeNeedleCenterRadius: 0.25

        property real smallGaugeTextOffset: 0.575

        property bool speedoMph: speedoModel.units === "mph"
        property bool coolantTempF: coolantTempModel.units === "F"
        property bool oilPressureBar: oilPModel.units === "bar"

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: 0

                minAngle: -210
                maxAngle: 30

                imageSource: container.speedoMph ?
                                "qrc:/gauge-faces-s60r/s60r_speedo.png" :
                                "qrc:/gauge-faces-s60r/s60r_speedo_kmh.png"
                needleResource: "qrc:/needles/needle_s60r.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius

                needleCenterImageSize: 0.2
                needleCenterUseImage: true
                needleCenterImageSource: "qrc:/needles/needle_center_s60r.png"

                textSize: .05
                textOffset: 0.2
                significatDigits: 0

                topTextSize: .05
                topTextOffset: 1 / 3.5
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

                initialValueOffset: 0

                minAngle: -210
                maxAngle: 30

                imageSource: "qrc:/gauge-faces-s60r/s60r_tach.png"
                needleResource: "qrc:/needles/needle_s60r.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius

                needleCenterImageSize: 0.2
                needleCenterUseImage: true
                needleCenterImageSource: "qrc:/needles/needle_center_s60r.png"

                textSize: 0.05
                textOffset: 0.2
                significatDigits: 0
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
            width: container.smallGaugeSize
            height: container.smallGaugeSize
            color: "transparent"
            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.left: tachContainer.right
            anchors.leftMargin: 25

            Rectangle {
                id: fuelLevelContainer
                AccessoryGaugeDelegate {
                    id: fuelLevelDelegate

                    minAngle: -130
                    maxAngle: -50

                    imageSource: "qrc:/gauge-faces-s60r/s60r_fuel_level.png"
                    needleResource: "qrc:/needles/needle_s60r.png"

                    needleWidth: container.smallGaugeNeedleWidth
                    needleLength: container.smallGaugeNeedleLength
                    needleOffset: container.smallGaugeNeedleOffset
                    needleCenterRadius: container.smallGaugeNeedleCenterRadius
                    needleCenterImageSize: 0.35
                    needleCenterUseImage: true
                    needleCenterImageSource: "qrc:/needles/needle_center_s60r.png"

                    yOffset: container.smallGaugeYOffset

                    significatDigits: 0
                    textOffset: container.smallGaugeTextOffset
                }


                anchors.fill: parent
                color: "transparent"

                ListView {
                    model: fuelLevelModel
                    delegate: fuelLevelDelegate.component
                }
            }
        }

        Rectangle {
            id: coolantTempContainer
            width: container.smallGaugeSize
            height: container.smallGaugeSize
            color: "transparent"
            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.right: speedoContainer.left
            anchors.rightMargin: 25
            Rectangle {
                AccessoryGaugeDelegate {
                    id: coolantTempDelegate

                    minAngle: -130
                    maxAngle: -50

                    imageSource: "qrc:/gauge-faces-s60r/s60r_coolant_temp.png"
                    needleResource: "qrc:/needles/needle_s60r.png"

                    needleWidth: container.smallGaugeNeedleWidth
                    needleLength: container.smallGaugeNeedleLength
                    needleOffset: container.smallGaugeNeedleOffset
                    needleCenterRadius: container.smallGaugeNeedleCenterRadius
                    needleCenterImageSize: 0.35
                    needleCenterUseImage: true
                    needleCenterImageSource: "qrc:/needles/needle_center_s60r.png"

                    yOffset: container.smallGaugeYOffset

                    significatDigits: 0
                    textOffset: container.smallGaugeTextOffset
                }


                anchors.fill: parent
                color: "transparent"

                ListView {
                    model: coolantTempModel
                    delegate: coolantTempDelegate.component
                }
            }
        }


        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -20
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
            anchors.horizontalCenterOffset: blinkerSize+20
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }


    }
}
