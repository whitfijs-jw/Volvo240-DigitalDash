import QtQuick 2.15

Component {
    id: rpmDelegate740

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = maxRpm
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0
            item.initialValueOffset = 200

            item.minAngle = -220
            item.maxAngle = 40

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/gauge-faces-740-940/740_tach.png"
            item.needleResource = "qrc:/needles/needle-740-940.png"

            item.needleColor = "red"

            item.needleWidth = tachSize * 0.035
            item.needleLength = tachSize * 0.45
            item.needleOffset = tachSize * 0.15 / 2

            item.needleCenterRadius = 0.15

            item.textSize = 20
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
