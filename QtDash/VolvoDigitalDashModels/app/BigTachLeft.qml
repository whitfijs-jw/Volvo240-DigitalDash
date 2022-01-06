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
            anchors.left: speedoContainer.right
            anchors.leftMargin: 50
            anchors.top: boostContainer.bottom
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
            anchors.left: tachContainer.right
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
            anchors.left: oilTContainer.right
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
            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            Clock {
                anchors.fill: parent
            }
        }

//        Rectangle {
//            id: ambientTempContainer
//            anchors.left: clockContainer.right
//            height: smallGaugeSize
//            width: smallGaugeSize
//            color: "transparent"

//            ListView {
//                id: ambientTemp
//                model: outsideTempModel
//                delegate: ambientTempDelegate
//            }
//        }
    }
}
