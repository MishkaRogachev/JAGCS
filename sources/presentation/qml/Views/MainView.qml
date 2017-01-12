import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "../Controls"

import "Status"

ApplicationWindow {
    id: main
    visibility: "Maximized"
    minimumWidth: 1024
    minimumHeight: 768
    visible: true

    property string mode
    property alias uiSize: palette.controlBaseSize

    signal updateUiSize();

    Palette {
        id: palette
        property color trackColor: "#E74C3C"
        property color missionColor: "#00897B"
    }

    header: StatusView {
        objectName: "status"
    }

    Loader {
        anchors.fill: parent
        sourceComponent: creteModeView(mode)
        onItemChanged: if (item) item.objectName = mode
    }

    function creteModeView(mode) {
        switch (mode) {
        case "flight": return Qt.createComponent("Flight/FlightView.qml");
        case "mission": return Qt.createComponent("Mission/MissionView.qml");
        case "settings": return Qt.createComponent("Settings/SettingsView.qml");
        }
    }
}
