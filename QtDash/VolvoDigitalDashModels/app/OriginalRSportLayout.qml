import QtQuick 2.15

Item {

    Rectangle {
        width: 1280
        height: 480
        color: "transparent"


        Rectangle {
            id: speedoContainer
            width: speedoSize
            height: speedoSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: speedoSize / 2
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -speedoSize / 10
            anchors.topMargin: 0
            color: "transparent"

            /* Rpm: */
            ListView {
                model: speedoModel
                delegate: speedoDelegateRSport
            }
        }


        Rectangle {
            id: tachContainer
            width: tachSize
            height: tachSize
            color: "transparent"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: - tachSize / 2
            anchors.verticalCenter: speedoContainer.verticalCenter

            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: rpmDelegateRSport
            }

        }

        Rectangle {
            anchors.right: tachContainer.left
            anchors.rightMargin: -smallGaugeSize * .15

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: smallGaugeSize * 0.45

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            Rectangle {
                id: coolantTempContainer
                color: "transparent"

                ListView {
                    model: coolantTempModel
                    delegate: coolantDelegateRSport
                }
            }

            Image {
                anchors.fill: parent
                source: "qrc:/gauge-faces-r-sport/r_sport_coolant_fahrenheit_shroud.png"
                cache: true
            }
        }

        Rectangle {
            anchors.left: speedoContainer.right
            anchors.leftMargin: -smallGaugeSize * 0.15

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: smallGaugeSize * 0.45


            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"


            Rectangle {
                id: fuelLevelContainer

                anchors.fill: parent
                color: "transparent"

                ListView {
                    model: fuelLevelModel
                    delegate: fuelLevelDelegateRSport
                }
            }

            Image {
                anchors.fill: parent
                source: "qrc:/gauge-faces-r-sport/r_sport_fuel_shroud.png"
                cache: true
            }
        }

        Rectangle {
            id: oilPContainer

            anchors.left: speedoContainer.right
            anchors.leftMargin: smallGaugeSize * 0.25

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: -smallGaugeSize * 0.5

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                model: oilPModel
                delegate: oilPressureDelegateRSport
            }
        }

        Rectangle {
            id: voltContainer
            anchors.right: tachContainer.left
            anchors.rightMargin: smallGaugeSize * 0.25

            anchors.verticalCenter: speedoContainer.verticalCenter
            anchors.verticalCenterOffset: -smallGaugeSize * 0.5

            height: smallGaugeSize
            width: smallGaugeSize
            color: "transparent"

            ListView {
                id: gaugeVolt
                model: voltMeterModel
                delegate: voltMeterDelegateRSport
            }
        }


        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -10
            color: "transparent"

            ListView {
                model: leftBlinkerModel
                delegate: leftBlinkerDelegate
            }
        }

        Rectangle {
            id: rightBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: blinkerSize+10
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }


    }
}
