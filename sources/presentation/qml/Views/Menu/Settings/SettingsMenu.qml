import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.SideNav {
    menuModel: [
        { text: qsTr("Database"), source: "qrc:/Views/Menu/Settings/Database/DatabaseView.qml" },
        { text: qsTr("Map"), source: "qrc:/Views/Menu/Settings/Map/MapSettingsView.qml" },
        { text: qsTr("Video"), source: "qrc:/Views/Menu/Settings/Video/VideoSourceListView.qml" },
        { text: qsTr("Joystick"), source: "qrc:/Views/Menu/Settings/Joystick/JoystickSettingsView.qml" },
        { text: qsTr("GUI"), source: "qrc:/Views/Menu/Settings/Gui/GuiSettingsView.qml" },
        { text: qsTr("Networking"), source: "qrc:/Views/Menu/Settings/Network/NetworkSettingsView.qml" }
    ]
}
