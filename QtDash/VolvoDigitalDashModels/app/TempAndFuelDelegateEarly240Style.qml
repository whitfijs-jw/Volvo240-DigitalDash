import QtQuick 2.15

Item {
    id: tempFuel
    property Component component: component
    width: parent.width
    height: parent.height

    Component {
        id: component
        Loader {
            source: "qrc:/TempCoolant.qml"
            asynchronous: true
            onLoaded: {
                item.maxCoolantTemp = tempMax
                item.minCoolantTemp = tempMin
                item.units = tempUnits

                item.highAlarm = alarmHighTemp
                item.lowAlarm = 0

                item.height = tempFuel.width
                item.width = tempFuel.width

                item.overlayImageSource = "qrc:/gauges-early-240/early-240-temp-fuel-overlay-with-border.png"
                item.gaugeImageResource = "qrc:/gauges-early-240/early-240-temp-fuel-with-border.png"

                item.needleResource = "qrc:/needles/needle-rsport.png"
                item.needleLength = 0.4
                item.needleWidth = 0.02

                item.offsetX = -0.05

                item.textXOffset = 0.375
                item.textOffset = 0.25
                item.textSize = 0.04
                item.enableFuelText = true;
            }

            Binding {
                target: item
                property: "coolantTemp"
                value: currentTemp;
            }

            Binding {
                target: item
                property: "fuelLevel"
                value: currentFuelLevel
            }

            Binding {
                target: item
                property: "width"
                value: tempFuel.width
            }

            Binding {
                target: item
                property: "height"
                value: tempFuel.height
            }
        }
    }
}
