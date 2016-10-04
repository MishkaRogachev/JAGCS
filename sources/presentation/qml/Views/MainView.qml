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

    property Palette palette: Palette {}

    header: StatusView {
        id: status
    }

    FlightView {
        id: flight
        anchors.fill: parent
    }

    SettingsView {
        id: settings
        anchors.fill: parent
        visible: false
    }
}
