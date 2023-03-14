import QtQuick 2.15
import QtQuick.Window 2.15

Window {

    property int smallGaugeSize: if (width > height) {
                                     width / 2.3
                                 } else {
                                     height / 2.3
                                 }

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04


//    Component {
//        id: boostDelegate

//        Loader {
//            source: "qrc:/Gauge.qml"
//            asynchronous: true
//            onLoaded: {
//                item.minValue = gaugeMin
//                item.maxValue = gaugeMax
//                item.units = gaugeUnits
//                item.highAlarm = gaugeHighAlarm
//                item.lowAlarm = gaugeMin
//                item.initialValueOffset = gaugeMin

//                item.minAngle = -226
//                item.maxAngle = 45

//                item.height = smallGaugeSize
//                item.width = smallGaugeSize

//                item.imageResource = "qrc:/accCluster/boost_black_no_numbers.png"

//                item.needleColor = "orange"

//                item.needleWidth = smallGaugeNeedleWidth240
//                item.needleLength = smallGaugeSize * 0.55
//                item.needleOffset = smallGaugeSize * .25 / 2

//                item.needleCenterRadius = 0.15
//            }

//            Binding {
//                target: item
//                property: "value"
//                value: currentValue
//            }

//            Binding {
//                target: item
//                property: "width"
//                value: smallGaugeSize
//            }

//            Binding {
//                target: item
//                property: "height"
//                value: smallGaugeSize
//            }
//        }
//    }

    Component {
        id: voltMeterDelegate

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.minAngle = -136
                item.maxAngle = -45

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = "qrc:/accCluster/volt_black.png"

                item.needleColor = "orange"

                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * 0.65
                item.needleOffset = smallGaugeSize * .25 / 2

                item.offset = smallGaugeSize / 4.5

                item.significantDigits = 2

                item.needleCenterRadius = 0.15
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: smallGaugeSize
            }

            Binding {
                target: item
                property: "height"
                value: smallGaugeSize
            }
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
                source: "qrc:/sideScreen/SideGaugesNoControls.qml"
                asynchronous: true
                visible: true
            }
         }
    }
}

