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
                item.lowAlarm = alarmLowFuel

                item.height = tempFuel.height
                item.width = tempFuel.width
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
