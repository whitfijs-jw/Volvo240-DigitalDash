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
            item.lowAlarm = alarmLowFuel

            item.height = tempFuelSize
            item.width = tempFuelSize
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
