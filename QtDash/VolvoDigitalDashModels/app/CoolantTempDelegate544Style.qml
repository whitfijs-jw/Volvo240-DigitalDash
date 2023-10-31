import QtQuick 2.15

Component {
    id: coolantTempDelegate544

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm
            item.clockwise = true

            item.minAngle = -130
            item.maxAngle = -55

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-544/coolant-temp-544.png"
            item.needleResource = "qrc:/needles/needle-544-140.png"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.75
            item.needleOffset = smallGaugeSize * 0.25 / 2
            item.offset = smallGaugeSize / 4.0

            item.textOffset = -item.height / 2.0

            item.significantDigits = 1

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
