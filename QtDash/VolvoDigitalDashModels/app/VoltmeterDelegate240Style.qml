import QtQuick 2.15

Component {
    id: voltMeterDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm

            item.minAngle = -135
            item.maxAngle = -44

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/accCluster/later-240-voltmeter.png"

            item.needleColor = "orange"

            item.needleWidth = smallGaugeNeedleWidth240
            item.needleLength = smallGaugeSize * 0.7
            item.needleOffset = smallGaugeSize * .125

            item.offset = smallGaugeSize * 0.25

            item.significantDigits = 2

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
