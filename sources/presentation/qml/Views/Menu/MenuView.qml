import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

import "Settings/DataBase"
import "Settings/Map"
import "Settings/Gui"
import "Settings/Joystick"
import "Settings/Network"

import "About"
import "Quit"

Controls.Frame {
    id: root

    function home() {
        loader.sourceComponent = topMenuComponent;
        loader.path = [];
        menuLabel.path = [];

        updatePath();
    }

    function back() {
        if (loader.path.length < 1) return;

        loader.sourceComponent = loader.path.pop();
        menuLabel.path.pop();

        updatePath();
    }

    function deepIn(component, text) {
        loader.path.push(loader.sourceComponent);
        loader.sourceComponent = component;
        menuLabel.path.push(text);

        updatePath();
    }

    function updatePath() {
        menuLabel.text = menuLabel.path.join(", ");

        backButton.enabled = loader.path.length > 0;
        if (menuLabel.path.length > 1) {
            backButton.tipText = qsTr("Back to ") + menuLabel.path[menuLabel.path.length - 2];
        }
        else {
            backButton.tipText = qsTr("Back to home");
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

            Controls.Button {
                id: backButton
                iconSource: "qrc:/icons/left.svg"
                flat: true
                onClicked: back()
            }

            Controls.Label {
                id: menuLabel

                property var path: []

                Layout.fillWidth: true
            }
        }

        Flickable {
            contentHeight: loader.height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            Loader {
                id: loader

                property var path: []

                width: parent.width
                onItemChanged: {
                    if (!item) return;

                    root.width = item.preferredWidth
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
            property int preferredWidth: palette.controlBaseSize * 7

            menuModel: [
                { text: qsTr("Communications") },
                { text: qsTr("Vehicles") },
                { text: qsTr("Video") },
                { text: qsTr("Settings"), component: settingsMenuComponent },
                { text: qsTr("About"), component: aboutComponent },
                { text: qsTr("Quit"), component: quitComponent }
            ]
        }
    }

    Component {
        id: settingsMenuComponent

        Controls.SideNav {
            property int preferredWidth: palette.controlBaseSize * 7

            menuModel: [
                { text: qsTr("Database"), component: dbComponent },
                { text: qsTr("Map"), component: mapComponent  },
                { text: qsTr("Joystick"), component: joystickComponent  },
                { text: qsTr("GUI"), component: guiComponent  },
                { text: qsTr("Networking"), component: networkComponent  }
            ]
        }
    }

    Component { id: dbComponent; DataBaseView { objectName: "database" } }
    Component { id: mapComponent; MapSettingsView { objectName: "map" } }
    Component { id: joystickComponent; JoystickSettingsView { objectName: "joystick" } }
    Component { id: guiComponent; GuiSettingsView { objectName: "gui" } }
    Component { id: networkComponent; NetworkSettingsView { objectName: "network" } }

    Component { id: aboutComponent; AboutView { objectName: "about" } }
    Component { id: quitComponent; QuitView { objectName: "quit" } }
}
