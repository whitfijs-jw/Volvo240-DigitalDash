import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {

    Rectangle {
        width: 1280
        height: 480
        color: "black"

        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.right: speedoContainer.left
            anchors.verticalCenter: speedoContainer.verticalCenter
            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegate
            }

        }

        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate
            }

        }

        Rectangle {
            id: tempFuelContainer
            width: tempFuelSize
            height: tempFuelSize
            anchors.left: speedoContainer.right
            anchors.verticalCenter: speedoContainer.verticalCenter
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate
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

        Rectangle {
            id: parkingBrakeWarningLight
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 200
            height: warningLightWidth
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
            height: warningLightWidth
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
    }
}
