import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

import "Communications"

import "Settings/Database"
import "Settings/Video"
import "Settings/Map"
import "Settings/Gui"
import "Settings/Joystick"
import "Settings/Network"

import "About"
import "Quit"

Controls.Pane {
    id: root

    function home() {
        loader.sourceComponent = topMenuComponent;
        currentLabel.text = "";
        pathModel.clear();
    }

    function deepIn(component, text) {
        loader.sourceComponent = component;
        pathModel.append({ "component": component, "text": text });
        currentLabel.text = text;
    }

    function backOut(index) {
        loader.sourceComponent = pathModel.get(index).component;
        currentLabel.text = pathModel.get(index).text;

        if (index + 1 < pathModel.count) {
            pathModel.remove(index + 1, pathModel.count - index - 1);
        }
    }

    signal requestPresenter(string view)

    padding: 0
    Component.onCompleted: home()

    ColumnLayout {
        anchors.fill: parent
        spacing: palette.spacing

        RowLayout {
            Controls.Button {
                tipText: qsTr("Home")
                iconSource: "qrc:/icons/home.svg"
                flat: true
                enabled: loader.sourceComponent !== topMenuComponent
                onClicked: home()
            }

            Repeater {
                model: ListModel { id: pathModel }

                Controls.Button {
                    text: model.text
                    flat: true
                    visible: index + 1 < pathModel.count
                    onClicked: backOut(index)
                }
            }

            Controls.Label {
                id: currentLabel
                font.bold: true
            }
        }

        Flickable {
            id: flickable
            contentHeight: loader.height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: palette.margins

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            Loader {
                id: loader
                width: parent.width
                onItemChanged: {
                    if (!item) return;

                    root.width = item.implicitWidth + palette.margins * 2
                    item.height = Qt.binding(function() {
                        return Math.max(item.implicitHeight, flickable.height);
                    } );
                    root.requestPresenter(item.objectName)
                }

                Connections {
                    target: loader.item
                    ignoreUnknownSignals: true

                    onReqestComponent: root.deepIn(component, text)
                }
            }
        }
    }

    Component {
        id: topMenuComponent

        Controls.SideNav {
            menuModel: [
                { text: qsTr("Communications"), component: commComponent },
                { text: qsTr("Vehicles") },
                { text: qsTr("Settings"), component: settingsMenuComponent },
                { text: qsTr("About"), component: aboutComponent },
                { text: qsTr("Quit"), component: quitComponent }
            ]
        }
    }

    Component {
        id: settingsMenuComponent

        Controls.SideNav {
            menuModel: [
                { text: qsTr("Database"), component: dbComponent },
                { text: qsTr("Map"), component: mapComponent },
                { text: qsTr("Video"), component: videoComponent },
                { text: qsTr("Joystick"), component: joystickComponent },
                { text: qsTr("GUI"), component: guiComponent },
                { text: qsTr("Networking"), component: networkComponent }
            ]
        }
    }

    Component { id: commComponent; CommunicationsView { objectName: "communications" } }

    Component { id: dbComponent; DatabaseView { objectName: "database" } }
    Component { id: mapComponent; MapSettingsView { objectName: "map" } }
    Component { id: videoComponent; VideoSettingsView { objectName: "video" } }
    Component { id: joystickComponent; JoystickSettingsView { objectName: "joystick" } }
    Component { id: guiComponent; GuiSettingsView { objectName: "gui" } }
    Component { id: networkComponent; NetworkSettingsView { objectName: "network" } }

    Component { id: aboutComponent; AboutView { objectName: "about" } }
    Component { id: quitComponent; QuitView { objectName: "quit" } }
}
