import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property int buttonSpacing: 3
    property int buttonWidth: (parent.width - buttonSpacing*3) / 4.0
    property int buttonHeight: parent.height / 13.0

    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Row {
            spacing: 3
            width: parent.width
            height: buttonHeight + spacing * 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            layoutDirection: "LeftToRight";
            Button {
                id: leftButton
                text: "<"
                width: buttonWidth
                height: buttonHeight
                onPressed: {
                    rootWindow.advance(false);
                }
            }
            Button {
                id: middleLeftButton
                text: "1"
                width: buttonWidth
                height: buttonHeight
                onPressed: {
                    //rootWindow.advance(false);
                }
            }
            Button {
                id: middleRightButton
                text: "2"
                width: buttonWidth
                height: buttonHeight
                onPressed: {
                    //rootWindow.advance(false);
                }
            }
            Button {
                id: rightButton
                text: ">"
                width: buttonWidth
                height: buttonHeight
                onPressed: {
                    rootWindow.advance(true);
                }
            }
        }
    }
}
