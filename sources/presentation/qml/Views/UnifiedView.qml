import QtQuick 2.6

import "qrc:/Controls" as Controls

import "Topbar"
import "Menu"

Rectangle {
    id: unified

    color: palette.backgroundColor

    TopbarView {
        id: topbar
        objectName: "topbar"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    MenuView {
        id: menu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.rightMargin: opened ? 0 : -width

        Behavior on anchors.rightMargin { PropertyAnimation { duration: 100 } }
    }

    Controls.Button {
        id: menuButton
        tipText: qsTr("Menu")
        iconSource: "qrc:/icons/burger.svg"
        anchors.top: parent.top
        anchors.right: parent.right
        highlighted: menu.opened
        onClicked: menu.opened = !menu.opened
    }
}
