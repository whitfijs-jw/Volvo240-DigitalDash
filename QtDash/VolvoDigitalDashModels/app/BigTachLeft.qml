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
            anchors.right: speedoContainer.left
            anchors.bottom: speedoContainer.bottom

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
            anchors.verticalCenterOffset: 70
            anchors.topMargin: 0
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
            anchors.verticalCenterOffset: -20
            anchors.leftMargin: 50
//            anchors.top: boostContainer.bottom
//            anchors.topMargin: 10
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate
            }

        }


        Rectangle {
            id: boostContainer
            anchors.left: tachContainer.right
            anchors.bottom: speedoContainer.top
            anchors.bottomMargin: 10
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
            anchors.left: boostContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
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
            anchors.verticalCenter: boostContainer.verticalCenter
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
            anchors.left: oilTContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
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
            id: clockContainer
            anchors.left: voltContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            Clock {
                anchors.fill: parent
            }
        }
    }
}
