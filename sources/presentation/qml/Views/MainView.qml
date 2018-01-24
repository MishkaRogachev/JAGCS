import QtQuick 2.6

import "../Controls" as Controls

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

    Item {
        id: corner
        anchors.top: topbar.bottom
        anchors.right: tools.left
        anchors.margins: sizings.margins
        width: Math.min(parent.width / 3, parent.height / 3)
        height: cornerMap ? map.implicitHeight : video.implicitHeight
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

    MapControl { // TODO: to ToolsPanel
        id: tools
        anchors.right: substrate.right
        anchors.bottom: parent.bottom
        anchors.margins: sizings.margins

        Controls.Button {
            id: tracking
            iconSource: "qrc:/icons/center.svg"
            tipText: qsTr("Center vehicle on map")
            checkable: true
            enabled: dashboard.selectedVehicle !== undefined && map.visible
            onEnabledChanged: if (!enabled) checked = false;
            onCheckedChanged: map.trackingVehicleId = checked ?
                                  dashboard.selectedVehicle.id : 0
        }

        Controls.Button {
            tipText: cornerMap ? qsTr("Map") : qsTr("Video")
            iconSource: cornerMap ? "qrc:/icons/map-marker.svg" : "qrc:/icons/video.svg"
            onClicked: cornerMap = !cornerMap
        }

        Controls.Button {
            id: maxMinButton
            tipText: cornerVisible ? qsTr("Hide window") : qsTr("Show window")
            iconSource: cornerVisible ? "qrc:/icons/window.svg" : "qrc:/icons/subwindow.svg"
            onClicked: cornerVisible = !cornerVisible
        }
    }

    NotificationPopup {
        id: notificator
        x: substrate.width - width - sizings.margins
        y: substrate.y + sizings.margins
        width: Math.min(implicitWidth, substrate.width - dashboard.width - sizings.margins * 2)
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
