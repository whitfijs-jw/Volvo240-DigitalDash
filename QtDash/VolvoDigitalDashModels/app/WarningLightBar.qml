import QtQuick 2.15

Item {
    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8
    property int deadSpaceMiddle: 100;

    Rectangle {
        width: 1920
        height: 720
        color: "transparent"

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: checkEngineLight.top
            color: "transparent"
            width: deadSpaceMiddle
            height: warningLightWidth


            ListView {
                model: odometerModel
                delegate: odometerDelegate
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

            ListView {
                model: serviceLightModel
                delegate: serviceLightDelegate
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

            ListView {
                model: checkEngineLightModel
                delegate: checkEngineLightDelegate
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

            ListView {
                model: absWarningLightModel
                delegate: absWarningLightDelegate
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

            ListView {
                model: batteryWarningLightModel
                delegate: batteryWarningLightDelegate
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

            ListView {
                model: oilWarningLightModel
                delegate: oilWarningLightDelegate
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

            ListView {
                model: srsWarningLightModel
                delegate: srsWarningLightDelegate
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

            ListView {
                model: highBeamLightModel
                delegate: highBeamLightDelegate
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

            ListView {
                model: parkingBrakeLightModel
                delegate: parkingBrakeLightDelegate
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

            ListView {
                model: brakeFailureLightModel
                delegate: brakeFailureLightDelegate
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

            ListView {
                model: bulbFailureLightModel
                delegate: bulbFailureLightDelegate
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

            ListView {
                model: shiftUpLightModel
                delegate: shiftUpLightDelegate
                anchors.fill: parent
            }
        }
    }
}
