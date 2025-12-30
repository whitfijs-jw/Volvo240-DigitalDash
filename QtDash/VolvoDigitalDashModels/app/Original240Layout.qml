import QtQuick 2.15

Item {  
    Rectangle {
        id: container
        width: parent.width
        height: parent.height
        color: "transparent"

        property real speedometerSize: parent.height * 0.925
        property real tachometerSize: parent.height / 1.2
        property real tempFuelSize: tachometerSize

        property bool speedoMph: speedoModel.units === "mph"

        Rectangle {
            TachometerDelegate {
                id: tachometerDelegate
            }

            id: tachContainer
            width: container.tachometerSize
            height: container.tachometerSize
            color: "transparent"
            anchors.right: speedoContainer.left
            anchors.verticalCenter: speedoContainer.verticalCenter
            /* Rpm: */
            ListView {
                model: rpmModel
                delegate: tachometerDelegate.component
            }

        }

        Rectangle {
            SpeedoDelegate {
                id: speedoDelegate

                initialValueOffset: container.speedoMph ? 5 : 20

                minAngle: container.speedoMph ? -238 : -254
                maxAngle: container.speedoMph ? 44 : 45

                imageSource: container.speedoMph ?
                                 "qrc:/mainCluster/later-240-speedo.png" :
                                 "qrc:/mainCluster/later-240-speedo-kph.png"

                gearIndicatorEnabled: true
            }

            id: speedoContainer
            width: container.speedometerSize
            height: container.speedometerSize
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
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
            color: "transparent"

            /* Rpm: */
            ListView {
                model: tempFuelModel
                delegate: tempFuelDelegate.component
            }

        }

        Rectangle {
            id: leftBlinker
            width: blinkerSize * 2
            anchors.top: speedoContainer.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -parent.width / 8
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
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: parent.width / 6
            color: "transparent"

            ListView {
                model: rightBlinkerModel
                delegate: rightBlinkerDelegate
            }
        }
    }
}
