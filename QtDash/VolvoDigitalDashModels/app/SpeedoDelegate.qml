import QtQuick 2.15


Item {
    id: speedometer

    property Component component: component

    width: parent.width
    height: parent.height
    property real minAngle: -238
    property real maxAngle: 44

    property real initialValueOffset: 5

    property real needleWidth: .02
    property real needleLength: 0.45
    property real needleOffset: 0.075
    property real needleCenterRadius: 0.1

    property real yOffset: 0

    property real gaugeMin: -1
    property real gaugeMax: -1
    property real gaugeMinOffset: -1
    property real significatDigits: 0

    property url imageSource: "qrc:/mainCluster/later-240-speedo.png"
    property url needleResource: "qrc:/needles/needle-240.png"

    property real topTextOffset: -.15
    property real topTextSize: 0.05

    property real textSize: 0.075
    property real textOffset: .175

    property bool gearInidcatorEnabled: false

    Component {
        id: component

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = minValue
                item.maxValue = maxValue
                item.units = speedUnits
                item.lowAlarm = minValue
                item.highAlarm = maxValue

                item.initialValueOffset = speedometer.initialValueOffset

                item.topValue = valueTop
                item.topUnits = valueTopUnits
                item.topValueEnabled = true
                item.topTextOffset = speedometer.topTextOffset
                item.topTextSize = speedometer.topTextSize

                item.minAngle = speedometer.minAngle
                item.maxAngle = speedometer.maxAngle

                item.height = speedometer.height
                item.width = speedometer.width

                item.imageResource = speedometer.imageSource

                item.needleResource = speedometer.needleResource

                item.needleWidth = speedometer.needleWidth
                item.needleLength =speedometer.needleLength
                item.needleOffset = speedometer.needleOffset

                item.needleCenterRadius = speedometer.needleCenterRadius

                item.textSize = speedometer.textSize
                item.textOffset = speedometer.textOffset
                item.significantDigits = speedometer.significatDigits

                item.gearValueEnabled = speedometer.gearInidcatorEnabled
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "topValue"
                value: valueTop
            }

            Binding {
                target: item
                property: "width"
                value: speedometer.width
            }

            Binding {
                target: item
                property: "height"
                value: speedometer.width
            }
        }
    }
}
