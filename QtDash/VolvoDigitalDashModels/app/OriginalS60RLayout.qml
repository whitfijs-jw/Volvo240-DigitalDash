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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -speedoSize / 1.75
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -speedoSize / 10
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegateS60R
            }
        }


        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: tachSize / 1.75
            anchors.verticalCenter: speedoContainer.verticalCenter

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegateS60R
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
