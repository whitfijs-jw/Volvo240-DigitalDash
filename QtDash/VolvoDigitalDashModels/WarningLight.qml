import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    id: warning_light

    property bool on
    property bool flipped
    property string warningText
    property color lightColor

    height: warningLightHeight
    width: warningLightWideWidth
    visible: on

    Label {
        id: warning_text
        text: warning_light.warningText
        z: 3

        anchors.fill: parent
        color: "black"

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.bold: true
    }

    Rectangle {
        anchors.fill: parent
        color: warning_light.lightColor
        z: 2
    }

    onWidthChanged: {
        //console.debug("Size changed " + parent.width + " x " + parent.height)
    }
}
