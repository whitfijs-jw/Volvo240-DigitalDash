import QtQuick 2.15

Component {
    id: coolant740Delegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm

            item.minAngle = -115
            item.maxAngle = -65

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-740-940/740_coolant_temp.png"
            item.needleResource = "qrc:/needles/needle-740-940.png"

            item.needleColor = "red"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.75
            item.needleOffset = smallGaugeSize * 0.25 / 2
            item.offset = smallGaugeSize / 4.5

            item.significantDigits = 0

            item.needleCenterRadius = 0.25
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
