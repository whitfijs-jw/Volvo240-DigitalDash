import QtQuick 2.15

Component {
    id: boostDelegate740

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeMin
            item.initialValueOffset = gaugeMin

            item.minAngle = -228
            item.maxAngle = 45

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-740-940/740_boost.png"
            item.needleResource = "qrc:/needles/needle-740-940.png"

            item.needleColor = "red"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.55
            item.needleOffset = smallGaugeSize * .25 / 2

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
