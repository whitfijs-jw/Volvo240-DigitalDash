import QtQuick 2.15

Item {

    Rectangle {
        width: 1920
        height: 720
        color: "transparent"

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
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
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
    }
}
