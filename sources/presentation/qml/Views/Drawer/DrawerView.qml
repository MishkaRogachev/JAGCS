import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "../../Controls" as Controls

Item {
    id: menu

    property int mode: DrawerPresenter.UnknownMode
    property var nestedModes: []
    property var parentModes: []

    signal open()

    function home() { presenter.home(); }
    function setMode(mode) { presenter.setMode(mode); }
    function close() { setMode(DrawerPresenter.UnknownMode) }

    onModeChanged: if (!menu.visible && mode != DrawerPresenter.UnknownMode) open()
    implicitWidth: sizings.controlBaseSize * 7

    DrawerPresenter {
        id: presenter
        view: menu
    }

    RowLayout {
        id: drawerHeader
        anchors.top: parent.top
        width: parent.width
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
                //visible: index < parentModes.count
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
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - sizings.padding * 2
        height: parent.height - drawerHeader.height - sizings.spacing
        contentHeight: contents.height
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        DrawerMenu {
            id: contents
            menuModel: nestedModes
            width: parent.width
            height: Math.max(contents.implicitHeight, flickable.height - sizings.margins);

            Loader {
                id: loader
                Layout.fillWidth: true
                Layout.fillHeight: true
                source: {
                    switch (mode) {
                    case DrawerPresenter.Planning: return "Planning/PlanningView.qml";
                    case DrawerPresenter.Vehicles: return "Vehicles/VehicleListView.qml";
                    case DrawerPresenter.Links: return "Links/LinkListView.qml";
                    case DrawerPresenter.Logbook: return "Log/LogListView.qml";
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
                onItemChanged: menu.width = item ? item.implicitWidth + sizings.margins * 2 :
                                                   menu.implicitWidth
            }
        }
    }
}
