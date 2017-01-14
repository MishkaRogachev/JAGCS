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
    property int paletteStyle: 0

    signal updateUiSettings();

    Palette {
        id: palette

        property color trackColor: "#F44336"
        property color missionColor: paletteStyle ? "#1DE9B6" : "#00897B"

        backgroundColor: paletteStyle ? "#37474F" : "#CFD8DC"
        sunkenColor: paletteStyle ? "#263238" : "#B0BEC5"
        raisedColor: paletteStyle ? "#455A64" : "#ECEFF1"
        buttonColor: paletteStyle ? "#546E7A" : "#F5F5F5"

        disabledColor: paletteStyle ? "#212121" : "#BDBDBD"

        textColor: paletteStyle ? "#FAFAFA" : "#37474F"
        selectedTextColor: "#424242"

        highlightColor: "#00E676"
        selectionColor: "#69F0AE"

        negativeColor: "#F44336"
        neutralColor: "#FFC107"
        positiveColor: "#4CAF50"
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
