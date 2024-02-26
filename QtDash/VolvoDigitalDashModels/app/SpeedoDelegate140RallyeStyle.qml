import QtQuick 2.15

Component {
    id: speedoDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = 130
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = 130

            item.initialValueOffset = 10

            item.topValue = valueTop
            item.topUnits = valueTopUnits
            item.topValueEnabled = true
            item.topTextOffset = -speedoSize / 6
            item.topTextSize = speedoSize / 20.0

            item.minAngle = -247
            item.maxAngle = 45

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/gauge-faces-140-rallye/140-rallye-speedo.png"

            item.needleResource = "qrc:/needles/needle-rsport.png"
            item.needleColor = "burlywood"

            item.needleWidth = speedoSize * 0.02
            item.needleLength = speedoSize * 0.5
            item.needleOffset = speedoSize * 0.075

            item.needleCenterRadius = 0.10

            item.textSize = speedoSize * .075
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
