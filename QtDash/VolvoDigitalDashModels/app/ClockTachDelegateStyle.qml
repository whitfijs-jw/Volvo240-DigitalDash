import QtQuick 2.15

Component {
    id: clockTachDelegate

    Loader {
        source: "qrc:/ClockGauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = maxRpm
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0

            item.divFactor = 100.0

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/mainCluster/origclockblack.png"
            item.needleResource = "qrc:/needles/needle-240.png"

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
