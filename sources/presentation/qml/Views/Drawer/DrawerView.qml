import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "../../Controls" as Controls

ColumnLayout {
    id: menu

    property int mode: DrawerPresenter.UnknownMode
    property var nestedModes: []
    property var parentModes: []

    signal open()

    function home() { presenter.home(); }
    function setMode(mode) { presenter.setMode(mode); }

    onModeChanged: if (!menu.visible) open()
    spacing: sizings.spacing
    width: Math.max(loader.item ? Math.min(loader.implicitWidth + sizings.margins * 2,
                                           main.width / 2) : 0, sizings.controlBaseSize * 7)

    DrawerPresenter {
        id: presenter
        view: menu
    }

    RowLayout {
        Layout.maximumWidth: parent.width
        spacing: 0

        Controls.Button {
            tipText: qsTr("Close menu")
            iconSource: "qrc:/icons/left.svg"
            flat: true
            onClicked: drawer.close()
        }

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: mode != DrawerPresenter.Home
            onClicked: home()
        }

        Repeater {
            model: parentModes

            Controls.Button {
                text: presenter.modeString(modelData)
                flat: true
                visible: index + 1 < parentModes.count
                onClicked: setMode(modelData)
            }
        }

        Controls.Label {
            text: presenter.modeString(mode)
            font.bold: true
            Layout.fillWidth: true
        }
    }

    Flickable {
        id: flickable
        contentHeight: contents.height
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: sizings.margins

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        DrawerMenu {
            id: contents
            menuModel: nestedModes
            Layout.fillWidth: true

            Loader {
                id: loader
                Layout.fillWidth: true
                Layout.fillHeight: true
                source: {
                    switch (mode) {
                    case DrawerPresenter.Planning: return "Planning/PlanningView.qml";
                    case DrawerPresenter.Vehicles: return "Vehicles/VehicleListView.qml";
                    case DrawerPresenter.Links: return "Links/LinkListView.qml";
                    case DrawerPresenter.Logbook: return "Logbook/LogListView.qml";
                    case DrawerPresenter.Database: return "Settings/Database/DatabaseView.qml";
                    case DrawerPresenter.Map: return "Settings/Map/MapSettingsView.qml";
                    case DrawerPresenter.Video: return "Settings/Video/VideoSourceListView.qml";
                    case DrawerPresenter.Joystick: return "Settings/Joystick/JoystickSettingsView.qml";
                    case DrawerPresenter.Gui: return "Settings/Gui/GuiSettingsView.qml";
                    case DrawerPresenter.Networking: return "Settings/Network/NetworkSettingsView.qml";
                    case DrawerPresenter.About: return "About/AboutView.qml";
                    case DrawerPresenter.Quit: return "Quit/QuitView.qml";
                    default: return "";
                    }
                }
            }
        }
    }
}
