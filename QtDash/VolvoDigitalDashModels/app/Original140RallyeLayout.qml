import QtQuick 2.15

Item {

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

        property bool speedoMph: speedoModel.units === "mph"
        property bool oilPressureBar: oilPModel.units === "bar"

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
                maxAngle: 33

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

                initialValueOffset: container.speedoMph ? 10 : 18

                minAngle: container.speedoMph ? -247 : -251
                maxAngle: container.speedoMph ? 45 : 46

                imageSource: container.speedoMph ?
                                 "qrc:/gauge-faces-140-rallye/140-rallye-speedo.png" :
                                 "qrc:/gauge-faces-140-rallye/140-rallye-speedo-kph.png"
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

                gaugeMax: container.oilPressureBar ? 8 : 120

                minAngle: container.smallGaugeMinAngle
                maxAngle: container.smallGaugeMaxAngle

                needleOffset: container.smallGaugeNeedleOffset
                needleLength: container.smallGaugeNeedleLength
                needleWidth: container.smallGaugeNeedleWidth
                needleCenterRadius: container.smallGaugeNeedleCenterRadius
                yOffset: container.smallGaugeYOffset

                significatDigits: 1

                imageSource: container.oilPressureBar ?
                                 "qrc:/gauge-faces-140-rallye/140-rallye-oil-pressure-bar.png" :
                                 "qrc:/gauge-faces-140-rallye/140-rallye-oil-pressure-psi.png"
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
