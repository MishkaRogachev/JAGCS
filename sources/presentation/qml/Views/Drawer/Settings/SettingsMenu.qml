import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.DrawerMenu {
    menuModel: [
        { text: qsTr("Database"), icon: "qrc:/icons/db.svg",
            source: "qrc:/Views/Drawer/Settings/Database/DatabaseView.qml" },
        { text: qsTr("Map"), icon: "qrc:/icons/map.svg",
            source: "qrc:/Views/Drawer/Settings/Map/MapSettingsView.qml" },
        { text: qsTr("Video"), icon: "qrc:/icons/video.svg",
            source: "qrc:/Views/Drawer/Settings/Video/VideoSourceListView.qml" },
        { text: qsTr("Joystick"), icon: "qrc:/icons/joystick.svg",
            source: "qrc:/Views/Drawer/Settings/Joystick/JoystickSettingsView.qml" },
        { text: qsTr("GUI"), icon: "qrc:/icons/show.svg",
            source: "qrc:/Views/Drawer/Settings/Gui/GuiSettingsView.qml" },
        { text: qsTr("Networking"), icon: "qrc:/icons/connect.svg",
            source: "qrc:/Views/Drawer/Settings/Network/NetworkSettingsView.qml" }
    ]
}
