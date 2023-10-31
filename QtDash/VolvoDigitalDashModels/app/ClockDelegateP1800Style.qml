import QtQuick 2.15

Component {
    id: clockDelegate
    Loader {
        source: "qrc:/Clock.qml"
        asynchronous: true
        onLoaded: {
            item.height = smallGaugeSize
            item.width = smallGaugeSize

            item.needleCenterRadius = 0.05

            item.imageResource = "qrc:/gauge-faces-p1800/clock-p1800.png"
            item.needleResource = "qrc:/needles/needle-rsport.png"
        }

        Binding {
            target: item
            property: "width"
            value: smallGaugeSize
        }

        Binding {
            target: item
            property: "height"
            value: smallGaugeSize
        }
    }
}
