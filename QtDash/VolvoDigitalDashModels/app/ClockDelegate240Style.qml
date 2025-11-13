import QtQuick 2.15

Item {
    id: clock

    implicitWidth: 333
    implicitHeight: 333

    anchors.fill: parent

    property Component component: component

    Component {
        id: component
        Loader {
            source: "qrc:/Clock.qml"
            asynchronous: true
            onLoaded: {
                item.height = clock.height
                item.width = clock.width
            }

            Binding {
                target: item
                property: "width"
                value: clock.width
            }

            Binding {
                target: item
                property: "height"
                value: clock.height
            }
        }
    }
}
