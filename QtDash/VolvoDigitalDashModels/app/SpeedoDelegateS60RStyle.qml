import QtQuick 2.15

Component {
    id: speedoDelegateS60R

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

            item.minAngle = -210
            item.maxAngle = 30

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/gauge-faces-s60r/s60r_speedo.png"
            item.needleResource = "qrc:/needles/needle_s60r.png"

            item.needleCenterImageSize = speedoSize / 5
            item.needleCenterUseImage = true
            item.needleCenterImageResource = "qrc:/needles/needle_center_s60r.png"

            item.needleColor = "red"

            item.needleWidth = speedoSize * 0.0325
            item.needleLength = speedoSize * 0.55
            item.needleOffset = speedoSize * 0.10

            item.textSize = speedoSize / 20
            item.textOffset = speedoSize / 5
            item.significantDigits = 0

            item.topValue = valueTop
            item.topUnits = valueTopUnits
            item.topValueEnabled = true
            item.topTextOffset = speedoSize / 3.5
            item.topTextSize = speedoSize / 20
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
