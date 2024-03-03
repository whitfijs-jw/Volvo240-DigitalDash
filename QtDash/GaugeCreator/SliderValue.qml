import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: sliderValue
    property string name: "Current Value:"
    property real to: 100
    property real from: 0
    property real value: slider.value
    property real defaultValue: 0

    Row {
        id: currentValueContainer
        Text {
            text: name
            anchors.verticalCenter: parent.verticalCenter
        }

        Slider {
            id: slider
            from: sliderValue.from
            to: sliderValue.to
            value: defaultValue
            anchors.verticalCenter: parent.verticalCenter
        }
        TextField {
            text: slider.value
            anchors.verticalCenter: parent.verticalCenter
            onAccepted: {
                slider.value = parseFloat(text);
            }
        }
    }

}
