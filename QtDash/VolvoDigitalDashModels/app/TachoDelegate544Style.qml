import QtQuick 2.15


Item {
    id: tach

    anchors.fill: parent

    property Component component: component

    Component {
        id: component

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = maxRpm
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.height = tach.height
                item.width = tach.width

                item.imageResource = "qrc:/gauge-faces-544/tachometer-544.png"

                item.needleColor = "red"

                item.needleWidth = 0.4
                item.needleLength = 0.775

                item.offset = 0.625
                item.offsetX = 0.15

                item.textSize = 0.5
                item.textOffset = -0.8
                item.significantDigits = 0

                item.blockWidth = 0.15

            }

            Binding {
                target: item
                property: "value"
                value: rpm
            }

            Binding {
                target: item
                property: "width"
                value: tach.width
            }

            Binding {
                target: item
                property: "height"
                value: tach.height
            }
        }
    }
}
