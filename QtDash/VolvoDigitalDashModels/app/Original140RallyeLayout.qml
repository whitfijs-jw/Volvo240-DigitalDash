import QtQuick 2.15

Item {

    Accessory140RallyeStyle {
        id: coolantTempDelegate140RallyeStyle
        significatDigits: 1

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-coolant.png"
    }

    Accessory140RallyeStyle {
        id: fuelLevelDelegate140RallyeStyle
        significatDigits: 0

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-fuel.png"
    }

    Accessory140RallyeStyle {
        id: oilPressureDelegate140RallyeStyle
        gaugeMin: 0
        gaugeMax: 8
        significatDigits: 2

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-oil-pressure-bar.png"
    }

    Accessory140RallyeStyle {
        id: oilTempDelegate140RallyeStyle
        significatDigits: 1

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-oil-temp.png"
    }

    Accessory140RallyeStyle {
        id: voltmeterDelegate140RallyeStyle
        gaugeMin: 10
        gaugeMax: 18
        significatDigits: 2

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-voltmeter.png"
    }

    Accessory140RallyeStyle {
        id: boostDelegate140RallyeStyle
        minAngle: -240
        maxAngle: 60
        yOffset: 0
        needleLength: 0.55

        significatDigits: 1

        imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-boost_no_num.png"
    }

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height /1.2
        property real tachometerSize: speedometerSize

        property real largeGaugeNeedleWidth: 0.02
        property real largeGaugeNeedleLength: 0.5
        property real largeGaugeNeedleOffset: 0.075
        property real largeGaugeNeedleCenterRadius: 0.10

        property real smallGaugeSize: parent.height / 2.4

        property real smallGaugeNeedleLength: 0.65
        property real smallGaugeNeedleWidth: 0.04;
        property real smallGaugeNeedleOffset: 0.1
        property real smallGaugeMinAngle: -135
        property real smallGaugeMaxAngle: -45
        property real smallGaugeYOffset: 0.25
        property real smallGaugeNeedleCenterRadius: 0.15

        Rectangle {
            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.right: fuelLevelContainer.left
            anchors.rightMargin: -40
            anchors.verticalCenter: parent.verticalCenter

            TachometerDelegate {
                id: tachometerDelegate

                minAngle: -235
                maxAngle: -33

                initialValueOffset: 500

                imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-tach.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.left: coolantTempContainer.right
            anchors.leftMargin: -30
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: 10

                minAngle: -247
                maxAngle: 45

                imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-speedo.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }

        }

        Rectangle {
            id: coolantTempContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -container.smallGaugeSize * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: container.smallGaugeSize * 0.75

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            AccessoryGaugeDelegate {
                id: coolantTempDelegate
                minAngle: container.smallGaugeMinAngle
                maxAngle: container.smallGaugeMaxAngle

                needleOffset: container.smallGaugeNeedleOffset
                needleLength: container.smallGaugeNeedleLength
                needleWidth: container.smallGaugeNeedleWidth
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset

                imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-coolant.png"
                needleResource: "qrc:/needles/needle-rsport.png"
            }

            ListView {
                model: coolantTempModel
                delegate: coolantTempDelegate.component
            }
        }

        Rectangle {
            id: fuelLevelContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -container.smallGaugeSize * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -container.smallGaugeSize * 0.75

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            AccessoryGaugeDelegate {
                id: fuelLevelDelegate
                minAngle: container.smallGaugeMinAngle
                maxAngle: container.smallGaugeMaxAngle

                needleOffset: container.smallGaugeNeedleOffset
                needleLength: container.smallGaugeNeedleLength
                needleWidth: container.smallGaugeNeedleWidth
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset

                significatDigits: 0

                imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-fuel.png"
                needleResource: "qrc:/needles/needle-rsport.png"

            }

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate.component
            }
        }

        Rectangle {
            id: oilPContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: container.smallGaugeSize * 0.25
            anchors.horizontalCenter: parent.horizontalCenter
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            AccessoryGaugeDelegate {
                id: oilPressureDelegate

                gaugeMax: 8

                minAngle: container.smallGaugeMinAngle
                maxAngle: container.smallGaugeMaxAngle

                needleOffset: container.smallGaugeNeedleOffset
                needleLength: container.smallGaugeNeedleLength
                needleWidth: container.smallGaugeNeedleWidth
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset

                imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-oil-pressure-bar.png"
                needleResource: "qrc:/needles/needle-rsport.png"

            }
            ListView {
                model: oilPModel
                delegate: oilPressureDelegate.component
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -blinkerSize
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }
    }
}
