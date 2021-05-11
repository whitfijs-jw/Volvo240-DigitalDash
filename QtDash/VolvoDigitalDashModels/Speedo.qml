import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id: speedo
    property int maxSpeed
    property int minSpeed
    property real speed
    property string units

    property var topValue
    property var topUnit

    CircularGauge
    {
        id: gauge

        value: (speedo.speed <= 4.0) ? 4 : speedo.speed

        anchors.fill: parent

        maximumValue: speedo.maxSpeed
        minimumValue: speedo.minSpeed


        Rectangle
        {
            id: indexTextBox
            width: parent.width
            height: parent.height/1.2

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            color: "transparent"

            Text {
                id: topText
                property int textSize: parent.height / 13.33333

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -65

                fontSizeMode: Text.Fit
                font.pixelSize: textSize

                text: Number(speedo.topValue).toFixed(0).toLocaleString(Qt.locale("en_US")) + " " + speedo.topUnit
                color: "white"
            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 132
            minimumValueAngle: -142

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

                    text: Number(speedo.speed).toFixed(0).toLocaleString(Qt.locale("en_US")) + " " + units
                    color: "white"
                }

                Image{
                    z:0
                    source: "qrc:mainCluster/early120mphspeedolo.png"
                    anchors.fill: parent
                }
            }

            foreground: NeedleCenter {
                size: outerRadius * 0.2
                rotation: valueToAngle(speedo.speed) - 90
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
