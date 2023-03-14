import QtQuick 2.15

Item {
    Rectangle {
        anchors.fill: parent
        color: "transparent"
    }

    Rectangle {
        id: boostContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        height: smallGaugeSize
        width: smallGaugeSize
        color: "transparent"

        ListView {
            model: boostModel
            delegate: BoostDelegate240Style
        }
    }
//    Rectangle {
//        id: oilPContainer
//        anchors.left: tachContainer.right
//        anchors.top: tachContainer.top

//        height: smallGaugeSize
//        width: smallGaugeSize
//        color: "transparent"

//        ListView {
//            model: oilPModel
//            delegate: oilPressureDelegate
//        }
//    }

//    Rectangle {
//        id: oilTContainer
//        anchors.left: oilPContainer.right
//        anchors.top: tachContainer.top

//        height: smallGaugeSize
//        width: smallGaugeSize
//        color: "transparent"

//        ListView {
//            model: oilTModel
//            delegate: oilTemperatureDelegate
//        }
//    }

    Rectangle {
        id: voltContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: boostContainer.bottom
        anchors.topMargin: 10

        height: smallGaugeSize
        width: smallGaugeSize
        color: "transparent"

        ListView {
            id: gaugeVolt
            model: voltMeterModel
            delegate: voltMeterDelegate
        }
    }
}
