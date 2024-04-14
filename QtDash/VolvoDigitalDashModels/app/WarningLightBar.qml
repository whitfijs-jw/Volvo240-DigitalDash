import QtQuick 2.15

Item {
    property int warningLightHeight: parent.height * (50/480)
    property int warningLightWidth: parent.height * (70/480)
    property int warningLightWideWidth: parent.height * (100/480)
    property int warningLightVerticalMargin: parent.height * (5/480);
    property int warningLightHorizontalMargin: parent.height * (8/480)
    property int deadSpaceMiddle: parent.height * (100/480);
    property bool showLights: true

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: checkEngineLight.top
            color: "transparent"
            width: deadSpaceMiddle
            height: warningLightHeight
            visible: true

            OdometerDelegate {
                id: odometerDelegate
            }

            ListView {
                model: odometerModel
                delegate: odometerDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: serviceLight
            anchors.right: checkEngineLight.left
            anchors.top: checkEngineLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: serviceLightDelegate
                color: "orange"
            }

            ListView {
                model: serviceLightModel
                delegate: serviceLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: checkEngineLight
            anchors.right: absWarningLight.left
            anchors.top: absWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: checkEngineLightDelegate
                color: "red"
            }

            ListView {
                model: checkEngineLightModel
                delegate: checkEngineLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: absWarningLight
            anchors.right: batteryWarningLight.left
            anchors.top: batteryWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: absWarningLightDelegate
                color: "red"
            }

            ListView {
                model: absWarningLightModel
                delegate: absWarningLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: batteryWarningLight
            anchors.right: oilWarningLight.left
            anchors.top: oilWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: batteryWarningLightDelegate
                color: "red"
                imageResource: "qrc:warningLights/battery_charge_icon_no_background.png"
            }

            ListView {
                model: batteryWarningLightModel
                delegate: batteryWarningLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: oilWarningLight
            anchors.right: srsWarningLight.left
            anchors.top: srsWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: oilWarningLightDelegate
                color: "red"
                imageResource: "qrc:warningLights/oil_icon_no_background.png"
            }

            ListView {
                model: oilWarningLightModel
                delegate: oilWarningLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: srsWarningLight
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -deadSpaceMiddle
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: srsWarningLightDelegate
                color: "red"
            }

            ListView {
                model: srsWarningLightModel
                delegate: srsWarningLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: highBeamLight
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: deadSpaceMiddle
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.rightMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

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
            id: parkingBrakeWarningLight
            anchors.left: highBeamLight.right
            anchors.top: highBeamLight.top
            height: warningLightHeight
            width: warningLightWideWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

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
            id: brakeFailureWarningLight
            anchors.left: parkingBrakeWarningLight.right
            anchors.top: parkingBrakeWarningLight.top
            height: warningLightHeight
            width: warningLightWideWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

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
            id: bulbFailureWarningLight
            anchors.left: brakeFailureWarningLight.right
            anchors.top: brakeFailureWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: bulbFailureLightDelegate
                color: "orange"
                imageResource: "qrc:/warningLights/Bulb_failure_icon_no_background.png"
            }

            ListView {
                model: bulbFailureLightModel
                delegate: bulbFailureLightDelegate.component
                anchors.fill: parent
            }
        }

        Rectangle {
            id: shiftUpLight
            anchors.left: bulbFailureWarningLight.right
            anchors.top: bulbFailureWarningLight.top
            height: warningLightHeight
            width: warningLightWidth
            anchors.bottomMargin: warningLightVerticalMargin
            anchors.leftMargin: warningLightHorizontalMargin
            color: "transparent"
            visible: showLights

            WarningLightDelegate {
                id: shiftUpLightDelegate
                color: "orange"
            }

            ListView {
                model: shiftUpLightModel
                delegate: shiftUpLightDelegate.component
                anchors.fill: parent
            }
        }
    }
}
