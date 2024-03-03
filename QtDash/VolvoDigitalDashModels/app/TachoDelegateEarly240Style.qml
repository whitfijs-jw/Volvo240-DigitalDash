import QtQuick 2.15

Component {
    id: rpmDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = maxRpm
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0

            item.initialValueOffset = 400

            item.minAngle = -228
            item.maxAngle = 38

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/gauges-early-240/early-240-tach.png"

            item.needleResource = "qrc:/needles/needle-rsport.png"
            item.needleColor = "burlywood"

            item.needleWidth = tachSize * 0.02
            item.needleLength = tachSize * 0.45
            item.needleOffset = tachSize * 0.15 / 2

            item.needleCenterRadius = 0.10

            item.textSize = tachSize * 0.15 / 2
            item.textOffset = tachSize / 8
            item.significantDigits = 0
        }

        Binding {
            target: item
            property: "value"
            value: rpm
        }

        Binding {
            target: item
            property: "width"
            value: tachSize
        }

        Binding {
            target: item
            property: "height"
            value: tachSize
        }
    }
}
