import QtQuick 2.15


Item {
    id: speedo

    anchors.fill: parent

    property Component component: component

    Component {
        id: component

        Loader {
            source: "qrc:/LinearGauge.qml"
            asynchronous: true
            onLoaded: {
                item.minValue = gaugeMin
                item.maxValue = gaugeMax
                item.units = gaugeUnits
                item.lowAlarm = gaugeMin
                item.highAlarm = gaugeMax

                item.height = speedo.height
                item.width = speedo.width

                item.imageResource = "qrc:/gauge-faces-544/speedo-544-large.png"

                item.needleColor = "red"

                item.needleWidth = 0.4
                item.needleLength = 0.9

                item.offset = 0.675
                item.offsetX = 0.035

                item.textSize = 0.5
                item.textOffset = 1.0
                item.significantDigits = 0
            }

            Binding {
                target: item
                property: "value"
                value: currentValue;
            }

            Binding {
                target: item
                property: "maxValue"
                value: speedoModel.maxValue
            }

            Binding {
                target: item
                property: "width"
                value: speedo.width
            }

            Binding {
                target: item
                property: "height"
                value: speedo.height
            }
        }
    }
}
