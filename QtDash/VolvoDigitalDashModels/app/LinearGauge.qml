import QtQuick 2.15
import QtQuick.Controls 2.15


Item {
    id: gauge

    property int maxValue: 120
    property int minValue: 0
    property real value: 0

    property string units: "F"
    property int lowAlarm: 0
    property int highAlarm: 0
    property int offset: 0
    property int offsetX: 0
    property int initialValueOffset: 0

    property string imageResource: "qrc:/gauge-faces-544/speedo-544.png"

    property color needleColor: "orange"
    property int needleWidth: 20
    property int needleLength: width * 0.82

    property real textOffset:  parent.height / 10.0
    property real textSize: parent.height / 10.0
    property bool textEnabled: true
    property int significantDigits: 1
    width: linearSpeedoWidth
    height: linearSpeedoHeight
    layer.smooth: true
    layer.mipmap: true

    property real shear: -1.25
    property real blockWidth: width * 0.0875

    Rectangle {
        id: back
        anchors.fill: parent
        color: "black"
        z: -2
    }

    ProgressBar {
        id: control
        x: gauge.offsetX
        y: gauge.offset
        width: needleLength
        z: -1
        //anchors.fill: parent
        implicitWidth: 200
        implicitHeight: 20

        height: needleWidth
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
            width: control.visualPosition * parent.width
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
            radius: 5
            gradient: Gradient {
                    GradientStop { position: -0.5; color: "white"}
                    GradientStop { position: 0.5; color: needleColor }
                    GradientStop { position: 1.5; color: "white" }
            }
        }
    }

    Rectangle {
        id: lowerBlock
        height: needleWidth
        color: "black"
        width: blockWidth
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
        z: 0
    }

    Text {

        id: valueText

        visible: textEnabled

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenterOffset: 0

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: gauge.textOffset

        fontSizeMode: Text.Fit
        font.pixelSize: gauge.textSize

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
