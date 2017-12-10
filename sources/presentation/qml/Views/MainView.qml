import QtQuick 2.6

import "../Controls" as Controls

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

    property Component mapComponent

    property QtObject map
    property QtObject video

    function reloadMap(type) {
        mapType = type !== undefined ? type : parseInt(settings.value("Map/plugin"));
        mapComponent = mapFactory.create(mapType);
    }

    visible: true
    Component.onCompleted: reloadMap()

    ListModel { id: contextModel }

    header: TopbarView {
        id: topbar
    }

    Loader {
        id: substrate
        anchors.left: parent.left
        anchors.top: topbar.bottom
        width: menuDrawer.visible ? menuDrawer.x : parent.width
        anchors.bottom: parent.bottom
        sourceComponent: cornerMap ? videoComponent : mapComponent
        onItemChanged: if (item) cornerMap ? video = item : map = item;
    }

    DashboardView {
        id: dashboard
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }

    MapControl { // TODO: to ToolsPanel
        id: tools
        anchors.right: substrate.right
        anchors.bottom: parent.bottom
        anchors.margins: sizings.margins

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

    Loader {
        id: corner
        anchors.bottom: parent.bottom
        anchors.right: tools.left
        anchors.margins: sizings.margins
        width: Math.min(parent.width / 3, parent.height / 3)
        sourceComponent: cornerMap ? mapComponent : videoComponent
        visible: cornerVisible
        onItemChanged: if (item) cornerMap ? map = item : video = item;
        z: 1
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

    MapFactory { id: mapFactory }
    Component { id: videoComponent; ActiveVideoView { id: video } }
}
