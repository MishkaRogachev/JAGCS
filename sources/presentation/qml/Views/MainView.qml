import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "../Controls"

import "Status"

ApplicationWindow {
    id: main

    property string mode

    minimumWidth: 1024
    minimumHeight: 768

    header: StatusView {
        objectName: "statusbar"
    }

    Loader {
        anchors.fill: parent
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

    function updateUiSettings() {
        visibility = settings.boolValue("Gui/fullscreen") ? "FullScreen" : "Windowed"
    }
}
