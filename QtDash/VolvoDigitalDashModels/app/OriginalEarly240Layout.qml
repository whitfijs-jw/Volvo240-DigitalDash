import QtQuick 2.15

Item {
    BlinkerDelegateEarly240Style {
        id: leftBlinkerDelegateEarly240Style
        flipped: false
    }

    BlinkerDelegateEarly240Style {
        id: rightBlinkerDelegateEarly240Style
        flipped: true
    }

    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height / 1.2
        property real tachometerSize: parent.height * 0.625
        property real tachometerOverlaySize: tachometerSize / 0.9375
        property real tempFuelSize: speedometerSize

        property real blinkerSize: parent.height / 9.6
        property real topMargin: parent.height / 48.0

        property real warningLightWidthWide: parent.height / 4.8
        property real warningLightHeight: parent.height / 9.6
        property real warningLightSizeNarrow: warningLightHeight
        property int warningLightVerticalMargin: parent.height / 96
        property int warningLightHorizontalMargin: parent.height / 60

        property real largeGaugeNeedleWidth: 0.02
        property real largeGaugeNeedleLength: 0.45
        property real largeGaugeNeedleOffset: 0.075
        property real largeGaugeNeedleCenterRadius: 0.1

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: 8

                minAngle: -246
                maxAngle: 45

                imageSource: "qrc:/gauges-early-240/early-240-speedo-with-border.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius
            }

            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.right: tachContainer.left
            anchors.rightMargin: parent.width * 0.035
            anchors.bottom: tachContainer.bottom
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }

        }

        Image {
            id: tachOverlay
            antialiasing: true
            smooth: true
            source: "qrc:/gauges-early-240/early-240-tach-border.png"

            anchors.horizontalCenter: tachContainer.horizontalCenter
            anchors.bottom: tachContainer.bottom
            width: container.tachometerOverlaySize
            height: container.tachometerOverlaySize
        }

        Rectangle {
            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: container.tachometerSize * 0.025

            TachometerDelegate {
                id: tachometerDelegate

                minAngle: -228
                maxAngle: 38

                initialValueOffset: 400

                imageSource: "qrc:/gauges-early-240/early-240-tach.png"
                needleResource: "qrc:/needles/needle-rsport.png"

                needleWidth: container.largeGaugeNeedleWidth
                needleLength: container.largeGaugeNeedleLength
                needleOffset: container.largeGaugeNeedleOffset
                needleCenterRadius: container.largeGaugeNeedleCenterRadius

                textSize: .075
                textOffset: .125
            }

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            id: tempFuelContainer
            width: container.tempFuelSize
            height: container.tempFuelSize
            anchors.left: tachContainer.right
            anchors.leftMargin: parent.width * 0.035
            anchors.verticalCenter: speedoContainer.verticalCenter
            color: "transparent"

            TempAndFuelDelegateEarly240Style {
                id: tempFuelDelegate
            }

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate.component
            }

        }

        Rectangle {
            id: leftBlinker
            width: container.blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: container.topMargin
            anchors.right: parkingBrakeLight.left
            anchors.rightMargin: container.warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegateEarly240Style.component
            }
        }

        Rectangle {
            id: parkingBrakeLight
            width: container.warningLightWidthWide
            height: container.warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: container.topMargin
            anchors.right : highBeamLight.left
            anchors.rightMargin: container.warningLightHorizontalMargin
            color: "transparent"

            WarningLightDelegate {
                id: parkingBrakeLightDelegate
                color: "red"
            }

            ListView {
                model: parkingBrakeLightModel
                delegate: parkingBrakeLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: highBeamLight
            width: container.warningLightSizeNarrow
            height: container.warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: container.topMargin
            anchors.horizontalCenter: tachContainer.horizontalCenter
            color: "transparent"

            WarningLightDelegate {
                id: highBeamLightDelegate
                color: "lightcyan"
                imageResource: "qrc:/warningLights/high_beam_icon.png"
            }

            ListView {
                model: highBeamLightModel
                delegate: highBeamLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: brakeFailureLight
            width: container.warningLightWidthWide
            height: container.warningLightHeight
            anchors.top: speedoContainer.top
            anchors.topMargin: container.topMargin
            anchors.left : highBeamLight.right
            anchors.leftMargin: container.warningLightHorizontalMargin
            color: "transparent"

            WarningLightDelegate {
                id: brakeFailureLightDelegate
                color: "red"
            }

            ListView {
                model: brakeFailureLightModel
                delegate: brakeFailureLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: rightBlinker
            width: container.blinkerSize
            anchors.top: speedoContainer.top
            anchors.topMargin: container.topMargin
            anchors.left : brakeFailureLight.right
            anchors.leftMargin: container.warningLightHorizontalMargin
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegateEarly240Style.component
            }
        }

        Rectangle {
            id: oilWarningLight
            width: container.warningLightSizeNarrow
            height: container.warningLightHeight
            anchors.horizontalCenter: tempFuelContainer.horizontalCenter
            anchors.horizontalCenterOffset: -(oilWarningLight.width + container.warningLightHorizontalMargin) / 2
            anchors.top: tempFuelContainer.top
            anchors.topMargin: container.topMargin
            color: "transparent"

            WarningLightDelegate {
                id: oilPressureLightDelegate
                text: "OIL"
                overrideText: true
                color: "red"
            }

            ListView {
                model: oilWarningLightModel
                delegate: oilPressureLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: batteryWarningLight
            width: container.warningLightSizeNarrow
            height: container.warningLightHeight
            anchors.horizontalCenter: tempFuelContainer.horizontalCenter
            anchors.horizontalCenterOffset: (batteryWarningLight.width + container.warningLightHorizontalMargin) / 2
            anchors.top: tempFuelContainer.top
            anchors.topMargin: container.topMargin
            color: "transparent"

            WarningLightDelegate {
                id: batteryLightDelegate
                text: "AMP"
                overrideText: true
                color: "red"
            }

            ListView {
                model: batteryWarningLightModel
                delegate: batteryLightDelegate.component
                anchors.fill: parent
            }
        }


    }
}
