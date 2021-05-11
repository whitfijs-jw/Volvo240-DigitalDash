import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 1280
    height: 480

    SwipeView {
        id: swipeView
        anchors.fill: parent
        //currentIndex: tabBar.currentIndex

        MainCluster {
            id: mainCluster

            Timer {
                property real speed: 0.0
                property real rpm: 0.0
                property real coolantTemp: 100
                property real fuel: 0

                id: speedTimer
                interval: 100
                running: true
                repeat: true
                onTriggered: {
                    mainCluster.setSpeed(speed);
                    mainCluster.setRpm(rpm);
                    mainCluster.setCoolantTemp(coolantTemp);
                    mainCluster.setFuelLevel(fuel);
                    mainCluster.setSpeedoTopValue("", "");

                    if( speed > 125 ) { speed = 0 };
                    speed += 0.5;

                    if ( rpm > 7000 ) { rpm = 800 };
                    rpm += 10;

                    if ( coolantTemp > 250 ) { coolantTemp = 120 };
                    coolantTemp += 0.25;

                    if ( fuel > 100 ) { fuel = 0.0 };
                    fuel += 0.5;
                }
            }

            Timer {
                property bool swap: false

                id: blinkerTimer
                interval: 5000
                running: true
                repeat: true
                onTriggered: {
                    if( swap ) {
                        mainCluster.leftBlink(true);
                        mainCluster.rightBlink(false);
                        swap = false;
                    }else {
                        mainCluster.leftBlink(false);
                        mainCluster.rightBlink(true);
                        swap = true;
                    }
                }
            }
        }

        MainClusterCustom {
            id: accCluster

            Timer {
                property real boost: -30.0
                property real oilP: -1
                property real oilT: 110
                property real volts: 9.5

                interval: 100
                running: true;
                repeat: true;
                onTriggered: {
                    accCluster.setBoost(boost);
                    accCluster.setOilPressure(oilP);
                    accCluster.setOilTemperature(oilT);
                    accCluster.setVoltage(volts);

                    if (boost > 35 ) { boost = -30 }
                    boost += 0.25;

                    if (oilP > 5.0) { oilP = -1 }
                    oilP += 0.01;

                    if (oilT > 305.0) { oilT = 110 }
                    oilT += 0.1;

                    if(volts > 16.5) { volts = 9.5 }
                    volts += 0.01
                }
            }

            Timer {
                property real speed: 0.0
                property real rpm: 0.0
                property real coolantTemp: 100
                property real fuel: 0

                interval: 100
                running: true
                repeat: true
                onTriggered: {
                    accCluster.setSpeed(speed);
                    accCluster.setRpm(rpm);
                    accCluster.setCoolantTemp(coolantTemp);
                    accCluster.setFuelLevel(fuel);
                    accCluster.setSpeedoTopValue("", "");

                    if( speed > 125 ) { speed = 0 };
                    speed += 0.5;

                    if ( rpm > 7000 ) { rpm = 800 };
                    rpm += 10;

                    if ( coolantTemp > 250 ) { coolantTemp = 120 };
                    coolantTemp += 0.25;

                    if ( fuel > 100 ) { fuel = 0.0 };
                    fuel += 0.5;
                }
            }

        }
    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex
//        Rectangle {
//            anchors.fill: parent
//            color: "black"
//        }

//        TabButton {
//            text: qsTr("Main Cluster")
//        }
//        TabButton {
//            text: qsTr("Accessory Gauges")
//        }
//    }
}
