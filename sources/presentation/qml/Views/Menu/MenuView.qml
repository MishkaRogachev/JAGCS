import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

import "About"
import "Quit"

Controls.Frame {
    id: root

    function home() {
        menuLabel.text = "";
        loader.sourceComponent = topMenuComponent;
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

            Controls.Label {
                id: menuLabel
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
                width: parent.width
                onItemChanged: {
                    if (!item) return;

                    root.width = item.preferredWidth
                    root.requestPresenter(item.objectName)
                }

                Connections {
                    target: loader.item
                    ignoreUnknownSignals: true

                    onReqestComponent: {
                        menuLabel.text = text;
                        loader.sourceComponent = component;
                    }
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
                { text: qsTr("Settings"), menu: [
                        { text: qsTr("Database") },
                        { text: qsTr("Map") },
                        { text: qsTr("Joystick") },
                        { text: qsTr("GUI") },
                        { text: qsTr("Networking") }
                    ] },
                { text: qsTr("About"), component: aboutComponent },
                { text: qsTr("Quit"), component: quitComponent }
            ]
        }
    }

    Component { id: aboutComponent; AboutView { objectName: "about" } }
    Component { id: quitComponent; QuitView { objectName: "quit" } }
}
