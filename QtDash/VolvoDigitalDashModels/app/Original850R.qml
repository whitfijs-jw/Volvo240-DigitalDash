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
            anchors.verticalCenter: parent.verticalCenter
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate740
            }
        }


        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.left: speedoContainer.right
            anchors.leftMargin: tachSize / 8
            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: tachSize * 0.10

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegate740
            }

        }

        Rectangle {
            width: tachSize
            height: tachSize
            anchors.right: speedoContainer.left
            anchors.rightMargin: tachSize / 8
            anchors.verticalCenter: tachContainer.verticalCenter
            anchors.verticalCenterOffset: -smallGaugeSize * 0.1
            color: "transparent"

            Rectangle {
                id: boostContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -smallGaugeSize * 0.4
                height: smallGaugeSize
                width: smallGaugeSize
                color: "transparent"

                ListView {
                    model: boostModel
                    delegate: boostDelegate850
                }
            }

            Rectangle {
                id: coolantTempContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: smallGaugeSize * 0.325
                height: smallGaugeSize
                width: smallGaugeSize
                color: "transparent"

                ListView {
                    model: coolantTempModel
                    delegate: coolantDelegate850
                }
            }

            Rectangle {
                id: fuelLevelContainer
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: -smallGaugeSize * 0.325
                height: smallGaugeSize
                width: smallGaugeSize
                color: "transparent"

                ListView {
                    model: fuelLevelModel
                    delegate: fuelLevelDelegate850
                }
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
