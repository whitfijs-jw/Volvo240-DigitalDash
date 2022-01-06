import QtQuick 2.15
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: ambientTemp
    property int maxValue
    property int minValue
    property real value
    property string units

    CircularGauge
    {
        id: gauge

        value: ambientTemp.value

        anchors.fill: parent

        maximumValue: ambientTemp.maxValue
        minimumValue: ambientTemp.minValue


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
                anchors.bottomMargin: -textSize*1.5

                fontSizeMode: Text.Fit
                font.pixelSize: textSize

                text: Number(ambientTemp.value).toFixed(0).toLocaleString(Qt.locale("en_US")) + " " + units
                color: "white"
            }


        }

        style: CircularGaugeStyle {
            maximumValueAngle: 146.5
            minimumValueAngle: -95

            tickmark: null
            tickmarkLabel: null
            //tickmarkStepSize: 5
            minorTickmark: null

            background: Image
            {
                source: "qrc:accCluster/ambient_temp_black_f.png"
                anchors.fill: parent
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: boundedAngle(valueToAngle(ambientTemp.value), minimumValueAngle, maximumValueAngle) - 90
            }
            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 1.1
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
