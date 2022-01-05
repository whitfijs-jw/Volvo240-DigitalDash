import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: clock740
    property int maxValue
    property int minValue
    property real value

    property real hours
    property real minutes
    property real seconds

    property string dateString

    function timeChanged() {
        var date = new Date;
        hours = date.getHours() + date.getMinutes()/60;
        if(hours > 12) {
            hours -= 12.0;
        }

        minutes = date.getMinutes()
        seconds = date.getUTCSeconds();
        dateString = date.toTimeString();
    }

    Timer {
        interval: 500; running: true; repeat: true;
        onTriggered: clock740.timeChanged()
    }

    Image
    {
        z: -1
        source: "qrc:gauge-faces-740-940/740_clock.png"
        anchors.fill: parent
        asynchronous: true
    }

//    CircularGauge
//    {
//        id: secondHand
//        z: 1

//        value: clock740.seconds

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

    CircularGauge
    {
        id: minuteHand

        value: clock740.minutes

        anchors.fill: parent

        maximumValue: 60
        minimumValue: 0

        style: CircularGaugeStyle {
            maximumValueAngle: 360
            minimumValueAngle: 0

            tickmark: null
            tickmarkLabel: null
            minorTickmark: null

            background: Rectangle {
                anchors.fill: parent
                color: "transparent"

                Text {
                    property int textSize: clock740.height/8
                    id: valueText

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: outerRadius *  0.35

                    fontSizeMode: Text.Fit
                    font.pixelSize: outerRadius * 0.15

                    text: clock740.dateString
                    color: "white"
                }
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: valueToAngle(minuteHand.value) - 90
            }

            needle: Rectangle {
                y: - outerRadius * 0.35
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 1.0
                implicitHeight: outerRadius * 0.05
                antialiasing: true
                rotation: 90
                gradient: Gradient {
                        GradientStop { position: 0.25; color: "red"}
                        GradientStop { position: 0.5; color: "orange" }
                        GradientStop { position: 0.75; color: "red" }
                }
            }

        }

    }

    CircularGauge
    {
        id: hourHand

        value: clock740.hours

        anchors.fill: parent

        maximumValue: 12
        minimumValue: 0

        style: CircularGaugeStyle {
            maximumValueAngle: 360
            minimumValueAngle: 0

            tickmark: null
            tickmarkLabel: null
            //tickmarkStepSize: 1
            minorTickmark: null

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: valueToAngle(hourHand.value) - 90
            }

            needle: Rectangle {
                y: - outerRadius * 0.35
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 0.5
                implicitHeight: outerRadius * 0.05
                antialiasing: true
                rotation: 90
                gradient: Gradient {
                        GradientStop { position: 0.25; color: "red"}
                        GradientStop { position: 0.5; color: "orange" }
                        GradientStop { position: 0.75; color: "red" }
                }
            }

        }

    }
}
