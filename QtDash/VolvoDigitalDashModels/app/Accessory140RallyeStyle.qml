import QtQuick 2.15

Item {
    id: accGauge
    property Component component: component
    property real minAngle: -135
    property real maxAngle: -45
    property real needleOffset: 0.1
    property real needleLength: 0.65
    property real needleWidth: .04
    property real yOffset: 0.25
    property real gaugeMin: -1
    property real gaugeMax: -1
    property real gaugeMinOffset: -1
    property real significatDigits: 1

    property string imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-coolant.png"

    Component {
        id: component

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = (accGauge.gaugeMin == -1) ? gaugeMin : accGauge.gaugeMin
                item.maxValue = (accGauge.gaugeMax == -1) ? gaugeMax : accGauge.gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.initialValueOffset = (accGauge.gaugeMinOffset == -1) ? gaugeMin : accGauge.gaugeMin

                item.minAngle = accGauge.minAngle
                item.maxAngle = accGauge.maxAngle

                item.height = smallGaugeSize
                item.width = smallGaugeSize

                item.imageResource = accGauge.imageSource

                item.needleResource = "qrc:/needles/needle-rsport.png"
                item.needleColor = "burlywood"
                item.needleWidth = smallGaugeNeedleWidth240
                item.needleLength = smallGaugeSize * accGauge.needleLength
                item.needleOffset = smallGaugeSize * accGauge.needleOffset
                item.needleCenterRadius = 0.15

                item.offset = smallGaugeSize * accGauge.yOffset
                item.significantDigits = accGauge.significatDigits

                item.textOffset = smallGaugeSize * 0.55
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
}
