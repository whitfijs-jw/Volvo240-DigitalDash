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

            item.initialValueOffset = 250

            item.minAngle = -221
            item.maxAngle = 33

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/mainCluster/later-240-tacho.png"

            item.needleColor = "orange"

            item.needleWidth = tachSize * 0.02
            item.needleLength = tachSize * 0.45
            item.needleOffset = tachSize * 0.15 / 2

            item.needleCenterRadius = 0.10

            item.textSize = tachSize * 0.15 / 2
            item.textOffset = tachSize / 6
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
