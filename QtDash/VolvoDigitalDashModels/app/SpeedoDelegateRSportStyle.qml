import QtQuick 2.15

Component {
    id: speedoDelegateRSport

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = speedoMax
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = speedoMax

            item.initialValueOffset = 10

            item.topValue = valueTop
            item.topUnits = valueTopUnits
            item.topValueEnabled = true
            item.topTextOffset = -speedoSize / 6
            item.topTextSize = speedoSize / 20.0

            item.minAngle = -148
            item.maxAngle = 128

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_speedo_mph.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleColor = "burlywood"

            item.needleWidth = speedoSize * 0.025
            item.needleLength = speedoSize * 0.525
            item.needleOffset = speedoSize * 0.2 / 2

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
