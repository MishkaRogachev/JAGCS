import QtQuick 2.6

import "../Controls" as Controls

import "Status"

Item {
    id: main

    property string mode

    anchors.fill: parent

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        objectName: "statusbar"
        z: 1000
    }

    Loader {
        anchors.fill: parent
        anchors.topMargin: status.height
        sourceComponent: createModeView(mode)
        onItemChanged: if (item) item.objectName = mode
    }

    function createModeView(mode) {
        switch (mode) {
        case "control": return Qt.createComponent("Control/ControlView.qml");
        case "planning": return Qt.createComponent("Planning/PlanningView.qml");
        case "settings": return Qt.createComponent("Settings/SettingsView.qml");
        }
    }
}
