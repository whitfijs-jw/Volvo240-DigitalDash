import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: tacho
    property int maxValue
    property int minValue: 0
    property int mRedLine
    property real value

    CircularGauge
    {
        id: gauge

        value: (tacho.value) > 250 ? (tacho.value) : 250

        anchors.fill: parent

        maximumValue: tacho.maxValue
        minimumValue: tacho.minValue

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
                    color: tacho.value > tacho.mRedLine ? "#ff7011" : "white"
                }

                Image{
                    z:0
                    source: "qrc:mainCluster/tacho.png"
                    anchors.fill: parent
                }
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.2
                rotation: valueToAngle(tacho.value) - 90
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
