import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: boostGauge
    property int maxValue
    property int minValue
    property real value
    property string units
    property int highAlarm

    CircularGauge
    {
        id: gauge

        value: boostGauge.value

        anchors.fill: parent

        maximumValue: boostGauge.maxValue
        minimumValue: boostGauge.minValue


        Rectangle
        {
            id: indexTextBox
            width: parent.width
            height: parent.height/1.2

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            Text {
                property int textSize: gauge.height/8
                id: valueText

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -textSize

                fontSizeMode: Text.Fit
                font.pixelSize: textSize

                text: Number(boostGauge.value).toFixed(0).toLocaleString(Qt.locale("en_US")) + " " + units
                color: boostGauge.value > boostGauge.highAlarm ? "#ff7011" : "white"
            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 135
            minimumValueAngle: -135

            tickmark: null
            tickmarkLabel: null
            minorTickmark: null

            background: Image
            {
                source: "qrc:/gauge-faces-740-940/740_boost.png"
                anchors.fill: parent
                asynchronous: true
//                smooth: true
//                mipmap: true
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.5
                rotation: boundedAngle(valueToAngle(boostGauge.value), minimumValueAngle, maximumValueAngle) - 90
            }
            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.075
                implicitWidth: outerRadius * 0.9
                implicitHeight: outerRadius * 0.1
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
