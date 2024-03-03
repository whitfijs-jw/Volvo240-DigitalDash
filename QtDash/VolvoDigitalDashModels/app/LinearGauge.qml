import QtQuick 2.15
import QtQuick.Controls 2.15


Item {
    id: gauge

    width: parent.width
    height: parent.height

    property int maxValue: 1000
    property int minValue: 0
    property real value: 500

    property string units: "F"
    property int lowAlarm: 0
    property int highAlarm: 0
    property real offset: 0
    property real offsetX: 0
    property int initialValueOffset: 0

    property string imageResource: "qrc:/gauge-faces-544/speedo-544.png"

    property color needleColor: "orange"
    property real needleWidth: 0.3
    property real needleLength: 0.82

    property real textOffset: 0.1
    property real textOffsetY: 0.0
    property real textSize: 0.1
    property bool textEnabled: true
    property real textRotation: 0.0

    property int significantDigits: 1

    layer.smooth: true
    layer.mipmap: true

    property real shear: -1.25
    property real blockWidth: 0.0875
    property real barRadius: 5

    Rectangle {
        id: back
        anchors.fill: parent
        color: "black"
        z: -2
    }

    ProgressBar {
        id: control
        x: gauge.offsetX * gauge.width
        y: gauge.offset * gauge.height
        width: needleLength * gauge.width
        z: 0
        //anchors.fill: parent
        implicitWidth: 200
        implicitHeight: 20

        height: needleWidth * gauge.height
        antialiasing: true

        value: gauge.value
        from: gauge.minValue
        to: gauge.maxValue

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }

        contentItem: Rectangle {
            id: bar
            width: control.visualPosition > 0.0 ? control.visualPosition * parent.width : 0.0
            antialiasing: true
            smooth: true
            height: parent.height
            transform: Matrix4x4 {
                matrix : Qt.matrix4x4(
                             1, gauge.shear, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1)
            }
            radius: gauge.barRadius
            gradient: Gradient {
                    GradientStop { position: -0.5; color: "white"}
                    GradientStop { position: 0.5; color: needleColor }
                    GradientStop { position: 1.5; color: "white" }
            }


            Behavior on width {
                NumberAnimation {
                    duration: 150
                }
            }
        }
    }

    Rectangle {
        id: lowerBlock
        height: needleWidth * gauge.height * 1.1
        color: "black"
        width: blockWidth * gauge.width
        anchors.left: parent.left
        anchors.verticalCenter: control.verticalCenter
    }

    Image {
        id: image
        cache: true
        rotation: 0
        anchors.fill: parent
        source: imageResource
        mipmap: true
        z: -1
    }

    Text {

        id: valueText

        visible: textEnabled

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        rotation: gauge.textRotation

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: gauge.textOffsetY * gauge.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: gauge.textOffset * gauge.height

        fontSizeMode: Text.Fit
        font.pixelSize: gauge.textSize * gauge.height

        text: Number(gauge.value).toFixed(significantDigits).toLocaleString(Qt.locale("en_US")) + " " + units
        color: ( (gauge.value < gauge.lowAlarm)  || (gauge.value > gauge.highAlarm))
               ? "#ff7011" : "white"
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:7;invisible:true}
}
##^##*/
