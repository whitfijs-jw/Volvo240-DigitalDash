import QtQuick 2.15

Item {
    id: tachometer

    property Component component: component

    width: parent.width
    height: parent.height

    property real minAngle: -221
    property real maxAngle: 33

    property real initialValueOffset: 250

    property real needleWidth: .02
    property real needleLength: 0.45
    property real needleOffset: 0.075
    property real needleCenterRadius: 0.1

    property real yOffset: 0

    property real gaugeMin: -1
    property real gaugeMax: -1
    property real gaugeMinOffset: -1
    property real significatDigits: 0

    property url imageSource: "qrc:/mainCluster/later-240-tacho.png"
    property url needleResource: "qrc:/needles/needle-240.png"

    property real textSize: 0.075
    property real textOffset: .175

    Component {
        id: component

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = 0
                item.maxValue = maxRpm
                item.units = "rpm"
                item.highAlarm = redLine
                item.lowAlarm = 0

                item.initialValueOffset = tachometer.initialValueOffset

                item.minAngle = tachometer.minAngle
                item.maxAngle = tachometer.maxAngle

                item.height = tachometer.height
                item.width = tachometer.width

                item.imageResource = tachometer.imageSource
                item.needleResource = tachometer.needleResource

                item.needleWidth = tachometer.needleWidth
                item.needleLength = tachometer.needleLength
                item.needleOffset = tachometer.needleOffset

                item.needleCenterRadius = tachometer.needleCenterRadius

                item.textSize = tachometer.textSize
                item.textOffset = tachometer.textOffset
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
                value: tachometer.width
            }

            Binding {
                target: item
                property: "height"
                value: tachometer.height
            }
        }
    }
}
