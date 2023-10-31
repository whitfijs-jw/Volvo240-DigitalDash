import QtQuick 2.15

Component {
    id: speedoDelegate

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = minValue
            item.maxValue = speedoMax
            item.units = speedUnits
            item.lowAlarm = minValue
            item.highAlarm = speedoMax

            item.initialValueOffset = 4

            item.topValue = valueTop
            item.topUnits = valueTopUnits
            item.topValueEnabled = true
            item.topTextOffset = -speedoSize / 6
            item.topTextSize = speedoSize / 20.0

            item.minAngle = -233
            item.maxAngle = 43

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:mainCluster/early120mphspeedolo.png"

            item.needleColor = "orange"

            item.needleWidth = speedoSize * 0.02
            item.needleLength = speedoSize * 0.45
            item.needleOffset = speedoSize * 0.15 / 2

            item.needleCenterRadius = 0.10

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
