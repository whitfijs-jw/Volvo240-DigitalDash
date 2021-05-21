import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Item {
    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8

    Rectangle {
        width: 1280
        height: 480
        color: "transparent"

        Rectangle {
            id: parkingBrakeWarningLight
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 180
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

        Rectangle {
            id: highBeamLight
            anchors.right: parkingBrakeWarningLight.left
            anchors.top: parkingBrakeWarningLight.top
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
    }
}
