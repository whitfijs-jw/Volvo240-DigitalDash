import QtQuick 2.15
//import QtGraphicalEffects 1.0

Item {
    property real size

    Rectangle {
        width: size
        height: size
        radius: size
        anchors.centerIn: parent

        gradient: Gradient {
                GradientStop { position: 0.0; color: "black"}
                GradientStop { position: 0.5; color: "gray" }
                GradientStop { position: 1.0; color: "black" }
        }
    }
    Rectangle {
        width: size
        height: size
        radius: size
        anchors.centerIn: parent
        color: "transparent"
        border.width: size/15
        border.color: "gray"
    }
}
