import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: coolantGauge
    property int maxValue
    property int minValue
    property real value
    property string units
    property int highAlarm

    Image
    {
        source: "qrc:/gauge-faces-740-940/740_coolant_temp.png"
        anchors.fill: parent
        asynchronous: true
        z: -1
        smooth: true
        mipmap: true
    }

    CircularGauge
    {
        id: gauge

        value: coolantGauge.value

        maximumValue: coolantGauge.maxValue
        minimumValue: coolantGauge.minValue

        width: parent.width
        height: parent.height

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/4.5

        anchors.horizontalCenter: parent.horizontalCenter

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
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 45

                fontSizeMode: Text.Fit
                font.pixelSize: textSize

                text: Number(coolantGauge.value).toFixed(0).toLocaleString(Qt.locale("en_US")) + " " + units
                color: coolantGauge.value > coolantGauge.highAlarm ? "#ff7011" : "white"
            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 26
            minimumValueAngle: -24

            tickmark: null
            tickmarkLabel: null
            minorTickmark: null

            foreground: NeedleCenter {
                size: outerRadius * 0.5
                rotation: boundedAngle(valueToAngle(coolantGauge.value), minimumValueAngle, maximumValueAngle) - 90
            }
            needle: Rectangle {
                y: - outerRadius * 0.5
                radius: outerRadius * 0.05
                implicitWidth: outerRadius * 1.25
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
