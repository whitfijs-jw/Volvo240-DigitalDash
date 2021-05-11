import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: ambientTemp
    property int maxValue
    property int minValue
    property real value

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
                property int textSize: 20
                id: valueText

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 45

                fontSizeMode: Text.Fit
                font.pixelSize: textSize

                text: Number(ambientTemp.value).toFixed(0).toLocaleString(Qt.locale("en_US")) + " °F"
                color: "white"
            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 160
            minimumValueAngle: -70

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
                rotation: valueToAngle(ambientTemp.value) - 90
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
