import QtQuick 2.15

Component {
    id: rpmDelegateRSport

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = maxRpm
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0

            item.initialValueOffset = 400

            item.minAngle = -140
            item.maxAngle = 126

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/gauge-faces-r-sport/r_sport_tachometer.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"

            item.needleColor = "burlywood"

            item.needleWidth = tachSize * 0.025
            item.needleLength = tachSize * 0.525
            item.needleOffset = tachSize * 0.2 / 2

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
            value: tachSize
        }

        Binding {
            target: item
            property: "height"
            value: tachSize
        }
    }
}
