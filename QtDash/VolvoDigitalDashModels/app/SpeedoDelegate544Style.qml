import QtQuick 2.15

Component {
    id: speedoDelegate544

    Loader {
        source: "qrc:/LinearGauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = maxValue
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = maxValue

            item.height = linearSpeedoHeight
            item.width = linearSpeedoWidth

            item.imageResource = "qrc:/gauge-faces-544/speedo-544-large.png"

            item.needleColor = "red"

            item.needleWidth = item.height * 0.4
            item.needleLength = item.width * 0.9

            item.offset = item.height * .675
            item.offsetX = item.width * 0.035

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
            value: speedoModel.maxValue
        }

        Binding {
            target: item
            property: "width"
            value: linearSpeedoWidth
        }

        Binding {
            target: item
            property: "height"
            value: linearSpeedoHeight
        }
    }
}
