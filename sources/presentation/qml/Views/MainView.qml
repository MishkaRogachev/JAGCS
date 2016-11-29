import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

import "../Controls"

import "Status"
import "Flight"
import "Settings"

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
        sourceComponent: {
            switch (mode) {
            case "flight": return flight;
            case "settings": return settings;
            }
        }
    }

    // TODO: Dynamic object creation
    // http://doc.qt.io/qt-5/qtqml-javascript-dynamicobjectcreation.html
    Component {
        id: flight

        FlightView {
            objectName: "flight"
            anchors.fill: parent
        }
    }

    Component {
        id: settings

        SettingsView {
            objectName: "settings"
            anchors.fill: parent
        }
    }
}
