import QtQuick 2.15

Item {
    id: odo
    anchors.fill: parent

    property Component component: component

    Component {
        id: component

        Loader {
            source: "qrc:/Odometer.qml"
            asynchronous: true
            onLoaded: {
                item.odometerValue = odometerValue
                item.tripAValue = tripAValue
                item.tripBValue = tripBValue
            }

            Binding {
                target: item
                property: "odometerValue"
                value: odometerValue
            }

            Binding {
                target: item
                property: "tripAValue"
                value: tripAValue
            }

            Binding {
                target: item
                property: "tripBValue"
                value: tripBValue
            }

            Binding {
                target: item
                property: "width"
                value: odo.width
            }

            Binding {
                target: item
                property: "height"
                value: odo.height
            }
        }
    }
}
