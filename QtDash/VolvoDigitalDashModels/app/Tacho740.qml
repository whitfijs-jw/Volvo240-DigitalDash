import QtQuick 2.15
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
            maximumValueAngle: 130
            minimumValueAngle: -133

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
                    source: "qrc:gauge-faces-740-940/740_tach.png"
                    anchors.fill: parent
                    asynchronous: true
                }
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: boundedAngle(valueToAngle(tacho.value), minimumValueAngle, maximumValueAngle) - 90
            }

            needle: Rectangle {
                y: - outerRadius * 0.3
                radius: outerRadius * 0.025
                implicitWidth: outerRadius * 0.85
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
