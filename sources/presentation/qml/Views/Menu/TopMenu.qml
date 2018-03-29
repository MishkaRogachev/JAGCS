import QtQuick 2.6

import "../../Controls" as Controls

Controls.SideNav {
    menuModel: [
        { text: qsTr("Planning"), icon: "qrc:/icons/planning.svg",
            source: "qrc:/Views/Menu/Planning/PlanningView.qml" },
        { text: qsTr("Vehicles"), icon: "qrc:/icons/fleet.svg",
            source: "qrc:/Views/Menu/Vehicles/VehicleListView.qml" },
        { text: qsTr("Links"), icon: "qrc:/icons/connect.svg",
            source: "qrc:/Views/Menu/Links/LinkListView.qml" },
        { text: qsTr("Logbook"), icon: "qrc:/icons/logbook.svg",
            source: "qrc:/Views/Menu/Log/LogListView.qml" },
        { text: qsTr("Settings"), icon: "qrc:/icons/settings.svg",
            source: "qrc:/Views/Menu/Settings/SettingsMenu.qml" },
        { text: qsTr("About"), icon: "qrc:/icons/info.svg",
            source: "qrc:/Views/Menu/About/AboutView.qml" },
        { text: qsTr("Quit"), icon: "qrc:/icons/quit.svg",
            source: "qrc:/Views/Menu/Quit/QuitView.qml" }
    ]
}
