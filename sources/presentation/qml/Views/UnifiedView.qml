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
        anchors.right: parent.right
        anchors.rightMargin: opened ? 0 : -width

        Behavior on anchors.rightMargin { PropertyAnimation { duration: 100 } }
        Behavior on width { PropertyAnimation { duration: 100 } }
    }
}
