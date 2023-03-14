import QtQuick 2.15

Component {
    id: coolantDelegateRSport


    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm
            item.clockwise = false

            item.minAngle = -35
            item.maxAngle = 38

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_coolant_fahrenhet.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleColor = "burlywood"

            item.needleWidth = smallGaugeSize * 0.035
            item.needleLength = smallGaugeSize * 0.65
            item.needleOffset = smallGaugeSize * 0.25 / 2
            item.offsetX = -smallGaugeSize / 7.4

            item.significantDigits = 0

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
