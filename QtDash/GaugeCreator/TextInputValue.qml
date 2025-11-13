import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: sliderValue
    property string name: "Current Value:"
    property real defaultValue: 0
    property real value: parseFloat(valueInput.text)
    property string text: valueInput.text

    Row {
        id: currentValueContainer
        Text {
            text: name
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            id: valueInput
            placeholderText: name
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            anchors.verticalCenter: parent.verticalCenter
            text: defaultValue
        }
    }

}
