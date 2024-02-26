import QtQuick 2.15

Item {

    Rectangle {
        width: 1280
        height: 480
        color: "transparent"

        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.right: fuelLevelContainer.left
            anchors.rightMargin: -40
            anchors.verticalCenter: parent.verticalCenter
            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachoDelegate140RallyeStyle
            }

        }

        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.left: coolantTempContainer.right
            anchors.leftMargin: -30
            anchors.verticalCenter: parent.verticalCenter
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate140RallyeStyle
            }

        }

        Rectangle {
            id: coolantTempContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -smallGaugeSize * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: smallGaugeSize * 0.75

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: coolantTempModel
                delegate: coolantTempDelegate140RallyeStyle.component
            }
        }

        Rectangle {
            id: fuelLevelContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -smallGaugeSize * 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -smallGaugeSize * 0.75

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: fuelLevelModel
                delegate: fuelLevelDelegate140RallyeStyle.component
            }
        }

        Rectangle {
            id: oilPContainer
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: smallGaugeSize * 0.25
            anchors.horizontalCenter: parent.horizontalCenter
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate140RallyeStyle.component
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
