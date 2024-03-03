import QtQuick 2.0

Item {
    id: warningLight
    anchors.fill: parent

    property Component component: component

    property color color: "red"
    property url imageResource: ""
    property bool overrideText: false
    property string text: ""

    Component {
        id: component

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLight.overrideText ? warningLight.text : warningLightText
                item.lightColor = warningLight.color
                item.width = warningLight.width
                item.height = warningLight.height
                item.imageSource = warningLight.imageResource
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }

            Binding {
                target: item
                property: "width"
                value: warningLight.width
            }
            Binding {
                target: item
                property: "height"
                value: warningLight.height
            }
        }
    }

}
