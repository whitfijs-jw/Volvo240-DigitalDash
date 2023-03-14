import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property int buttonWidth: parent.width / 5.0

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Row {
            spacing: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter
            layoutDirection: "LeftToRight";
            Button {
                id: leftButton
                text: "<"
                width: buttonWidth
                onPressed: {
                    rootWindow.advance(false);
                }
            }
            Button {
                id: middleLeftButton
                text: "1"
                width: buttonWidth
                onPressed: {
                    //rootWindow.advance(false);
                }
            }
            Button {
                id: middleRightButton
                text: "2"
                width: buttonWidth
                onPressed: {
                    //rootWindow.advance(false);
                }
            }
            Button {
                id: rightButton
                text: ">"
                width: buttonWidth
                onPressed: {
                    rootWindow.advance(true);
                }
            }
        }
    }
}
