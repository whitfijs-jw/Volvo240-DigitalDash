import QtQuick 2.15

Component {
    id: clockSpeedoDelegate

    Loader {
        source: "qrc:/ClockGauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = speedoMax
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = speedoMax

            item.divFactor = 1.0

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/mainCluster/origclockblack.png"
            item.needleResource = "qrc:/needles/needle-240.png"

            item.textSize = speedoSize * 0.15 / 2
            item.textOffset = speedoSize / 8
            item.significantDigits = 0
        }

        Binding {
            target: item
            property: "value"
            value: currentValue
        }

        Binding {
            target: item
            property: "width"
            value: speedoSize
        }

        Binding {
            target: item
            property: "height"
            value: speedoSize
        }
    }
}
