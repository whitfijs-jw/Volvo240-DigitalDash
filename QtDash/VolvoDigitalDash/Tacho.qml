import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: tacho
    property int maxValue
    property int minValue
    property real value

    CircularGauge
    {
        id: gauge

        value: (tacho.value / 1000) > 0.25 ? (tacho.value / 1000) : 0.25

        anchors.fill: parent

        maximumValue: tacho.maxValue / 1000
        minimumValue: tacho.minValue / 1000

        style: CircularGaugeStyle {
            maximumValueAngle: 122
            minimumValueAngle: -130

            tickmark: null
            tickmarkLabel: null
            minorTickmark: null

            background: Rectangle {
                anchors.fill: parent
                color: "transparent"

                Text {
                    z:1
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: outerRadius *  0.35

                    fontSizeMode: Text.Fit
                    font.pixelSize: outerRadius * 0.15

                    text: Number(tacho.value).toFixed(0).toLocaleString(Qt.locale("en_US")) + " rpm"
                    color: "white"
                }

                Image{
                    z:0
                    source: "qrc:mainCluster/tacho.png"
                    anchors.fill: parent
                }
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.2
                rotation: valueToAngle(tacho.value / 1000) - 90
            }

            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 0.9
                implicitHeight: outerRadius * 0.03
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
