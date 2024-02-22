import QtQuick 2.0

Component {
    id: oilWarningLightEarly240Delegate

    Loader {
        source: "qrc:/WarningLight.qml"
        asynchronous: true
        onLoaded: {
            item.warningText = "OIL"
            item.lightColor = "red"
            item.width = warningLightHeight
            item.imageSource = ""
        }

        Binding {
            target: item
            property: "on"
            value: warningLightOn
        }
    }
}
