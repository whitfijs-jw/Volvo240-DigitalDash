import QtQuick 2.15
//import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Item {
    id: warning_light

    property bool on
    property bool flipped
    property string warningText
    property color lightColor
    property url imageSource

    opacity: (on == true) ? 1.0 : 0.0
    height: warningLightHeight
    visible: true

    Behavior on opacity {
        PropertyAnimation {
            target: warning_light
            property: "opacity"
            duration: 250
        }
    }


    Text {
        id: warning_text
        text: warning_light.warningText
        z: 3

        anchors.fill: parent
        color: "black"

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.bold: false

        fontSizeMode: Text.Fit
        font.pixelSize: parent.height / 4.0
    }

    Image {
        id: warning_symbol
        source: warning_light.imageSource

        fillMode: Image.PreserveAspectFit
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

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
