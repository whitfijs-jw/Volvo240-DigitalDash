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
    property string needleResource: ""

    property string generation: "740"

    property int minuteWidth: parent.width * 0.03

    function timeChanged() {
        var date = new Date;
        var hrLocal = parseInt(date.toTimeString().substring(0,2), 10);
        hours = hrLocal + date.getMinutes()/60;

        if(hours > 12) {
            hours -= 12.0;
        }

        minutes = date.getMinutes()
        seconds = date.getUTCSeconds();
        dateString = date.toTimeString();
        valueText.text = date.toTimeString();
    }

    Timer {
        interval: 250; running: true; repeat: true;
        onTriggered: clockLarge.timeChanged()
    }

    Behavior on seconds {
        RotationAnimation {
            duration: 250
            direction: RotationAnimation.Shortest
        }
    }

    Gauge {
        id: minuteHand
        anchors.fill: parent

        z: generation === "740" ? 0 : 2

        value: clockLarge.minutes

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: generation === "740" ? imageSource : ""
        needleResource: clockLarge.needleResource

        needleColor: generation === "740" ? "red" : "orange"

        needleWidth: generation === "740" ? parent.width * 0.03 : parent.width * 0.015
        needleLength: generation === "740" ? parent.width * 0.525 : parent.width * 0.425
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: generation === "740" ? 0.15: 0.10

        dir: RotationAnimation.Shortest
    }

    Gauge {
        id: secondHand
        anchors.fill: parent
        visible: enableSeconds

        z: generation === "740" ? 0 : 0

        value: clockLarge.seconds

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 60

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: generation === "740" ? "" : imageSource
        needleResource: clockLarge.needleResource

        needleColor: generation === "740" ? "red" : "orange"

        needleWidth: generation === "740" ? parent.width * 0.015 : parent.width * 0.010
        needleLength: generation === "740" ? parent.width * 0.525 : parent.width * 0.425
        needleOffset: parent.width * .15 / 2

        needleCenterRadius: generation === "740" ? 0.15: 0.10

        dir: RotationAnimation.Shortest
    }

    Gauge {
        id: hour
        anchors.fill: parent

        value: clockLarge.hours

        z: generation === "740" ? 0 : 1

        lowAlarm: -1
        highAlarm: 61

        minValue: 0
        maxValue: 12

        minAngle: -90
        maxAngle: 270

        units: ""
        textEnabled: false

        imageResource: ""

        needleColor: generation === "740" ? "red" : "orange"
        needleResource: clockLarge.needleResource

        needleWidth: generation === "740" ? parent.width * 0.035 : parent.width * 0.020
        needleLength: generation === "740" ? parent.width * 0.425 : parent.width * 0.275
        needleOffset: generation === "740" ? (parent.width * .15 / 2) : (parent.width * 0.05 / 2)

        needleCenterRadius: generation === "740" ? 0.15: 0.10

        dir: RotationAnimation.Shortest
    }

    Text {
        property int textSize: clockLarge.height * 0.075
        id: valueText

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: generation === "740" ? (parent.height / 6.0) : (parent.height / 8.0)

        fontSizeMode: Text.Fit
        font.pixelSize: textSize

        text: "--:--:--"
        color: "white"
    }
}
