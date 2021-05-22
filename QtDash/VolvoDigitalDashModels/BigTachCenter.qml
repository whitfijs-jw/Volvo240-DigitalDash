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
            anchors.horizontalCenter: parent.horizontalCenter

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
            anchors.right: tachContainer.left
            anchors.top: boostContainer.bottom
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
            anchors.left: tachContainer.right
            anchors.top: oilPContainer.bottom
            anchors.topMargin: 10
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate
            }

        }


        Rectangle {
            id: boostContainer
            anchors.right: tachContainer.left
            anchors.leftMargin: -50
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: boostModel
                delegate: boostDelegate
            }
        }
        Rectangle {
            id: oilPContainer
            anchors.left: tachContainer.right
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate
            }
        }

        Rectangle {
            id: oilTContainer
            anchors.left: oilPContainer.right
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: oilTModel
                delegate: oilTemperatureDelegate
            }
        }

        Rectangle {
            id: voltContainer
            anchors.right: boostContainer.left
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                id: gaugeVolt
                model: voltMeterModel
                delegate: voltMeterDelegate
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: tachContainer.top
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
            anchors.top: tachContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width / 6.75
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }
    }
}
