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
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -container.tachometerSize * 0.9

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
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: tachContainer.bottom
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
            anchors.left: speedoContainer.right
            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: -20
            anchors.leftMargin: 50
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
            anchors.left: tachContainer.right
            anchors.bottom: speedoContainer.top
            anchors.bottomMargin: 10
            anchors.leftMargin: -50
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
            anchors.left: boostContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
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
            anchors.verticalCenter: boostContainer.verticalCenter
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
            anchors.left: oilTContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            ListView {
                model: voltMeterModel
                delegate: voltMeterDelegate.component
            }
        }

        Rectangle {
            id: clockContainer
            anchors.left: voltContainer.right
            anchors.verticalCenter: boostContainer.verticalCenter
            height: container.smallGaugeSize
            width: container.smallGaugeSize
            color: "transparent"

            Clock {
                anchors.fill: parent
            }
        }
    }
}
