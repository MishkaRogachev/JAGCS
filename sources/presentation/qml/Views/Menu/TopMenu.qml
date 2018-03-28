import QtQuick 2.6

import "../../Controls" as Controls

Controls.SideNav {
    menuModel: [
        { text: qsTr("Planning"), source: "qrc:/Views/Menu/Planning/PlanningView.qml" },
        { text: qsTr("Vehicles"), source: "qrc:/Views/Menu/Vehicles/VehicleListView.qml" },
        { text: qsTr("Links"), source: "qrc:/Views/Menu/Links/LinkListView.qml" },
        { text: qsTr("Logbook"), source: "qrc:/Views/Menu/Log/LogListView.qml" },
        { text: qsTr("Settings"), source: "qrc:/Views/Menu/Settings/SettingsMenu.qml" },
        { text: qsTr("About"), source: "qrc:/Views/Menu/About/AboutView.qml" },
        { text: qsTr("Quit"), source: "qrc:/Views/Menu/Quit/QuitView.qml" }
    ]
}
