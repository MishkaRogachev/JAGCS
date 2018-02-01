import QtQuick 2.6

import "../Controls" as Controls

import "Tools"
import "Notifications"
import "Topbar"
import "Video"
import "Map"
import "Dashboard"
import "Menu"

Controls.ApplicationWindow  {
    id: main

    property bool fullscreen: false
    property bool cornerMap: false
    property bool cornerVisible: false
    property int mapType: -1

    property QtObject map

    function reloadMap(type) {
        mapType = type !== undefined ? type : parseInt(settings.value("Map/plugin"));
        mapLoader.sourceComponent = mapFactory.create(mapType);
    }

    Component.onCompleted: reloadMap()
    visible: true

    header: TopbarView {
        id: topbar
        anchors.left: dashboard.right
        anchors.right: parent.right
    }

    Item {
        id: substrate
        anchors.left: parent.left
        anchors.top: topbar.bottom
        width: menuDrawer.visible ? menuDrawer.x : parent.width
        anchors.bottom: parent.bottom
    }

    MouseArea {
        id: corner
        anchors.top: topbar.bottom
        anchors.right: substrate.right
        anchors.margins: sizings.margins
        width: Math.min(parent.width / 3, parent.height / 2)
        height: cornerMap ? map.implicitHeight : video.implicitHeight
        z: cornerVisible ? 2 : -1
        onClicked: cornerMap = !cornerMap
    }

    ActiveVideoView {
        id: video
        anchors.fill: cornerMap ? substrate : corner
        visible: cornerVisible || cornerMap
        z: !cornerMap
    }

    Loader {
        id: mapLoader
        anchors.fill: cornerMap ? corner : substrate
        visible: cornerVisible || !cornerMap
        onItemChanged: map = item
        z: cornerMap
    }

    MapFactory { id: mapFactory }

    DashboardView {
        id: dashboard
        anchors.top: topbar.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        z: 1
    }

    ToolsPanel {
        id: tools
        anchors.top: topbar.bottom
        anchors.right: substrate.right
        anchors.bottom: parent.bottom
        anchors.margins: sizings.margins
        z: 3
    }

    NotificationListView {
        id: notifications
        anchors.top: corner.bottom
        anchors.right: tools.left
        anchors.bottom: parent.bottom
        anchors.left: dashboard.right
        anchors.margins: sizings.margins
        z: 3
    }

    Controls.Drawer {
        id: menuDrawer
        y: topbar.height
        width: menu.width
        height: parent.height - y
        edge: Qt.RightEdge

        MenuView {
            id: menu
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            visible: menuDrawer.position > 0
        }

        Behavior on width { PropertyAnimation { duration: 200 } }
    }
}
