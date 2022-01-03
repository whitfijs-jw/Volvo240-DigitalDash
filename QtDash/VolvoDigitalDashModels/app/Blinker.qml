import QtQuick 2.0

Item {
    id: blinker

    property bool on
    property bool flipped

    Image{
        id: blinkerOnImage
        z:2
        source: "qrc:mainCluster/arrow_on.png"
        anchors.fill: parent
        visible: blinker.on
        rotation: (blinker.flipped) ? 180 : 0
    }

    Image{
        id: blinkerOffImage
        z:1
        source: "qrc:mainCluster/arrow_off.png"
        anchors.fill: parent
        rotation: (blinker.flipped) ? 180 : 0
    }
}
