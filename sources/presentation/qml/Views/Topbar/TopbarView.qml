import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Rectangle {
    id: root

    color: palette.raisedColor
    height: palette.controlBaseSize

    RowLayout {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        Controls.Button {
            id: menuButton
            tipText: qsTr("Menu")
            iconSource: "qrc:/icons/burger.svg"
            anchors.verticalCenter: parent.verticalCenter
            highlighted: menu.opened
            onClicked: menu.opened = !menu.opened
        }
    }
}
