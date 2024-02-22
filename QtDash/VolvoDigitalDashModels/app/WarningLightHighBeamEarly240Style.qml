import QtQuick 2.0

Component {
    id: highBeamLightEarly240Delegate

    Loader {
        source: "qrc:/WarningLight.qml"
        asynchronous: true
        onLoaded: {
            item.warningText = ""
            item.lightColor = "lightcyan"
            item.width = warningLightHeight
            item.imageSource = "qrc:/warningLights/high_beam_icon.png"
        }

        Binding {
            target: item
            property: "on"
            value: warningLightOn
        }
    }
}
