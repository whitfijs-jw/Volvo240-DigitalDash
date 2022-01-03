import QtQuick 2.12
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Item {
    id: warning_light

    property bool on
    property bool flipped
    property string warningText
    property color lightColor
    property url imageSource

    height: warningLightHeight
    visible: on

    Label {
        id: warning_text
        text: warning_light.warningText
        z: 3

        anchors.fill: parent
        color: "black"

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.bold: false
    }

    Image {
        id: warning_symbol
        source: warning_light.imageSource
        smooth: true
        mipmap: true

        anchors.fill: parent
        z: 3
        asynchronous: true
    }

    Rectangle {
        id: backLight
        anchors.fill: parent
        color: warning_light.lightColor
        border.color: Qt.rgba(0, 0, 0, 0.01)
        border.width: 1
        layer.enabled: true
        layer.effect: InnerShadow {
            color: "black"
            samples: 20
            radius: 5
            spread: 0.01
        }
    }

    onWidthChanged: {
        //console.debug("Size changed " + parent.width + " x " + parent.height)
    }
}
