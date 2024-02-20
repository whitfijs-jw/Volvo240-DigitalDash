import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15

Window {
    width: 440
    height: 440
    visible: true
    title: qsTr("VolvoDash Gauge Delegate Generator")
    property int smallGaugeSize: 440
    property alias gauge: currentGauge

    Window {
        width: 400
        height: 800
        visible: true

        GridLayout {
            id: values
            anchors.fill: parent
            columns: 1
            SliderValue {
                Layout.row: 0
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: currentValue
                name: "Current value"
                to: gauge.maxValue
                from: gauge.minValue
                Binding {
                    target: gauge
                    property: "value"
                    value: currentValue.value
                }
            }
            TextInputValue {
                Layout.row: 1
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: minValue
                name: "Min Value"
                defaultValue: 0
                Binding {
                    target: gauge
                    property: "minValue"
                    value: minValue.value
                }
            }
            TextInputValue {
                Layout.row: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: maxValue
                name: "Max Value"
                defaultValue: 100
                Binding {
                    target: gauge
                    property: "maxValue"
                    value: maxValue.value
                }
            }
            TextInputValue {
                Layout.row: 3
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: minValueOffset
                name: "Min Value Offset"
                defaultValue: 0
                Binding {
                    target: gauge
                    property: "initialValueOffset"
                    value: minValueOffset.value
                }
            }
            TextInputValue {
                Layout.row: 4
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: minAngle
                name: "Min Angle"
                defaultValue: gauge.minAngle
                Binding {
                    target: gauge
                    property: "minAngle"
                    value: minAngle.value
                }
            }
            TextInputValue {
                Layout.row: 5
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: maxAngle
                name: "Max Angle"
                defaultValue: gauge.maxAngle
                Binding {
                    target: gauge
                    property: "maxAngle"
                    value: maxAngle.value
                }
            }
            TextInputValue {
                Layout.row: 6
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: highAlarm
                name: "High Alarm"
                defaultValue: gauge.highAlarm
                Binding {
                    target: gauge
                    property: "highAlarm"
                    value: highAlarm.value
                }
            }
            TextInputValue {
                Layout.row: 7
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: lowAlarm
                name: "Low Alarm"
                defaultValue: gauge.lowAlarm
                Binding {
                    target: gauge
                    property: "lowAlarm"
                    value: lowAlarm.value
                }
            }

            TextInputValue {
                Layout.row: 8
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: units
                name: "Main Units"
                defaultValue: gauge.units
                Binding {
                    target: gauge
                    property: "units"
                    value: units.text
                }
            }
            SliderValue {
                Layout.row: 9
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: needleLength
                name: "Needle Length"
                to: 2.0
                from: 0.05
                defaultValue: gauge.needleLength
                Binding {
                    target: gauge
                    property: "needleLength"
                    value: needleLength.value * gauge.height
                }
            }
            SliderValue {
                Layout.row: 10
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: needleOffset
                name: "Needle Offset"
                to: 2.0
                from: 0.05
                defaultValue: gauge.needleOffset
                Binding {
                    target: gauge
                    property: "needleOffset"
                    value: needleOffset.value * gauge.height
                }
            }
            SliderValue {
                Layout.row: 11
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: needleWidth
                name: "Needle width"
                to: 0.5
                from: 0.001
                defaultValue: gauge.needleWidth
                Binding {
                    target: gauge
                    property: "needleWidth"
                    value: needleWidth.value * gauge.height
                }
            }
            SliderValue {
                Layout.row: 12
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: needleCenterRadius
                name: "Needle Center Radius"
                to: 0.5
                from: 0.001
                defaultValue: gauge.needleCenterRadius
                Binding {
                    target: gauge
                    property: "needleCenterRadius"
                    value: needleCenterRadius.value
                }
            }
            SliderValue {
                Layout.row: 13
                Layout.fillHeight: true
                Layout.fillWidth: true
                to: 1.0
                from: 0.001
                id: textSize
                name: "Text Size Factor"
                defaultValue: gauge.textSize
                Binding {
                    target: gauge
                    property: "textSize"
                    value: textSize.value * gauge.height
                }
            }

            SliderValue {
                Layout.row: 14
                Layout.fillHeight: true
                Layout.fillWidth: true
                to: 1.0
                from: 0.001
                id: textOffset
                name: "Text Offset Factor"
                defaultValue: gauge.textOffset
                Binding {
                    target: gauge
                    property: "textOffset"
                    value: textOffset.value * gauge.height
                }
            }

            TextInputValue {
                Layout.row: 25
                Layout.fillHeight: true
                Layout.fillWidth: true
                id: gaugeSize
                name: "Size (W & H)"
                defaultValue: gauge.width
                Binding {
                    target: mainWindow
                    property: "width"
                    value: gaugeSize.value
                }
                Binding {
                    target: mainWindow
                    property: "height"
                    value: gaugeSize.value
                }
            }


        }
    }

    FileDialog {
        id: gaugeImageDialog
        title: "Please choose a gauge image file"
        folder: shortcuts.home
        nameFilters: ["Image files (*.png *.jpg)"]
        onAccepted: {
            currentGauge.imageResource = gaugeImageDialog.fileUrl
            loadImage.visible = false
            close();
        }
        onRejected: {
            console.log("Canceled")
            close();
        }
        Component.onCompleted: visible = false
    }

    Rectangle {
        id: overlay
        anchors.fill: parent

        Gauge {
            id: currentGauge
            anchors.fill: overlay
            height: 440
            width: 440
        }
    }

    Button {
        id: loadImage
        text: "Load Gauge Image"
        onClicked: {
            gaugeImageDialog.open()
        }
        anchors.centerIn: parent
    }
}
