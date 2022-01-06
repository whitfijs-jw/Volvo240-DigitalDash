import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    id: clockLarge
    property int maxValue
    property int minValue
    property real value

    property real hours
    property real minutes
    property real seconds

    property string dateString

    property bool enableSeconds: true

    property string imageSource: ""

    function timeChanged() {
        var date = new Date;
        hours = date.getHours() + date.getMinutes()/60;
        if(hours > 12) {
            hours -= 12.0;
        }

        minutes = date.getMinutes()
        seconds = date.getUTCSeconds();
        dateString = date.toTimeString();
        valueText.text = date.toTimeString();
    }

    Timer {
        interval: 500; running: true; repeat: true;
        onTriggered: clockLarge.timeChanged()
    }


    Gauge {
        id: minuteHand
        anchors.fill: parent

        value: clockLarge.minutes

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: imageSource

        needleColor: "red"

        needleWidth: parent.width * 0.03
        needleLength: parent.width * 0.525
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: 0.15

    }

    Gauge {
        id: secondHand
        anchors.fill: parent
        visible: enableSeconds

        value: clockLarge.seconds

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: ""

        needleColor: "red"

        needleWidth: parent.width * 0.015
        needleLength: parent.width * 0.525
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: 0.15

    }

    Gauge {
        id: hour
        anchors.fill: parent

        value: clockLarge.hours

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 12

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: ""

        needleColor: "red"

        needleWidth: parent.width * 0.035
        needleLength: parent.width * 0.425
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: 0.15

    }

    Text {
        property int textSize: clockLarge.height * 0.075
        id: valueText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height / 6.0

        fontSizeMode: Text.Fit
        font.pixelSize: textSize

        text: "--:--:--"
        color: "white"
    }
}
