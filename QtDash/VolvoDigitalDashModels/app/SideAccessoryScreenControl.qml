import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Rectangle {
        anchors.fill: parent
        color: "transparent"

        Row {
            height: buttonHeight
            spacing: 2
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: leftButton
                text: "Left"
                focusPolicy: Qt.NoFocus
                onPressed: {
                    rootWindow.advance(false);
                }
            }
            Button {
                id: rightButton
                text: "Right"
                focusPolicy: Qt.NoFocus
                onPressed: {
                    rootWindow.advance(true);
                }
            }
        }
    }
}
