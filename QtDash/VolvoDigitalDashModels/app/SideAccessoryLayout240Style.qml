import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    SideAccessoryGauge240Style {
        id: upperGauge

        height: smallGaugeSize
        width: smallGaugeSize

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top


        initalModel: boostModel
        initialDelegate: boostDelegate240
    }

    SideAccessoryGauge240Style {
        id: lowerGauge

        height: smallGaugeSize
        width: smallGaugeSize

        anchors.top: upperGauge.bottom
        anchors.topMargin: parent.height / 25
        anchors.horizontalCenter: parent.horizontalCenter

        initalModel: voltMeterModel
        initialDelegate: voltMeterDelegate240
    }
}
