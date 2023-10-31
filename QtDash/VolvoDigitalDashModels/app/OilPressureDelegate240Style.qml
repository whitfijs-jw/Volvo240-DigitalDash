import QtQuick 2.15

Component {
    id: oilPressureDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = gaugeMin
            item.maxValue = gaugeMax
            item.units = gaugeUnits
            item.highAlarm = gaugeMax
            item.lowAlarm = gaugeLowAlarm

            item.minAngle = -136
            item.maxAngle = -45

            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.imageResource = "qrc:/accCluster/oil_pressure_black.png"

            item.needleColor = "orange"

            item.needleWidth = smallGaugeNeedleWidth240
            item.needleLength = smallGaugeSize * 0.65
            item.needleOffset = smallGaugeSize * .25 / 2

            item.offset = smallGaugeSize / 4.5

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
