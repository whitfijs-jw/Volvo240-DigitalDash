import QtQuick 2.15

Item {
    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real tachometerSize: parent.height * 0.925
        property real smallGaugeSize: parent.height / 3
        property real speedometerSize: (tachometerSize - smallGaugeSize)
        property real tempFuelSize: (tachometerSize - smallGaugeSize)
        property real smallGaugeXOffset: parent.height * (50/480)

        Rectangle {
            TachometerDelegate {
                id: tachometerDelegate
            }

            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate
            }

            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.right: tachContainer.left
            anchors.top: boostContainer.bottom
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegate.component
            }

        }

        Rectangle {
            TempAndFuelDelegate240Style {
                id: tempFuelDelegate
            }

            id: tempFuelContainer
            width: container.tempFuelSize
            height: container.tempFuelSize
            anchors.left: tachContainer.right
            anchors.top: oilPContainer.bottom
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate.component
            }

        }


        Rectangle {
            AccessoryGaugeDelegate {
                id: boostDelegate
                imageSource: "qrc:/accCluster/boost_black_no_numbers.png"

                minAngle: -227
                maxAngle: 48

                needleLength: 0.525

                yOffset: 0.0
            }

            id: boostContainer
            anchors.right: tachContainer.left
            anchors.top: tachContainer.top

            anchors.leftMargin: -container.smallGaugeXOffset
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: boostModel
                delegate: boostDelegate.component
            }
        }
        Rectangle {
            AccessoryGaugeDelegate {
                id: oilPressureDelegate
                imageSource: "qrc:/accCluster/later-240-oil-pressure.png"
            }

            id: oilPContainer
            anchors.left: tachContainer.right
            anchors.top: tachContainer.top

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegate.component
            }
        }

        Rectangle {
            AccessoryGaugeDelegate {
                id: oilTempDelegate
                imageSource: "qrc:/accCluster/later-240-oil-temp.png"
            }

            id: oilTContainer
            anchors.left: oilPContainer.right
            anchors.top: tachContainer.top

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: oilTModel
                delegate: oilTempDelegate.component
            }
        }

        Rectangle {
            AccessoryGaugeDelegate {
                id: voltMeterDelegate
            }

            id: voltContainer
            anchors.right: boostContainer.left
            anchors.top: tachContainer.top

            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                id: gaugeVolt
                model: voltMeterModel
                delegate: voltMeterDelegate.component
            }
        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize
            anchors.top: tachContainer.top
            anchors.topMargin: blinkerTopMargin
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -blinkerSize * 4
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize
            anchors.top: tachContainer.top
            anchors.topMargin: blinkerTopMargin
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize * 4
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }
    }
}
