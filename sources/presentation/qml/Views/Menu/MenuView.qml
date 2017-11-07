import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "About"
import "Quit"

Controls.Frame {
    id: root

    property bool opened: false

    function home() {
        menuLabel.text = "";
        loader.sourceComponent = topMenuComponent;
    }

    padding: 0
    Component.onCompleted: home()

    ColumnLayout {
        anchors.fill: parent
        spacing: palette.spacing

        RowLayout {
            opacity: opened ? 1 : 0

            Behavior on opacity { PropertyAnimation { duration: 100 } }

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

        Loader {
            id: loader
            Layout.fillWidth: true
            Layout.fillHeight: true

            onItemChanged:  if (item) root.width = item.preferredWidth

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

    Component {
        id: topMenuComponent

        Controls.SideNav {
            property int preferredWidth: palette.controlBaseSize * 7

            menuModel: [
                { text: qsTr("Data Base") },
                { text: qsTr("Communications") },
                { text: qsTr("Vehicles") },
                { text: qsTr("Video") },
                { text: qsTr("Settings"), menu: [
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
