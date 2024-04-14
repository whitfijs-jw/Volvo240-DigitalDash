import QtQuick 2.0

Item {
    id: blinker
    property Component component: component
    property bool flipped: false

    Component {
        id: component

        Loader {
            source: "qrc:/BlinkerEarly240.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = blinker.flipped
                item.width = blinkerSize
                item.height = blinkerSize
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: blinkerSize
            }
        }
    }
}
