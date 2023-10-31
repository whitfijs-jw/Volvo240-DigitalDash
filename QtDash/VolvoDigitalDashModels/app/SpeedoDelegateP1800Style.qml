import QtQuick 2.15

Component {
    id: speedoDelegateP1800

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = speedoMax
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = speedoMax

            item.initialValueOffset = 0

            item.topValue = valueTop
            item.topUnits = valueTopUnits
            item.topValueEnabled = true
            item.topTextOffset = -speedoSize / 6
            item.topTextSize = speedoSize / 20.0

            item.minAngle = -225
            item.maxAngle = 40

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/gauge-faces-p1800/speedo-mph-p1800.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleColor = "burlywood"

            item.needleWidth = item.width * 0.025
            item.needleLength = item.width * 0.375
            item.needleOffset = 0

            item.needleCenterRadius = 0.125

            item.textSize = speedoSize * .15 / 2
            item.textOffset = speedoSize / 6
            item.significantDigits = 0
        }

        Binding {
            target: item
            property: "value"
            value: currentValue;
        }

        Binding {
            target: item
            property: "maxValue"
            value: speedoMax
        }

        Binding {
            target: item
            property: "topValue"
            value: valueTop
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
