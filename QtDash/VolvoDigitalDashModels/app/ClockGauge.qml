import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    id: clockGauge
    property int maxValue
    property int minValue
    property real value
    property real divFactor: 1

    property string units: "F"
    property int lowAlarm: 0
    property int highAlarm: 0

    property real hours
    property real minutes

    property real textOffset:  parent.height / 1.5
    property real textSize: parent.height / 8
    property bool textEnabled: true
    property int significantDigits: 1

    property string imageResource: ""
    property string needleResource: ""
    property color needleColor: "orange"

    property int minuteWidth: parent.width * 0.03

    onValueChanged: {
        var temp = clockGauge.value / clockGauge.divFactor;
        clockGauge.hours = temp / 12.0;
        clockGauge.minutes = (hours - Math.floor(hours)) * 60.0;
    }

    Gauge {
        id: minuteHand
        anchors.fill: parent

        z: 1

        value: clockGauge.minutes

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        needleResource: clockGauge.needleResource

        needleColor: clockGauge.needleColor

        needleWidth: parent.width * 0.015
        needleLength: parent.width * 0.425
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: 0.10

        dir: RotationAnimation.Shortest
    }

    Gauge {
        id: hour
        anchors.fill: parent

        value: clockGauge.hours

        z: 0

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 12

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: clockGauge.imageResource

        needleColor: clockGauge.needleColor
        needleResource: clockGauge.needleResource

        needleWidth: parent.width * 0.020
        needleLength: parent.width * 0.275
        needleOffset: (parent.width * 0.05 / 2)

        needleCenterRadius: 0.10

        dir: RotationAnimation.Shortest
    }

    Text {

        id: valueText

        z: 1

        visible: textEnabled

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenterOffset: 0

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: clockGauge.textOffset

        fontSizeMode: Text.Fit
        font.pixelSize: clockGauge.textSize

        text: Number(clockGauge.value).toFixed(significantDigits).toLocaleString(Qt.locale("en_US")) + " " + units
        color: ( (clockGauge.value < clockGauge.lowAlarm)  || (clockGauge.value > clockGauge.highAlarm))
               ? "#ff7011" : "white"
    }
}
