import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: accWindow
    property int smallGaugeSize: if (width > height) {
                                     width / 2.4
                                 } else {
                                     height / 2.4
                                 }

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04
    property string currentStyle: "240"

    onCurrentStyleChanged: {
        currentLayout.update();
    }

    property var currentModel: {
        switch(currentStyle) {
        case "240":
            return available240Gauges;
        case "740":
            return available740Gauges;
        }
    }

    Item {
        //rotate all elements
        rotation: if (RASPBERRY_PI) {
                      90
                  } else {
                      0
                  }
        anchors.fill: parent
        focus: false

        Rectangle {
            id: container
            width: if (RASPBERRY_PI) {
                       parent.height
                   } else {
                       parent.width
                   }
            height: if (RASPBERRY_PI) {
                        parent.width
                    } else {
                        parent.height
                    }
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Loader {
                id: currentLayout
                width: container.width
                height: container.height - 50
                source: "qrc:/SideAccessoryLayout.qml"
                asynchronous: true
                visible: true
            }

            Loader {
                id: controlLayout
                anchors.fill: parent
                source: "qrc:/SideAccessoryScreenControl.qml"
                asynchronous: true
            }
         }
    }

    // 740 gauges
    property list<Component> delegates740: [
        BoostDelegate740Style {
            id: boostDelegate740
        },
        CoolantTempDelegate740Style {
            id: coolantDelegate740
        },
        FuelLevelDelegate740Style {
            id: fuelLevelDelegate740
        },
        OilTempDelegate740Style {
            id: oilTempDelegate740
        },
        OilPressureDelegate740Style {
            id: oilPressureDelegate740
        },
        VoltmeterDelegate740Style {
            id: voltMeterDelegate740
        }
    ]

    ListModel {
        id: available740Gauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "coolant temp"
        }
        ListElement {
            name: "fuel level"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "voltmeter"
        }
    }

    // 240 gauges
    property list<Component> delegates240: [
        BoostDelegate240Style {
            id: boostDelegate240
        },
        OilTempereatureDelegate240Style {
            id: oilTemperatureDelegate240
        },
        OilPressureDelegate240Style {
            id: oilPressureDelegate240
        },
        VoltmeterDelegate240Style {
            id: voltMeterDelegate240
        },
        ClockDelegate240Style {
            id: clockDelegate240Style
        }
    ]
    ListModel {
        id: available240Gauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "voltmeter"
        }
        ListElement {
            name: "clock"
        }
    }
}

