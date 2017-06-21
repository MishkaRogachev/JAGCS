import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "../Controls"

import "Status"

ApplicationWindow {
    id: main

    property string mode

    property alias uiSize: palette.controlBaseSize
    property int paletteStyle: 0

    minimumWidth: 1024
    minimumHeight: 768
    visibility: "Hidden"

    Palette {
        id: palette

        property color trackColor: "#a51834"
        property color missionColor: "#1ce9a5"

        property color skyColor: paletteStyle ? "#64adf6" : "#00d4ff"
        property color groundColor: paletteStyle ? "#86c34a" : "#7b4837"

        backgroundColor: paletteStyle ? "#ced1da" : "#30393d"
        sunkenColor: paletteStyle ? "#c3c6ce" : "#262e31"
        raisedColor: paletteStyle ? "#e1e5ee" : "#384348"
        buttonColor: paletteStyle ? "#f6f5f0" : "#54646b"

        disabledColor: paletteStyle ? "#9E9E9E" : "#212121"

        textColor: paletteStyle ? "#30393d" : "#f6f5f0"
        selectedTextColor: "#070707"

        highlightColor: "#1effb4"
        selectionColor: "#1ce9a5"

        negativeColor: "#e53535"
        neutralColor: "#ff9800"
        positiveColor: "#86c34a"
    }

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
        case "mission": return Qt.createComponent("Mission/MissionView.qml");
        case "settings": return Qt.createComponent("Settings/SettingsView.qml");
        }
    }

    function updateUiSettings() {
        visibility = settings.boolValue("Gui/fullscreen") ? "FullScreen" : "Windowed"
        uiSize = settings.value("Gui/uiSize");
        paletteStyle = settings.value("Gui/paletteStyle");
    }
}
