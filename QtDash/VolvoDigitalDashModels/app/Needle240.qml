import QtQuick 2.15
import QtQuick.Shapes 1.15

Item {
    property real length: 100
    property real needleWidth: 15
    property real needleTipRadius: 25
    property color needleColor: "orange"

    antialiasing: true
    smooth: true

    Shape {
        anchors.verticalCenter: parent.verticalCenter
        antialiasing: true
        smooth: true
        ShapePath {
            fillGradient: LinearGradient {
                x1: 0; y1: -needleWidth / 2.0
                x2: 0; y2: needleWidth / 2.0
                GradientStop { position: 0.25; color: needleColor}
                GradientStop { position: 0.5; color: "white" }
                GradientStop { position: 0.75; color: needleColor }
            }
            strokeColor: needleColor
            startY: needleWidth / 2.0
            startX: 0
            PathLine { y: needleWidth / 2.0; x: (length - needleTipRadius) }
            PathLine { y: 0; x: length }
            PathLine { y: -needleWidth / 2.0; x: (length - needleTipRadius) }
            PathLine { y: -needleWidth / 2.0; x: 0 }
            PathArc { y: needleWidth / 2.0; x: 0; radiusX: needleTipRadius / 4; radiusY: needleTipRadius / 4; direction: PathArc.Counterclockwise}
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}D{i:11}
}
##^##*/
