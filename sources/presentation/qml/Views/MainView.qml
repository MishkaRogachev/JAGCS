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

        property color trackColor: "#F44336"
        property color missionColor: paletteStyle ? "#00897B" : "#1DE9B6"

        property color skyColor: paletteStyle ? "#80DEEF" : "#00BCD4"
        property color groundColor: paletteStyle ? "#A1887F" : "#795548"

        backgroundColor: paletteStyle ? "#CFD8DC" : "#37474F"
        sunkenColor: paletteStyle ? "#B0BEC5" : "#263238"
        raisedColor: paletteStyle ? "#ECEFF1" : "#455A64"
        buttonColor: paletteStyle ? "#F5F5F5" : "#546E7A"

        disabledColor: paletteStyle ? "#9E9E9E" : "#212121"

        textColor: paletteStyle ? "#37474F" : "#FAFAFA"
        selectedTextColor: "#242424"
    }

    header: StatusView {
        objectName: "status"
    }

    Loader {
        anchors.fill: parent
        sourceComponent: createModeView(mode)
        onItemChanged: if (item) item.objectName = mode
    }

    function createModeView(mode) {
        switch (mode) {
        case "flight": return Qt.createComponent("Flight/FlightView.qml");
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
