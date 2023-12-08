import QtQuick 2.15

Component {
    id: rpmDelegateS60R

    Loader {
        source: "qrc:/Gauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = 8000
            item.units = "rpm"
            item.highAlarm = 7000
            item.lowAlarm = 0

            item.initialValueOffset = 0

            item.minAngle = -210
            item.maxAngle = 30

            item.height = tachSize
            item.width = tachSize

            item.imageResource = "qrc:/gauge-faces-s60r/tach_400.png"
            item.needleResource = "qrc:/needles/needle_s60r.png"

            item.needleColor = "red"

            item.needleWidth = speedoSize * 0.0325
            item.needleLength = speedoSize * 0.55
            item.needleOffset = speedoSize * 0.10

            item.textSize = speedoSize / 15
            item.textOffset = speedoSize / 5
            item.significantDigits = 0

            item.textSize = tachSize / 20
            item.textOffset = tachSize / 5
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
