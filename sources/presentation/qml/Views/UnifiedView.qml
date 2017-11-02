import QtQuick 2.6

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
        property bool opened: false
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.right
        anchors.leftMargin: opened ? -width : 0
        Behavior on anchors.leftMargin { PropertyAnimation { duration: 200 } }
    }
}
