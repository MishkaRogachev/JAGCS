import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Drawer {
    id: drawer

    property int mode: DrawerPresenter.UnknownMode
    readonly property bool noMode: mode == DrawerPresenter.UnknownMode
    readonly property bool atHome: mode == DrawerPresenter.Home
    property var nestedModes: []
    property var parentModes: []

    property string submode
    property bool filterEnabled: false

    signal closeSubmode()
    signal filter(string text)

    function home() {
        presenter.home();
        if (!drawerContents.visible) open();
    }

    function setMode(mode) {
        presenter.setMode(mode);
        if (!drawerContents.visible) open();
    }

    onAboutToShow: if (noMode) presenter.home()
    onAboutToHide: presenter.setMode(DrawerPresenter.UnknownMode)

    width: drawerContents.width

    Behavior on width { PropertyAnimation { duration: 200 } }

    DrawerPresenter {
        id: presenter
        view: drawer
    }

    Item {
        id: drawerContents
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        visible: drawer.position > 0
        clip: true

        ColumnLayout {
            id: drawerHeader
            width: parent.width
            spacing: industrial.spacing

            RowLayout {
                spacing: industrial.spacing

                RowLayout {
                    spacing: 0

                    Controls.Button {
                        tipText: qsTr("Close drawer")
                        iconSource: "qrc:/icons/arrow_left.svg"
                        flat: true
                        onClicked: drawer.close()
                    }

                    Controls.Button {
                        tipText: qsTr("Home")
                        iconSource: "qrc:/icons/home.svg"
                        flat: true
                        enabled: !atHome
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
                    visible: !atHome
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
                Layout.margins: industrial.padding
            }
        }

        Loader {
            id: loader
            anchors.fill: parent
            anchors.margins: industrial.padding
            anchors.topMargin: drawerHeader.height + industrial.spacing
            clip: true
            source: {
                switch (mode) {
                case DrawerPresenter.Plan: return "Planning/PlanningView.qml";
                case DrawerPresenter.Fleet: return "Vehicles/VehicleListView.qml";
                case DrawerPresenter.Connection: return "Connection/ConnectionView.qml";
                case DrawerPresenter.Logs: return "Logs/LogListView.qml";
                case DrawerPresenter.Database: return "Settings/Database/DatabaseView.qml";
                case DrawerPresenter.Map: return "Settings/Map/MapSettingsView.qml";
                case DrawerPresenter.Video: return "Settings/Video/VideoSourceListView.qml";
                case DrawerPresenter.Joystick: return "Settings/Joystick/JoystickSettingsView.qml";
                case DrawerPresenter.Gui: return "Settings/Gui/GuiSettingsView.qml";
                case DrawerPresenter.Networking: return "Settings/Network/NetworkSettingsView.qml";
                case DrawerPresenter.About: return "About/AboutView.qml";
                case DrawerPresenter.Quit: return "Quit/QuitView.qml";
                case DrawerPresenter.Home:
                case DrawerPresenter.Settings:
                    return "DrawerMenu.qml";
                default:
                    return "";
                }
            }
            onItemChanged: {
                if (!item) return;

                drawerContents.width = Qt.binding(function() {
                    return item ? Math.max(industrial.baseSize * 8,
                                           item.implicitWidth + industrial.margins * 2) : 0;
                });
            }
        }
    }
}
