import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "../../Controls" as Controls

Item {
    id: menu

    property int mode: DrawerPresenter.UnknownMode
    property var nestedModes: []
    property var parentModes: []

    property string submode
    property bool filterEnabled: false

    signal open()
    signal closeSubmode()
    signal filter(string text)

    function home() { presenter.home(); }
    function setMode(mode) { presenter.setMode(mode); }
    function close() { setMode(DrawerPresenter.UnknownMode) }

    onModeChanged: if (!menu.visible && mode != DrawerPresenter.UnknownMode) open()
    onVisibleChanged: if (mode == DrawerPresenter.UnknownMode) setMode(DrawerPresenter.Home)
    implicitWidth: sizings.controlBaseSize * 7

    DrawerPresenter {
        id: presenter
        view: menu
    }

    ColumnLayout {
        id: drawerHeader
        width: parent.width
        spacing: sizings.spacing

        RowLayout {
            spacing: sizings.spacing

            RowLayout {
                spacing: 0

                Controls.Button {
                    tipText: qsTr("Close drawer")
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
            }

            Repeater {
                model: parentModes

                Controls.Button {
                    text: presenter.modeString(modelData)
                    flat: true
                    visible: modelData != DrawerPresenter.Home
                    onClicked: setMode(modelData)
                }
            }

            Controls.Button {
                text: presenter.modeString(mode)
                flat: true
                visible: submode.length > 0
                onClicked: closeSubmode()
            }

            // TODO: ComboBox to select current submode without returning to root
            Controls.Label {
                text: submode.length > 0 ? submode : presenter.modeString(mode)
                font.bold: true
                Layout.fillWidth: true
            }

            Controls.Button {
                id: filterButton
                tipText: checked ? qsTr("Close filter") : qsTr("Open filter")
                iconSource: "qrc:/icons/find.svg"
                checkable: true
                visible: filterEnabled
                flat: true
                onVisibleChanged: if (!visible) checked = false
            }
        }

        Controls.FilterField {
            visible: filterButton.checked
            onVisibleChanged: visible ? forceActiveFocus() : clear()
            onTextChanged: filter(text)
            Layout.fillWidth: true
            Layout.margins: sizings.padding
        }
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        anchors.margins: sizings.padding
        anchors.topMargin: drawerHeader.height + sizings.spacing
        contentHeight: contents.height
        boundsBehavior: Flickable.OvershootBounds
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
                    case DrawerPresenter.Connection: return "Connection/ConnectionView.qml";
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
