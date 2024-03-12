import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: gauge

    width: parent.width
    height: parent.height

    property bool clockwise: true
    property real maxValue: 100
    property real minValue: 0
    property real value: 0
    property real internalValue: clockwise ? value : (maxValue - (value - minValue))
    property real angle: (internalValue <= initialValueOffset) ?
                           (initialValueOffset - minValue) / (maxValue - minValue) * (maxAngle - minAngle) + minAngle :
                           (internalValue - minValue) / (maxValue - minValue) * (maxAngle - minAngle) + minAngle;
    property string units: "F"
    property real lowAlarm: 0
    property real highAlarm: 0
    property real offset: 0
    property real offsetX: 0
    property real initialValueOffset: 0

    property int minAngle: -235
    property int maxAngle: 45

    property real needleWidth: 0.03
    property real needleLength: 0.6
    property real needleTipRadius: needleWidth
    property real needleOffset: .20

    property real needleCenterRadius: 0.15

    property string imageResource
    property string needleResource: "qrc:/needles/needle-240.png"

    property color needleColor: "orange"

    property real textOffset:  0.5
    property real textXOffset: 0
    property real textSize: 1 / 8.0
    property bool textEnabled: true
    property int significantDigits: 1

    property string topUnits: "F"
    property real topValue: 0
    property real topTextSize: 1 / 16.0
    property real topTextOffset: 1 / 4.0
    property bool topValueEnabled: false

    property real dir: RotationAnimation.Numerical

    function boundedAngle(angle, min, max) {
        if (angle > max) {
            angle = max;
        } else if (angle < min) {
            angle = min;
        }

        return angle;
    }

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Image {
            source: gauge.imageResource
            cache: true
            rotation: 0
            anchors.fill: parent
            mipmap: true
            z: -1
        }

        NeedleCenter {
            id: needleCenter
            size: needleCenterRadius * parent.width
            x: parent.width * 0.5 + parent.width * gauge.offsetX
            y: parent.width * 0.5 + parent.width * gauge.offset
            antialiasing: true
            smooth: true

            transform: [
                Rotation {
                    angle: gauge.angle > gauge.maxAngle ?
                               gauge.maxAngle : (gauge.angle < minAngle) ?
                                   gauge.minAngle : gauge.angle
                    origin.x: 0
                    origin.y: 0

                    Behavior on angle {
                        RotationAnimation {
                            duration: 150
                            direction: gauge.dir
                        }
                    }
                }
            ]
        }

        Image {
            id: needle

            x: parent.width * 0.5 + parent.width * gauge.offsetX
            y: parent.width * 0.5 + parent.width * gauge.offset
            width: parent.height * gauge.needleLength
            height: parent.height * gauge.needleWidth

            antialiasing: true
            smooth: true
            source: needleResource

            transform: [
                Translate {
                    y: -needle.height / 2
                    x: -parent.height * needleOffset
                },

                Rotation {
                    angle: gauge.angle > gauge.maxAngle ?
                               gauge.maxAngle : (gauge.angle < minAngle) ?
                                   gauge.minAngle : gauge.angle
                    origin.x: 0
                    origin.y: 0

                    Behavior on angle {
                        RotationAnimation {
                            duration: 150
                            direction: gauge.dir
                        }
                    }
                }
            ]
        }

        Text {

            id: valueText
            z: 10
            visible: textEnabled

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.height * gauge.textXOffset
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.height * gauge.textOffset

            fontSizeMode: Text.Fit
            font.pixelSize: parent.height * gauge.textSize

            text: Number(gauge.value).toFixed(significantDigits).toLocaleString(Qt.locale("en_US")) + " " + units
            color: ( (gauge.value < gauge.lowAlarm)  || (gauge.value > gauge.highAlarm))
                   ? "#ff7011" : "white"
        }

        Text {

            id: topValueText

            visible: topValueEnabled

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: 0

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: parent.height * gauge.topTextOffset

            fontSizeMode: Text.Fit
            font.pixelSize: parent.height * gauge.topTextSize

            text: Number(gauge.topValue).toFixed(1).toLocaleString(Qt.locale("en_US")) + " " + gauge.topUnits
            color: "white"
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:3;height:140;width:140}D{i:2}D{i:3}D{i:5}D{i:12}D{i:1}
}
##^##*/
