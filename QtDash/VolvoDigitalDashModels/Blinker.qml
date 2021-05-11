import QtQuick 2.0

Item {
    id: blinker

    function startBlinker() {
        blinkTimer.running = true;
    }

    function stopBlinker() {
        blinkTimer.running = false;
        blinkerOnImage.visible = false;
    }

    Timer {
        id: blinkTimer
        interval: 500
        running: false
        repeat: true

        onTriggered: {
            if( blinkerOnImage.visible ){
                blinkerOnImage.visible = false;
            }else{
                blinkerOnImage.visible = true;
            }
        }
    }

    Image{
        id: blinkerOnImage
        z:1
        source: "qrc:mainCluster/arrow_on.png"
        anchors.fill: parent
        visible: false
    }

    Image{
        id: blinkerOffImage
        z:-1
        source: "qrc:mainCluster/arrow_off.png"
        anchors.fill: parent
    }
}
