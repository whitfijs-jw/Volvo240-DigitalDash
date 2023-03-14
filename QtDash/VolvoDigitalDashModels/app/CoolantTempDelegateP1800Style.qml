import QtQuick 2.15

Component {
    id: coolantTempDelegateP1800

    Loader {
        source: "qrc:/LinearGauge.qml"
        asynchronous: true
        onLoaded: {
            item.minValue = 90
            item.maxValue = 230
            item.units = gaugeUnits
            item.highAlarm = gaugeHighAlarm
            item.lowAlarm = gaugeLowAlarm

            item.height = 20
            item.width = 125

            item.imageResource = ""

            item.needleColor = "goldenrod"

            item.needleWidth = item.height
            item.needleLength = item.width

            item.offset = 0
            item.offsetX = 0

            item.textSize = item.width * 0.2
            item.textOffsetY = item.width * 0.70
            item.textRotation = 90
            item.significantDigits = 0

            item.blockWidth = 0
            item.shear = 0
            item.barRadius = 2
        }

        Binding {
            target: item
            property: "value"
            value: currentValue
        }

        Binding {
            target: item
            property: "width"
            value: 80
        }

        Binding {
            target: item
            property: "height"
            value: 15
        }
    }
}
