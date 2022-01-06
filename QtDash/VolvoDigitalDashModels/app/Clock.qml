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
        hours = date.getHours() + date.getMinutes()/60;
        if(hours > 12) {
            hours -= 12.0;
        }

        minutes = date.getMinutes()
        seconds = date.getUTCSeconds();
        valueText.text = date.toTimeString();
    }

    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered: clock.timeChanged()
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

//    CircularGauge
//    {
//        id: secondHand
//        z: 1

//        value: clock.seconds

//        anchors.fill: parent

//        maximumValue: 60
//        minimumValue: 0

//        style: CircularGaugeStyle {
//            maximumValueAngle: 360
//            minimumValueAngle: 0

//            tickmark: null
//            tickmarkLabel: null
//            minorTickmark: null

//            foreground: NeedleCenter {
//                size: outerRadius * 0.3
//                rotation: valueToAngle(secondHand.value) - 90
//            }

//            needle: Rectangle {
//                y: - outerRadius * 0.35
//                radius: outerRadius * 0.025
//                implicitWidth: outerRadius * 1.0
//                implicitHeight: outerRadius * 0.03
//                antialiasing: true
//                rotation: 90
//                gradient: Gradient {
//                        GradientStop { position: 0.25; color: "orange"}
//                        GradientStop { position: 0.5; color: "white" }
//                        GradientStop { position: 0.75; color: "orange" }
//                }
//            }



//        }

//    }

//    CircularGauge
//    {
//        id: minuteHand

//        value: clock.minutes

//        anchors.fill: parent

//        maximumValue: 60
//        minimumValue: 0

//        style: CircularGaugeStyle {
//            maximumValueAngle: 360
//            minimumValueAngle: 0

//            tickmark: null
//            tickmarkLabel: null
//            minorTickmark: null

//            foreground: NeedleCenter {
//                size: outerRadius * 0.3
//            }

//            needle: Rectangle {
//                y: - outerRadius * 0.35
//                radius: outerRadius * 0.025
//                implicitWidth: outerRadius * 1.0
//                implicitHeight: outerRadius * 0.05
//                antialiasing: true
//                rotation: 90
//                gradient: Gradient {
//                        GradientStop { position: 0.25; color: "orange"}
//                        GradientStop { position: 0.5; color: "white" }
//                        GradientStop { position: 0.75; color: "orange" }
//                }
//            }

//        }

//    }

//    CircularGauge
//    {
//        id: hourHand

//        value: clock.hours

//        anchors.fill: parent

//        maximumValue: 12
//        minimumValue: 0

//        style: CircularGaugeStyle {
//            maximumValueAngle: 360
//            minimumValueAngle: 0

//            tickmark: null
//            tickmarkLabel: null
//            //tickmarkStepSize: 1
//            minorTickmark: null

//            foreground: NeedleCenter {
//                size: outerRadius * 0.3
//            }

//            needle: Rectangle {
//                y: - outerRadius * 0.35
//                radius: outerRadius * 0.025
//                implicitWidth: outerRadius * 0.65
//                implicitHeight: outerRadius * 0.05
//                antialiasing: true
//                rotation: 90
//                gradient: Gradient {
//                        GradientStop { position: 0.25; color: "orange"}
//                        GradientStop { position: 0.5; color: "white" }
//                        GradientStop { position: 0.75; color: "orange" }
//                }
//            }

//        }

//    }
}
