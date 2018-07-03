import QtQuick 2.6
import "../Controls" as Controls

import "Topbar"
import "Video"
import "Map"
import "Dashboard"
import "Tools"
import "VerticalProfile"
import "Drawer"

Controls.ApplicationWindow  {
    id: main

    property bool fullscreen: false
    property bool cornerMap: false
    property bool cornerVisible: false
    property bool plotVisible: false
    property bool plotAvailable: false
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
        anchors.left: parent.left
        anchors.right: parent.right

        Controls.RoundButton {
            id: burger
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: y
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Open drawer")
            onPressed: drawer.open()
        }
    }

    Item {
        id: substrate
        anchors.top: topbar.bottom
        anchors.left: parent.left
        anchors.leftMargin: drawer.position > 0 ? drawer.x + drawer.width : 0
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    MouseArea {
        id: corner
        anchors.bottom: plotVisible ? plot.top : parent.bottom
        anchors.left: tools.right
        anchors.margins: sizings.margins
        width: Math.max(0, Math.min(substrate.height / 2, substrate.width -
                                    (dashboard.dashboardVisible ? dashboard.width : 0) -
                                    tools.width - sizings.margins * 3))
        height: cornerMap ? width : video.implicitHeight
        z: cornerVisible ? 2 : -1
        enabled: cornerVisible
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
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        z: 1
    }

    ToolsPanel {
        id: tools
        x: drawer.position * drawer.width + sizings.margins
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        anchors.margins: sizings.margins
        z: 3
    }

    VerticalProfileView {
        id: plot
        visible: plotVisible
        height: substrate.height / 3
        anchors.right: dashboard.dashboardVisible &&
                       dashboard.implicitHeight < substrate.height - height ?
                           substrate.right : dashboard.left
        anchors.left: tools.right
        anchors.bottom: parent.bottom
        anchors.margins: sizings.margins
    }

    DrawerView {
        id: drawer
        height: parent.height
        interactive: !topbar.burgerHovered // NOTE: QTBUG-59141
    }

    MouseArea { // NOTE: drawer workaround
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: sizings.controlBaseSize * 0.5
        drag.target: highlight
        drag.axis: Drag.XAxis
        drag.minimumX: -highlight.width / 2
        drag.maximumX: 0
        onReleased: highlight.x = drag.minimumX

        Rectangle {
            id: highlight
            x: -width / 2
            width: sizings.controlBaseSize
            height: parent.height
            color: customPalette.highlightColor
            opacity: parent.pressed ? 0.33 : 0.0
            onXChanged: if (x == 0) drawer.open()

            Behavior on opacity { PropertyAnimation { duration: 100 } }
        }
    }
}
