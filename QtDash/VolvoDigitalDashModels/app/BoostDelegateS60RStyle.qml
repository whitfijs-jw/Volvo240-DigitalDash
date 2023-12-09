import QtQuick 2.15

Component {
    id: boostDelegateS60R

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = -15
            item.maxValue = 30
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeMin
            item.initialValueOffset = gaugeMin

            item.minAngle = -270
            item.maxAngle = 0

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-s60r/s60r_boost.png"
            item.needleResource = "qrc:/needles/needle_s60r.png"

            item.needleCenterImageSize = smallGaugeSize * 0.35
            item.needleCenterUseImage = true
            item.needleCenterImageResource = "qrc:/needles/needle_center_s60r.png"

            item.needleWidth = smallGaugeSize * 0.05
            item.needleLength = smallGaugeSize * 0.55
            item.needleOffset = smallGaugeSize * 0.165
            item.offset = 0

            item.significantDigits = 1
            item.textSize = smallGaugeSize / 12
            item.textOffset = smallGaugeSize * 0.55

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
