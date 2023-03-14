import QtQuick 2.15
import QtQuick.Window 2.15

Window {

    property int smallGaugeSize: if (width > height) {
                                     width / 2.3
                                 } else {
                                     height / 2.3
                                 }

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04

    BoostDelegate240Style {
        id: boostDelegate
    }

    VoltmeterDelegate240Style {
        id: voltMeterDelegate
    }

    Item {
        //rotate all elements
        rotation: if (RASPBERRY_PI) {
                      90
                  } else {
                      0
                  }
        anchors.fill: parent

        Rectangle {
            width: if (RASPBERRY_PI) {
                       parent.height
                   } else {
                       parent.width
                   }
            height:  if (RASPBERRY_PI) {
                         parent.width
                     } else {
                         parent.height
                     }
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Loader {
                id: currentLayout
                anchors.fill: parent
                source: "qrc:/SideGaugesNoControls.qml"
                asynchronous: true
                visible: true
            }
         }
    }
}

