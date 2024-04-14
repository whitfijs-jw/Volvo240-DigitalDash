import QtQuick 2.15

Item {
    id: accGauge

    implicitWidth: 333
    implicitHeight: 333

    anchors.fill: parent

    property Component component: component
    property real minAngle: -135
    property real maxAngle: -44

    property real needleOffset: 0.1
    property real needleLength: 0.65
    property real needleWidth: .04
    property real needleCenterRadius: 0.15
    property real yOffset: 0.25
    property real xOffset: 0

    property real gaugeMin: -1
    property real gaugeMax: -1
    property real gaugeMinOffset: -1

    property real significatDigits: 1

    property url imageSource: "qrc:/accCluster/later-240-voltmeter.png"
    property url needleResource: "qrc:/needles/needle-240.png"

    property real textOffset: 0.525

    property bool clockwise: true

    Component {
        id: component

        Loader {
            source: "qrc:/Gauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = (accGauge.gaugeMin == -1) ? gaugeMin : accGauge.gaugeMin
                item.maxValue = (accGauge.gaugeMax == -1) ? gaugeMax : accGauge.gaugeMax
                item.units = gaugeUnits
                item.highAlarm = gaugeHighAlarm
                item.lowAlarm = gaugeLowAlarm
                item.initialValueOffset = (accGauge.gaugeMinOffset == -1) ? gaugeMin : accGauge.gaugeMin

                item.clockwise = accGauge.clockwise

                item.minAngle = accGauge.minAngle
                item.maxAngle = accGauge.maxAngle

                item.height = accGauge.height
                item.width = accGauge.width

                item.imageResource = accGauge.imageSource

                item.needleResource = accGauge.needleResource
                item.needleWidth = accGauge.needleWidth
                item.needleLength = accGauge.needleLength
                item.needleOffset = accGauge.needleOffset
                item.needleCenterRadius = accGauge.needleCenterRadius

                item.offset = accGauge.yOffset
                item.offsetX = accGauge.xOffset

                item.significantDigits = accGauge.significatDigits

                item.textOffset = accGauge.textOffset
            }

            Binding {
                target: item
                property: "value"
                value: currentValue
            }

            Binding {
                target: item
                property: "width"
                value: accGauge.width
            }

            Binding {
                target: item
                property: "height"
                value: accGauge.height
            }
        }
    }
}
