import QtQuick 2.6

import "../Controls" as Controls

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

    Controls.Swipeable {
        id: menuSwipeable
        swipeToRight: true
        dragStartX: parent.width - widthOfSeizure
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: menu.width + widthOfSeizure

        MenuView {
            id: menu
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: menuSwipeable.widthOfSeizure
        }

        Behavior on x {
            enabled: !widthAnimation.running;
            PropertyAnimation { id: xAnimation; duration: 100; }
        }

        Behavior on width {
            enabled: !xAnimation.running;
            PropertyAnimation { id: widthAnimation; duration: 100 }
        }
    }

    Controls.Button {
        id: menuButton
        tipText: qsTr("Menu")
        iconSource: "qrc:/icons/burger.svg"
        anchors.top: parent.top
        anchors.right: parent.right
        highlighted: menuSwipeable.isOpened
        onClicked: menuSwipeable.isOpened ? menuSwipeable.close() : menuSwipeable.open()
    }
}
