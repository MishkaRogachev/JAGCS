import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "../Controls"

import "Status"

ApplicationWindow {
    id: main
    visibility: "Maximized"
    visible: true

    property string mode

    Palette {
        id: palette
        property color trackColor: "#E74C3C"
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
        case "settings": return Qt.createComponent("Settings/SettingsView.qml");
        }
    }
}
