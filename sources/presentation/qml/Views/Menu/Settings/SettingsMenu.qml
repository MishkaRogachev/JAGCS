import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.SideNav {
    menuModel: [
        { text: qsTr("Database"), icon: "qrc:/icons/db.svg",
            source: "qrc:/Views/Menu/Settings/Database/DatabaseView.qml" },
        { text: qsTr("Map"), icon: "qrc:/icons/map.svg",
            source: "qrc:/Views/Menu/Settings/Map/MapSettingsView.qml" },
        { text: qsTr("Video"), icon: "qrc:/icons/video.svg",
            source: "qrc:/Views/Menu/Settings/Video/VideoSourceListView.qml" },
        { text: qsTr("Joystick"), icon: "qrc:/icons/joystick.svg",
            source: "qrc:/Views/Menu/Settings/Joystick/JoystickSettingsView.qml" },
        { text: qsTr("GUI"), icon: "qrc:/icons/show.svg",
            source: "qrc:/Views/Menu/Settings/Gui/GuiSettingsView.qml" },
        { text: qsTr("Networking"), icon: "qrc:/icons/connect.svg",
            source: "qrc:/Views/Menu/Settings/Network/NetworkSettingsView.qml" }
    ]
}
