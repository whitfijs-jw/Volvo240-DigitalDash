import QtQuick 2.15

Component {
    id: clockDelegate
    Loader {
        source: "qrc:/Clock.qml"
        asynchronous: true
        onLoaded: {
            item.height = smallGaugeSize
            item.width = smallGaugeSize
        }

        Binding {
            target: item
            property: "width"
            value: smallGaugeSize
        }

        Binding {
            target: item
            property: "height"
            value: smallGaugeSize
        }
    }
}
