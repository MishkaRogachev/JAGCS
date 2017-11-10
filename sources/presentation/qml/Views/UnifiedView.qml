import QtQuick 2.6

import "../Controls" as Controls

import "Topbar"
import "Map"
import "Video"
import "Menu"

Rectangle {
    id: unified

    property bool cornerMap: false
    property bool cornerVisible: false
    property int cornerWidth: Math.min(width / 3, height / 3)

    color: palette.backgroundColor

    TopbarView {
        id: topbar
        objectName: "topbar"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
    }

    MapView {
        id: map
        objectName: "map"
        z: cornerMap
        anchors.bottom: parent.bottom
        anchors.right: cornerMap ? tools.left : parent.right
        anchors.margins: cornerMap ? palette.margins : 0
        width: cornerMap ? cornerWidth : parent.width
        height: cornerMap ? implicitHeight : parent.height
        visible: cornerMap && cornerVisible || !cornerMap

        Behavior on x { PropertyAnimation { duration: 100 } }
        Behavior on y { PropertyAnimation { duration: 100 } }
        Behavior on width { PropertyAnimation { duration: 100 } }
        Behavior on height { PropertyAnimation { duration: 100 } }
    }

    VideoSplitView {
        id: video
        objectName: "video"
        anchors.bottom: parent.bottom
        anchors.right: cornerMap ? parent.right : tools.left
        anchors.margins: cornerMap ? 0 : palette.margins
        width: cornerMap ? parent.width : cornerWidth
        height: cornerMap ? parent.height : implicitHeight
        visible: !cornerMap && cornerVisible || cornerMap

        Behavior on x { PropertyAnimation { duration: 100 } }
        Behavior on y { PropertyAnimation { duration: 100 } }
        Behavior on width { PropertyAnimation { duration: 100 } }
        Behavior on height { PropertyAnimation { duration: 100 } }
    }

    MapControl { // TODO: to ToolsPanel
        id: tools
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: palette.margins

        Controls.Button {
            tipText: cornerMap ? qsTr("Map") : qsTr("Video")
            iconSource: cornerMap ? "qrc:/icons/map-marker.svg" : "qrc:/icons/video.svg"
            onClicked: cornerMap = !cornerMap
        }

        Controls.Button {
            id: maxMinButton
            tipText: cornerVisible ? qsTr("Hide window") : qsTr("Show window")
            iconSource: cornerVisible ? "qrc:/icons/minimize.svg" : "qrc:/icons/maximize.svg"
            onClicked: cornerVisible = !cornerVisible
        }
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
            objectName: "menu"
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
