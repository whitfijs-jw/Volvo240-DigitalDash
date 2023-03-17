import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    SideAccessoryGauge {
        id: upperGauge

        height: smallGaugeSize
        width: smallGaugeSize

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        initialGauge: "oil temp"
    }

    SideAccessoryGauge {
        id: lowerGauge

        height: smallGaugeSize
        width: smallGaugeSize

        anchors.top: upperGauge.bottom
        anchors.topMargin: parent.height / 25
        anchors.horizontalCenter: parent.horizontalCenter

        initialGauge: "oil pressure"
    }
}
