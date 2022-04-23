import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: odometer

    property real odometerValue
    property real tripAValue
    property real tripBValue

    property real textOffset:  0
    property real textSize: parent.height / 4.0
    property bool textEnabled: true
    property int significantDigits: 1

    width: parent.width
    height: parent.height

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Text {
            id: labelText

            visible: textEnabled
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: 0

            anchors.fill: parent

            fontSizeMode: Text.Fit
            font.pixelSize: odometer.textSize

            text:  "\nTrip A: " + "\nTrip B: "
            color: "white"
        }

        Text {
            id: valueText

            visible: textEnabled

            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            anchors.fill: parent

            fontSizeMode: Text.Fit
            font.pixelSize: odometer.textSize

            text: odometerValue.toFixed(significantDigits) + "\n" + tripAValue.toFixed(significantDigits) + "\n" + tripBValue.toFixed(significantDigits)
            color: "white"
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:3;height:140;width:140}D{i:2}D{i:3}D{i:5}D{i:12}D{i:1}
}
##^##*/
