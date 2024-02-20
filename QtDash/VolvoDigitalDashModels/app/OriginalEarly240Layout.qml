import QtQuick 2.15

Item {

    Rectangle {
        width: 1280
        height: 480
        color: "transparent"

        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.right: tachContainer.left
            anchors.rightMargin: parent.width * 0.035
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegateEarly240
            }

        }

        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: tachSize * 0.1

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachoDelegateEarly240Style
            }

        }

        Rectangle {
            id: tempFuelContainer
            width: tempFuelSize
            height: tempFuelSize
            anchors.left: tachContainer.right
            anchors.leftMargin: parent.width * 0.035
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegateEarly240
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
    }
}
