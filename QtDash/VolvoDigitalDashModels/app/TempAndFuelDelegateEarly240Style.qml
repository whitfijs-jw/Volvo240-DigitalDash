import QtQuick 2.15

Component {
    id: tempFuelDelegate
    Loader {
        source: "qrc:/TempCoolant.qml"
        asynchronous: true
        onLoaded: {
            item.maxCoolantTemp = tempMax
            item.minCoolantTemp = tempMin
            item.units = tempUnits

            item.highAlarm = alarmHighTemp
            item.lowAlarm = 0

            item.height = tempFuelSize
            item.width = tempFuelSize

            item.overlayImageSource = "qrc:/gauges-early-240/early-240-temp-fuel-overlay-with-border.png"
            item.gaugeImageResource = "qrc:/gauges-early-240/early-240-temp-fuel-with-border.png"

            item.needleResource = "qrc:/needles/needle-rsport.png"
            item.needleLength = tempFuelSize * 0.4
            item.needleWidth = tempFuelSize * 0.02

            item.offsetX = -tempFuelSize * 0.05

            item.textXOffset = tempFuelSize * 0.375
            item.textOffset = tempFuelSize * 0.25
            item.textSize = tempFuelSize * 0.04
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
            value: tempFuelSize
        }

        Binding {
            target: item
            property: "height"
            value: tempFuelSize
        }
    }
}
