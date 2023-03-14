import QtQuick 2.15

Component {
    id: rpmDelegate544

    Loader {
        source: "qrc:/LinearGauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 0
            item.maxValue = maxRpm
            item.units = "rpm"
            item.highAlarm = redLine
            item.lowAlarm = 0

            item.height = 64
            item.width = 600

            item.imageResource = "qrc:/gauge-faces-544/tachometer-544.png"

            item.needleColor = "red"

            item.needleWidth = item.height * 0.4
            item.needleLength = item.width * 0.775

            item.offset = item.height * .625
            item.offsetX = item.width * 0.15

            item.textSize = speedoSize * .15 / 2
            item.textOffset = - speedoSize / 8
            item.significantDigits = 0

            item.blockWidth = item.width * 0.15

        }

        Binding {
            target: item
            property: "value"
            value: rpm
        }

        Binding {
            target: item
            property: "width"
            value: 600
        }

        Binding {
            target: item
            property: "height"
            value: 64
        }
    }
}
