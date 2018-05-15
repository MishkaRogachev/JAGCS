import QtQuick 2.6

DrawerMenu {
    menuModel: [
        { text: qsTr("Planning"), icon: "qrc:/icons/planning.svg", action: function() { goPlanning() } },
        { text: qsTr("Vehicles"), icon: "qrc:/icons/fleet.svg", action: function() { goVehicles() } },
        { text: qsTr("Links"), icon: "qrc:/icons/connect.svg", action: function() { goLinks() } },
        { text: qsTr("Logbook"), icon: "qrc:/icons/logbook.svg", action: function() { goLogbook() } },
        { text: qsTr("Settings"), icon: "qrc:/icons/settings.svg", action: function() { goSettings() } },
        { text: qsTr("About"), icon: "qrc:/icons/info.svg", action: function() { goAbout() } },
        { text: qsTr("Quit"), icon: "qrc:/icons/quit.svg", action: function() { goQuit() } }
    ]
}
