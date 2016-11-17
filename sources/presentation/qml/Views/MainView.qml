import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "qrc:/Martial"

import "Status"
import "Flight"
import "Settings"

ApplicationWindow {
    id: main
    visibility: "Maximized"
    visible: true

    // TODO: modes(e.g Flight, Misson, Settings)
    property Palette palette: Palette {
        property color trackColor: "#E74C3C"
    }

    header: StatusView {
        objectName: "status"
    }

    FlightView {
        objectName: "flight"
        anchors.fill: parent
    }

    SettingsView {
        objectName: "settings"
        anchors.fill: parent
        visible: false
    }
}
