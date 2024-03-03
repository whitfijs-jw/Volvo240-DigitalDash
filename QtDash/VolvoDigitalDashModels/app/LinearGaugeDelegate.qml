import QtQuick 2.15

Item {
    id: gauge
    width: parent.width
    height: parent.height

    property Component component: component

    property real minValue: 90
    property real maxValue: 230

    property int significantDigits: 0

    property real blockWidth: 0
    property real shear: 0
    property real barRadius: 2

    property color needleColor: "goldenrod"

    property url imageResource: ""

    property real yOffset: 0
    property real xOffset: 0

    property real textSize: 0.2
    property real textYOffset: 0.7
    property real textRotation: 90

    property real needleWidth: 1.0
    property real needleLength: 1.0

    Component {
        id: component

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gauge.minValue
                item.maxValue = gauge.maxValue
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm

                item.height = gauge.height
                item.width = gauge.width

                item.imageResource = gauge.imageResource

                item.needleColor = gauge.needleColor

                item.needleWidth = gauge.needleWidth
                item.needleLength = gauge.needleLength

                item.offset = gauge.yOffset
                item.offsetX = gauge.xOffset

                item.textSize = gauge.textSize
                item.textOffsetY = gauge.textYOffset
                item.textRotation = gauge.textRotation
                item.significantDigits = gauge.significantDigits

                item.blockWidth = gauge.blockWidth
                item.shear = gauge.shear
                item.barRadius = gauge.barRadius
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: gauge.width
            }

            Binding {
                target: item
                property: "height"
                value: gauge.height
            }
        }
    }
}
