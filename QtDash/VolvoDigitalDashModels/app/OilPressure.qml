import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: oilPressure
    property int maxValue
    property int minValue
    property real value
    property string units
    property int lowAlarm
    property int highAlarm

    Image
    {
        source: "qrc:accCluster/oil_pressure_black.png"
        anchors.fill: parent
        z: -1
        asynchronous: true
    }

    CircularGauge
    {
        id: gauge

        value: oilPressure.value

        width: parent.width
        height: parent.height

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/4.5

        anchors.horizontalCenter: parent.horizontalCenter

        maximumValue: oilPressure.maxValue
        minimumValue: oilPressure.minValue



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

                text: Number(oilPressure.value).toFixed(1).toLocaleString(Qt.locale("en_US")) + " " + units
                color: ( (oilPressure.value > oilPressure.highAlarm) || (oilPressure.value < oilPressure.lowAlarm) )
                       ? "#ff7011" : "white"

            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 46.5
            minimumValueAngle: -45.5

            tickmark: null
            tickmarkLabel: null
            //tickmarkStepSize: 0.5
            minorTickmark: null

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: boundedAngle(valueToAngle(oilPressure.value), minimumValueAngle, maximumValueAngle) - 90
            }

            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 1.325
                implicitHeight: outerRadius * 0.05
                antialiasing: true
                rotation: 90
                gradient: Gradient {
                        GradientStop { position: 0.25; color: "orange"}
                        GradientStop { position: 0.5; color: "white" }
                        GradientStop { position: 0.75; color: "orange" }
                }
            }

        }


    }
}
