import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: accWindow
    property int smallGaugeSize: if (width > height) {
                                     width / 2.4
                                 } else {
                                     height / 2.4
                                 }

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04
    property string currentStyle: "240"

    property bool coolantTempF: coolantTempModel.units === "F"
    property bool oilTempF: oilTModel.units === "F"

    onCurrentStyleChanged: {
        currentLayout.update();
    }

    property var currentModel: {
        switch(currentStyle) {
        case "240":
            return available240Gauges;
        case "740":
            return available740Gauges;
        case "p1800":
            return availableP1800Gauges;
        case "rSport":
            return availableRSportGauges;
        case "140rallye":
            return available140RallyeGauges;
        default:
            return available240Gauges;
        }
    }

    Item {
        //rotate all elements
        rotation: if (RASPBERRY_PI) {
                      90
                  } else {
                      0
                  }
        anchors.fill: parent
        focus: false

        Rectangle {
            id: container
            width: if (RASPBERRY_PI) {
                       parent.height
                   } else {
                       parent.width
                   }
            height: if (RASPBERRY_PI) {
                        parent.width
                    } else {
                        parent.height
                    }
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Loader {
                id: currentLayout
                width: container.width
                height: container.height - 50
                source: "qrc:/SideAccessoryLayout.qml"
                asynchronous: true
                visible: true
            }

            Loader {
                id: controlLayout
                anchors.fill: parent
                source: "qrc:/SideAccessoryScreenControl.qml"
                asynchronous: true
            }
         }
    }

    // 740 gauges
    property real needleLength_740: 0.75
    property real needleWidth_740: 0.05;
    property real needleOffset_740: 0.125
    property real gaugeYOffset_740: 1.0 / 4.5
    property real needleCenterRadius_740: 0.25

    property list<Item> delegates740: [
        AccessoryGaugeDelegate {
            imageSource: "qrc:/gauge-faces-740-940/740_boost.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            minAngle: -228
            maxAngle: 45

            needleWidth: needleWidth_740
            needleLength: 0.55
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: 0.0
        },
        AccessoryGaugeDelegate {
            minAngle: -115
            maxAngle: -65

            imageSource: "qrc:/gauge-faces-740-940/740_coolant_temp.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            needleWidth: needleWidth_740
            needleLength: needleLength_740
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: gaugeYOffset_740
        },
        AccessoryGaugeDelegate {
            minAngle: -115
            maxAngle: -65

            imageSource: "qrc:/gauge-faces-740-940/740_fuel.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            needleWidth: needleWidth_740
            needleLength: needleLength_740
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: gaugeYOffset_740
        },
        AccessoryGaugeDelegate {
            minAngle: -125
            maxAngle: -55

            imageSource: "qrc:/gauge-faces-740-940/740_oil_temperature.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            needleWidth: needleWidth_740
            needleLength: needleLength_740
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: gaugeYOffset_740
        },
        AccessoryGaugeDelegate {
            minAngle: -125
            maxAngle: -55

            imageSource: "qrc:/gauge-faces-740-940/740_oil_pressure.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            needleWidth: needleWidth_740
            needleLength: needleLength_740
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: gaugeYOffset_740
        },
        AccessoryGaugeDelegate {
            minAngle: -130
            maxAngle: -55

            imageSource: "qrc:/gauge-faces-740-940/740_voltmeter.png"
            needleResource: "qrc:/needles/needle-740-940.png"

            needleWidth: needleWidth_740
            needleLength: needleLength_740
            needleOffset: needleOffset_740
            needleCenterRadius: needleCenterRadius_740
            yOffset: gaugeYOffset_740
        }
    ]

    ListModel {
        id: available740Gauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "coolant temp"
        }
        ListElement {
            name: "fuel level"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "voltmeter"
        }
    }
    // 240 gauges
    property list<Item> delegates240: [
        AccessoryGaugeDelegate {
            imageSource: "qrc:/accCluster/boost_black_no_numbers.png"

            minAngle: -227
            maxAngle: 48

            needleLength: 0.525

            yOffset: 0.0
        },
        AccessoryGaugeDelegate {
            imageSource: oilTempF ?
                             "qrc:/accCluster/later-240-oil-temp.png" :
                             "qrc:/accCluster/later-240-oil-temp-c.png"
        },
        AccessoryGaugeDelegate {
            imageSource: "qrc:/accCluster/later-240-oil-pressure.png"
        },
        AccessoryGaugeDelegate {
        },
        ClockDelegate240Style {
        }
    ]

    ListModel {
        id: available240Gauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "voltmeter"
        }
        ListElement {
            name: "clock"
        }
    }

    property real p1800NeedleOffset: 0.0
    property real p1800NeedleLength: 0.375
    property real p1800NeedleCenterRadius: 0.0
    property real p1800YOffset: 0.0

    property list<Item> delegatesP1800: [
        AccessoryGaugeDelegate {
            gaugeMin: -20
            gaugeMax: 20

            minAngle: -145
            maxAngle: -35

            imageSource: "qrc:/gauge-faces-p1800/boost-p1800.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            needleLength: p1800NeedleLength
            needleOffset: p1800NeedleOffset
            needleCenterRadius: p1800NeedleCenterRadius

            yOffset: p1800YOffset
        },
        AccessoryGaugeDelegate {
            minAngle: -155
            maxAngle: -25

            imageSource: "qrc:/gauge-faces-p1800/oil-temp-p1800.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            needleLength: p1800NeedleLength
            needleOffset: p1800NeedleOffset
            needleCenterRadius: p1800NeedleCenterRadius

            yOffset: p1800YOffset
        },
        AccessoryGaugeDelegate {
            minAngle: -145
            maxAngle: -35

            imageSource: "qrc:/gauge-faces-p1800/oil-pressure-p1800.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            needleLength: p1800NeedleLength
            needleOffset: p1800NeedleOffset
            needleCenterRadius: p1800NeedleCenterRadius

            yOffset: p1800YOffset
        },
        AccessoryGaugeDelegate {
            minAngle: -145
            maxAngle: -35

            imageSource: "qrc:/gauge-faces-p1800/fuel-level-p1800.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            needleLength: p1800NeedleLength
            needleOffset: p1800NeedleOffset
            needleCenterRadius: p1800NeedleCenterRadius

            yOffset: p1800YOffset

            significatDigits: 0
        },
        ClockDelegateP1800Style {}
    ]

    ListModel {
        id: availableP1800Gauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "fuel level"
        }
        ListElement {
            name: "clock"
        }
    }

    property real rSportNeedleLength: 0.65
    property real rSportNeedleWidth: 0.035;
    property real rSportNeedleOffset: 0.125
    property real rSportGaugeXOffset: -1.0 / 4.65
    property real rSportNeedleCenterRadius: 0.15

    property list<Item> delegatesRSport: [
        AccessoryGaugeDelegate {
            gaugeMin: -20
            gaugeMax: 20

            minAngle: -48
            maxAngle: 48

            imageSource: "qrc:/gauge-faces-r-sport/r_sport_boost.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            clockwise: false

            needleWidth: rSportNeedleWidth
            needleLength: rSportNeedleLength
            needleOffset: rSportNeedleOffset
            xOffset: rSportGaugeXOffset
            yOffset: 0
            needleCenterRadius: rSportNeedleCenterRadius
        },
        AccessoryGaugeDelegate {
            minAngle: -48
            maxAngle: 48

            imageSource: "qrc:/gauge-faces-r-sport/r_sport_oil_temp_F.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            clockwise: false

            needleWidth: rSportNeedleWidth
            needleLength: rSportNeedleLength
            needleOffset: rSportNeedleOffset
            xOffset: rSportGaugeXOffset
            yOffset: 0
            needleCenterRadius: rSportNeedleCenterRadius
        },
        AccessoryGaugeDelegate {
            minAngle: -48
            maxAngle: 48

            imageSource: "qrc:/gauge-faces-r-sport/r_sport_oil_pressure_5bar.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            clockwise: false

            needleWidth: rSportNeedleWidth
            needleLength: rSportNeedleLength
            needleOffset: rSportNeedleOffset
            xOffset: rSportGaugeXOffset
            yOffset: 0
            needleCenterRadius: rSportNeedleCenterRadius
        },
        AccessoryGaugeDelegate {
            gaugeMin: 100
            gaugeMax: 260

            minAngle: -48
            maxAngle: 48

            imageSource: "qrc:/gauge-faces-r-sport/r_sport_acc_coolant_fahrenhet.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            clockwise: false

            needleWidth: rSportNeedleWidth
            needleLength: rSportNeedleLength
            needleOffset: rSportNeedleOffset
            xOffset: rSportGaugeXOffset
            yOffset: 0
            needleCenterRadius: rSportNeedleCenterRadius
        },
        AccessoryGaugeDelegate {
            gaugeMin: 8

            minAngle: -48
            maxAngle: 48

            imageSource: "qrc:/gauge-faces-r-sport/r_sport_voltmeter.png"
            needleResource: "qrc:/needles/needle-rsport.png"

            clockwise: false

            needleWidth: rSportNeedleWidth
            needleLength: rSportNeedleLength
            needleOffset: rSportNeedleOffset
            xOffset: rSportGaugeXOffset
            yOffset: 0
            needleCenterRadius: rSportNeedleCenterRadius
        }
    ]

    ListModel {
        id: availableRSportGauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "coolant temp"
        }
        ListElement {
            name: "voltmeter"
        }
    }

    // 140 Rallye gauges
   property list<Item> delegates140Rallye: [
        Accessory140RallyeStyle {
            id: boostDelegate140RallyeStyle
            gaugeMin: -20
            gaugeMax: 30
            minAngle: -240
            maxAngle: 60
            yOffset: 0
            needleLength: 0.55

            significatDigits: 1

            imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-boost_no_num.png"
        },
        Accessory140RallyeStyle {
            id: oilTempDelegate140RallyeStyle
            gaugeMin: 120
            gaugeMax: 300
            significatDigits: 1

            imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-oil-temp.png"
        },
        Accessory140RallyeStyle {
            id: oilPressureDelegate140RallyeStyle
            gaugeMin: 0
            gaugeMax: 8
            significatDigits: 2

            imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-oil-pressure-bar.png"
        },
        Accessory140RallyeStyle {
            id: coolantTempDelegate140RallyeStyle
            significatDigits: 1

            imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-coolant.png"
        },

        Accessory140RallyeStyle {
            id: voltmeterDelegate140RallyeStyle
            gaugeMin: 10
            gaugeMax: 18
            significatDigits: 2

            imageSource: "qrc:/gauge-faces-140-rallye/140-rallye-voltmeter.png"
        }
    ]

    ListModel {
        id: available140RallyeGauges
        ListElement {
            name: "boost"
        }
        ListElement {
            name: "oil temp"
        }
        ListElement {
            name: "oil pressure"
        }
        ListElement {
            name: "coolant temp"
        }
        ListElement {
            name: "voltmeter"
        }
    }
}

