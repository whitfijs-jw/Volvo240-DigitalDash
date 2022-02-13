import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    id: clock
    property int maxValue
    property int minValue
    property real value

    property real hours
    property real minutes
    property real seconds

    function timeChanged() {
        var date = new Date;
        valueText.text = date.toLocaleTimeString();
        var hrLocal = parseInt(date.toTimeString().substring(0,2), 10);
        hours = hrLocal + date.getMinutes()/60;
        if(hours > 12) {
            hours -= 12.0;
        }

        minutes = date.getMinutes()
        seconds = date.getUTCSeconds();
    }

    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered: clock.timeChanged()
    }

    Behavior on seconds {
        RotationAnimation {
            duration: 250
            direction: RotationAnimation.Shortest
        }
    }

    Gauge {
        id: secondHand
        anchors.fill: parent

        value: clock.seconds

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: "qrc:/accCluster/clock_black.png"

        needleColor: "orange"

        needleWidth: parent.width * 0.015
        needleLength: parent.width * 0.525
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: 0.15

    }

    Gauge {
        id: minuteHand
        anchors.fill: parent

        value: clock.minutes

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: ""

        needleColor: "orange"

        needleWidth: smallGaugeSize * 0.03
        needleLength: smallGaugeSize * 0.525
        needleOffset: smallGaugeSize * .15 / 2

        needleCenterRadius: 0.15

    }

    Gauge {
        id: hour
        anchors.fill: parent

        value: clock.hours

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 12

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: ""

        needleColor: "orange"

        needleWidth: smallGaugeSize * 0.035
        needleLength: smallGaugeSize * 0.425
        needleOffset: smallGaugeSize * .15 / 2

        needleCenterRadius: 0.15

    }

    Text {
        property int textSize: clock.height/8
        id: valueText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -textSize

        fontSizeMode: Text.Fit
        font.pixelSize: textSize

        text: "--:--:--"
        color: "white"
    }
}
