import QtQuick 2.15

Item {

    Rectangle {
        id: boostContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        height: smallGaugeSize
        width: smallGaugeSize
        color: "transparent"

        ListView {
            model: boostModel
            delegate: boostDelegate
        }
    }

    Rectangle {
        id: voltContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: boostContainer.bottom
        anchors.topMargin: 5

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
