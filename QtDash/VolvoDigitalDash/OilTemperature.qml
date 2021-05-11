import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item
{
    id: oilTemperature
    property int maxValue
    property int minValue
    property real value

    Image
    {
        source: "qrc:accCluster/oil_temp_black.png"
        anchors.fill: parent
        z: -1
    }

    CircularGauge
    {
        id: gauge

        value: oilTemperature.value

        width: parent.width
        height: parent.height

        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/4.5

        anchors.horizontalCenter: parent.horizontalCenter

        maximumValue: oilTemperature.maxValue
        minimumValue: oilTemperature.minValue



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

                text: Number(oilTemperature.value).toFixed(1).toLocaleString(Qt.locale("en_US")) + " °F"
                color: "white"
            }

        }

        style: CircularGaugeStyle {
            maximumValueAngle: 45
            minimumValueAngle: -45

            tickmark: null
            tickmarkLabel: null
//            tickmarkStepSize: 20
//            tickmarkInset: - outerRadius * 0.2
            minorTickmark: null

            foreground: NeedleCenter {
                size: outerRadius * 0.3
                rotation: valueToAngle(oilTemperature.value) - 90
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
