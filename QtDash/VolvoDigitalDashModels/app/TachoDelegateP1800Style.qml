import QtQuick 2.15

Component {
    id: rpmDelegateP1800

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = 7000
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0

            item.initialValueOffset = 0

            item.minAngle = -221
            item.maxAngle = 35

            item.height = speedoSize
            item.width = speedoSize

            item.imageResource = "qrc:/gauge-faces-p1800/tach-p1800.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleColor = "burlywood"

            item.needleWidth = item.width * 0.025
            item.needleLength = item.width * 0.375
            item.needleOffset = 0

            item.needleCenterRadius = 0.125

            item.textSize = tachSize * 0.15 / 2
            item.textOffset = tachSize / 6
            item.significantDigits = 0
        }

        Binding {
            target: item
            property: "value"
            value: rpm
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
