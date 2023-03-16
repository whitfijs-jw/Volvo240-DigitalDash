import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: rootWindow
    objectName: "rootWindow"
    visible: true
    width: 1280
    height: 480

    title: qsTr("Lolvo")

    SideAccessoryScreen {
        id: accessoryScreen
        objectName: "accessoryScreen"
        currentLayoutSource: "qrc:/SideAccessoryLayout240Style.qml"
    }

    property int smallGaugeSize: 140
    property int tachSize: 400
    property int speedoSize: 440
    property int tempFuelSize: 400
    property int blinkerSize: 50;
    property int linearSpeedoWidth: 1100
    property int linearSpeedoHeight: 65

    property int warningLightHeight: 50;
    property int warningLightWidth: 70;
    property int warningLightWideWidth: 100;
    property int warningLightVerticalMargin: 5;
    property int warningLightHorizontalMargin: 8

    property int speedoMax: 120;

    property int smallGaugeNeedleWidth240: smallGaugeSize * 0.04

    property var msg: [
        "You thought this\nwas going to work?",
        "Come back later...",
        "Just crush this\nthing already",
        "Can this thing\neven hit 60?",
        "Have fun with your\nM cam",
        "I bet you could get\n$500 on BaT for this",
        "404 Not Found",
        "I heard you like\nFWD Volvos",
        "How many neutrals\ndoes your trans have?",
        "Is a rear main seal\nsupposed to leak\nthat much?",
        "MOTOBOTO!",
        "Highway speeds\nmight not be\nan option for you",
    ]

    function setSmallGaugeSize(size) {
        smallGaugeSize = size;
    }

    function setTachSize(size) {
        tachSize = size;
    }

    function setSpeedoSize(size) {
        speedoSize = size;
    }

    function setTempFuelSize(size) {
        tempFuelSize = size;
    }

    function setSpeedoMax(max) {
        speedoMax = max;
    }

    function boundedAngle(angle, min, max) {
        if (angle > max) {
            angle = max;
        } else if (angle < min) {
            angle = min;
        }

        return angle;
    }

    function advance(forward) {
        gaugeItem.advanceScreen(forward);
    }

    OdometerDelegate {
        id: odometerDelegate
    }

    // 240 style delegates
    BoostDelegate240Style {
        id: boostDelegate
    }

    OilPressureDelegate240Style {
        id: oilPressureDelegate
    }

    OilTempereatureDelegate240Style {
        id: oilTemperatureDelegate
    }

    VoltmeterDelegate240Style {
        id: voltMeterDelegate
    }

    ClockDelegate240Style {
        id: clockDelegate
    }

    TachometerDelegate240Style {
        id: rpmDelegate
    }

    SpeedoDelegate240Style {
        id: speedoDelegate
    }

    TempAndFuelDelegate240Style {
        id: tempFuelDelegate
    }

    // 740 style delegates
    BoostDelegate740Style {
        id: boostDelegate740
    }

    TachometerDelegate740Style {
        id: rpmDelegate740
    }

    SpeedoDelegate740Style {
        id: speedoDelegate740
    }

    CoolantTempDelegate740Style {
        id: coolant740Delegate
    }

    FuelLevelDelegate740Style {
        id: fuelLevel740Delegate
    }

    VoltmeterDelegate740Style {
        id: voltMeterDelegate740
    }

    // 850 style delegates
    BoostDelegate850Style {
        id: boostDelegate850
    }

    CoolantTempDelegate850Style {
        id: coolantDelegate850
    }

    FuelLevelDelegate850Style {
        id: fuelLevelDelegate850
    }

    // rsport style delegates
    FuelLevelDelegateRSportStyle {
        id: fuelLevelDelegateRSport
    }

    CoolantTempDelegateRSportStyle {
        id: coolantDelegateRSport
    }

    OilPressureDelegateRSportStyle {
        id: oilPressureDelegateRSport
    }

    VoltmeterDelegateRSportStyle {
        id: voltMeterDelegateRSport
    }

    SpeedoDelegateRSportStyle {
        id: speedoDelegateRSport
    }

    TachoDelegateRSportStyle {
        id: rpmDelegateRSport
    }

    // 544 style delegates
    SpeedoDelegate544Style {
        id: speedoDelegate544
    }

    TachoDelegate544Style {
        id: rpmDelegate544
    }

    VoltmeterDelegate544Style {
        id: voltMeterDelegate544
    }

    FuelLevelDelegate544Style {
        id: fuelLevelDelegate544
    }

    CoolantTempDelegate544Style {
        id: coolantTempDelegate544
    }

    OilPressureDelegate544Style {
        id: oilPressureDelegate544
    }

    // p1800 style delegates
    SpeedoDelegateP1800Style {
        id: speedoDelegateP1800
    }

    TachoDelegateP1800Style {
        id: rpmDelegateP1800
    }

    CoolantTempDelegateP1800Style {
        id: coolantTempDelegateP1800
    }

    OilTempDelegateP1800Style {
        id: oilTempDelegateP1800
    }

    OilPressureDelegateP1800Style {
        id: oilPressureDelegateP1800
    }

    FuelLevelDelegateP1800Style {
        id: fuelLevelDelegateP1800
    }

    Component {
        id: leftBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = false
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Component {
        id: rightBlinkerDelegate

        Loader {
            source: "qrc:/Blinker.qml"
            asynchronous: true
            onLoaded: {
                item.flipped = true
                item.width = blinkerSize
                item.height = 3 * blinkerSize / 4
            }

            Binding {
                target: item
                property: "on"
                value: indicatorOn
            }

            Binding {
                target: item
                property: "width"
                value: blinkerSize
            }

            Binding {
                target: item
                property: "height"
                value: 3 * blinkerSize / 4
            }
        }
    }

    Component {
        id: parkingBrakeLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWideWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: brakeFailureLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWideWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: bulbFailureLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
                item.imageSource = "qrc:/warningLights/Bulb_failure_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: shiftUpLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: highBeamLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "lightcyan"
                item.width = warningLightWidth
                item.imageSource = "qrc:/warningLights/high_beam_icon.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: srsWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: oilWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
                item.imageSource = "qrc:warningLights/oil_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: batteryWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
                item.imageSource = "qrc:warningLights/battery_charge_icon_no_background.png"
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: absWarningLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "red"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: checkEngineLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Component {
        id: serviceLightDelegate

        Loader {
            source: "qrc:/WarningLight.qml"
            asynchronous: true
            onLoaded: {
                item.warningText = warningLightText
                item.lightColor = "orange"
                item.width = warningLightWidth
            }

            Binding {
                target: item
                property: "on"
                value: warningLightOn
            }
        }
    }

    Item {
        id: loading
        anchors.fill: parent
        rotation: if (RASPBERRY_PI) {
                      180
                  } else {
                      0
                  }
        Rectangle {
            anchors.fill: parent
            color: "black"

            Text {
                id: loadText
                text: qsTr(rootWindow.msg[Math.floor(Math.random() * rootWindow.msg.length)])
                horizontalAlignment: Text.AlignHCenter
                fontSizeMode: Text.Fit
                font.pixelSize: 100
                color: "white"
                onVisibleChanged: {
                    console.count("hidden");
                    var index = Math.floor(Math.random() * rootWindow.msg.length);
                    var txt = qsTr(rootWindow.msg[index]);
                    if (loadText.text === txt) {
                        if (++index > rootWindow.msg.length) {
                            index = 0
                        }

                        loadText.text = qsTr(rootWindow.msg[index]);
                    } else {
                        loadText.text = txt;
                    }
                }
                anchors.centerIn: parent
            }
        }
    }

    Item {
        id: gaugeItem
        anchors.fill: parent
        //focus: true
        rotation: if (RASPBERRY_PI) {
                      180
                  } else {
                      0
                  }
        property bool initialLoad: true
        antialiasing: true
        smooth: true
        property int screen: 0

        Loader {
            id: currentGauge
            anchors.fill: parent
            source: "qrc:/Original240Layout.qml"
            asynchronous: true
            visible: false
            onStatusChanged: {
                if (status == Loader.Ready) {
                    console.log("Loader Ready")
                    if (!gaugeItem.initialLoad) {
                        visible = true;
                        loadText.visible = false;
                    } else {
                        bootTimer.start();
                        gaugeItem.initialLoad = false
                    }
                } else if (status == Loader.Loading) {
                    currentGauge.visible = false;
                    loadText.visible = true;
                    console.log("Loader Loading")
                }
            }
        }

        Timer {
            id: bootTimer
            interval: 2000
            running: false
            repeat: false
            onTriggered: {
                currentGauge.visible = true;
                loadText.visible = false;
            }
        }

        function advanceScreen(forward) {
            if (forward) {
                if (++screen > 8) {
                    screen = 0;
                }
            } else {
                if (--screen < 0) {
                    screen = 8;
                }
            }

            switch (screen) {
                case 0:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/BigTachCenter.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setSpeedoMax(120);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                case 1:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/BigTachLeft.qml";
                    setSmallGaugeSize(140);
                    setTachSize(440);
                    setSpeedoSize(tachSize - smallGaugeSize - 10);
                    setSpeedoMax(120);
                    setTempFuelSize(tachSize - smallGaugeSize - 10);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                case 2:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original240Layout.qml";
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                case 3:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original740Layout.qml"
                    setSmallGaugeSize(140);
                    setTachSize(275);
                    setSpeedoSize(350);
                    setSpeedoMax(140);
                    setTempFuelSize(300);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout740Style.qml";
                    break;
                case 4:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original240LayoutClock.qml";
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                case 5:
                    //currentGauge.source = "";
                    currentGauge.source = "qrc:/Original850R.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(440);
                    setSpeedoMax(140);
                    //setTempFuelSize(300);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout740Style.qml";
                    break;
                case 6:
                    currentGauge.source = "qrc:/OriginalRSportLayout.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(350);
                    setSpeedoMax(130);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;

                case 7:
                    currentGauge.source = "qrc:/Original544Layout.qml"
                    setSmallGaugeSize(140);
                    setTachSize(400);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    setTempFuelSize(400);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                case 8:
                    currentGauge.source = "qrc:/OriginalP1800Layout.qml"
                    setSmallGaugeSize(200);
                    setTachSize(350);
                    setSpeedoSize(440);
                    setSpeedoMax(120);
                    accessoryScreen.currentLayoutSource = "qrc:/SideAccessoryLayout240Style.qml";
                    break;
                default:
                    break;
                }
        }

        Keys.onPressed: {
            if (!event.isAutoRepeat) {
                switch (event.key) {
                case Qt.Key_Left:
                    advanceScreen(false);
                    break;
                case Qt.Key_Right:
                    advanceScreen(true);
                    break;
                }

                event.accepted = true;
            }
        }

        Loader {
            source: "WarningLightBar.qml"
            asynchronous: true
        }
    }
}
