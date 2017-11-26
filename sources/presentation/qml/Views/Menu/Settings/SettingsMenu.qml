import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.SideNav {
    menuModel: [
        { text: qsTr("Database"), source: "Settings/Database/DatabaseView.qml" },
        { text: qsTr("Map"), source: "Settings/Map/MapSettingsView.qml" },
        { text: qsTr("Video"), source: "Settings/Video/VideoSourceListView.qml" },
        { text: qsTr("Joystick"), source: "Settings/Joystick/JoystickSettingsView.qml" },
        { text: qsTr("GUI"), source: "Settings/Gui/GuiSettingsView.qml" },
        { text: qsTr("Networking"), source: "Settings/Network/NetworkSettingsView.qml" }
    ]
}
