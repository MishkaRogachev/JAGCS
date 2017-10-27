import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../Map"
import "../Video"
import "Command"

Controls.Pane {
    id: root

    property QtObject commander

    property bool cornerMap: false
    property bool cornerVisible: false

    property alias vehicles: vehiclesBox.model
    property alias selectedVehicle: vehiclesBox.currentIndex

    signal selectVehicle(int index)

    padding: 0

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: palette.margins
        spacing: palette.spacing
        width: Math.max(palette.controlBaseSize * 8, height / 2)

        RowLayout {
            Layout.alignment: Qt.AlignTop

            Controls.Button {
                iconSource: "qrc:/icons/center.svg"
                checkable: true
                enabled: dashboard.online
                onEnabledChanged: if (!enabled) checked = false
                onCheckedChanged: map.trackingVehicle = checked
            }

            Controls.ComboBox {
                id: vehiclesBox
                onCurrentIndexChanged: selectVehicle(currentIndex)
                Layout.fillWidth: true
            }

            Controls.Button {
                id: commandButton
                iconSource: "qrc:/icons/command.svg"
                checkable: true
                enabled: dashboard.online
                onEnabledChanged: if (!enabled) checked = false
                onCheckedChanged: commandList.visible = checked
            }
        }

        DashboardView {
            id: dashboard
            objectName: "dashboard"
        }
    }

    CommandListView {
        id: commandList
        anchors.top: parent.top
        anchors.left: background.left
        anchors.margins: palette.margins
        visible: commandButton.checked
        z: 10
    }

    Item {
        id: background
        anchors.left: column.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
    }

    Item {
        id: corner
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: palette.margins
        width: cornerVisible ? background.width / 3 : 0
        height: cornerVisible ? cornerMap ? map.implicitHeight : video.implicitHeight : 0
    }

    MapView {
        id: map
        objectName: "map"
        anchors.fill: cornerMap ? corner : background
        z: cornerMap
    }

    VideoSplitView {
        id: video
        objectName: "video"
        anchors.fill: cornerMap ? background : corner
    }

    MapControl {
        id: control
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: palette.margins

        Controls.Button {
            onClicked: cornerMap = !cornerMap
            iconSource: cornerMap ? "qrc:/icons/map-marker.svg" : "qrc:/icons/video.svg"
        }

        Controls.Button {
            id: maxMinButton
            onClicked: cornerVisible = !cornerVisible
            iconSource: cornerVisible ? "qrc:/icons/minimize.svg" : "qrc:/icons/maximize.svg"
        }
    }
}
