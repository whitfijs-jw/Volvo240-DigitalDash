import QtQuick 2.15

Item {
    id: blinker

    property bool on
    property bool flipped

    Image{
        id: blinkerOnImage
        z:2
        source: "qrc:/gauges-early-240/early-240-blinker-on.png"
        anchors.fill: parent
        //visible: blinker.on
        opacity: (blinker.on == true) ? 1.0 : 0.0
        rotation: (blinker.flipped) ? 180 : 0
        asynchronous: true

        Behavior on opacity {
            PropertyAnimation {
                target: blinkerOnImage
                property: "opacity"
                duration: 150
            }
        }
    }

    Image{
        id: blinkerOffImage
        z:1
        source: "qrc:/gauges-early-240/early-240-blinker-off.png"
        anchors.fill: parent
        rotation: (blinker.flipped) ? 180 : 0
        asynchronous: true
    }


}
