import QtQuick 2.6

import "../../Controls" as Controls

Controls.DrawerMenu {
    menuModel: [
        { text: qsTr("Planning"), icon: "qrc:/icons/planning.svg",
            source: "qrc:/Views/Drawer/Planning/PlanningView.qml" },
        { text: qsTr("Vehicles"), icon: "qrc:/icons/fleet.svg",
            source: "qrc:/Views/Drawer/Vehicles/VehicleListView.qml" },
        { text: qsTr("Links"), icon: "qrc:/icons/connect.svg",
            source: "qrc:/Views/Drawer/Links/LinkListView.qml" },
        { text: qsTr("Logbook"), icon: "qrc:/icons/logbook.svg",
            source: "qrc:/Views/Drawer/Log/LogListView.qml" },
        { text: qsTr("Settings"), icon: "qrc:/icons/settings.svg",
            source: "qrc:/Views/Drawer/Settings/SettingsMenu.qml" },
        { text: qsTr("About"), icon: "qrc:/icons/info.svg",
            source: "qrc:/Views/Drawer/About/AboutView.qml" },
        { text: qsTr("Quit"), icon: "qrc:/icons/quit.svg",
            source: "qrc:/Views/Drawer/Quit/QuitView.qml" }
    ]
}
