import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool opened: false

    implicitWidth: palette.controlBaseSize * 7
    padding: 0

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
                onClicked: {
                    menuLabel.text = "";
                    loader.sourceComponent = topMenuComponent;
                }
            }

            Controls.Label {
                id: menuLabel
                Layout.fillWidth: true
            }
        }

        Loader {
            id: loader
            Layout.fillWidth: true
            sourceComponent: topMenuComponent
        }

        Item { Layout.fillHeight: true }
    }

    Component {
        id: topMenuComponent

        TopMenu {
            onReqestComponent: {
                menuLabel.text = text;
                loader.sourceComponent = component;
            }
        }
    }
}

    /*
    // NOTE: function in model does not work properly
    // https://stackoverflow.com/questions/43175574/how-to-store-a-function-and-call-it-later-in-qml-javascript
    property var menuModel: [
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
        { text: qsTr("About"), comp: aboutComponent }
    ]

    Component {
        id: aboutComponent

        AboutView { objectName: "about" }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Loader {
            id: loader
            Layout.fillHeight: true
            Layout.preferredWidth: item ? unified.width - flickable.width - palette.spacing : 0

            Behavior on Layout.preferredWidth { PropertyAnimation { duration: 100 } }
        }

        Flickable {
            id: flickable
            implicitWidth: content.width
            contentHeight: content.height
            clip: true
            Layout.fillHeight: true

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            Item {
                id: content
                width: column.width
                height: Math.max(root.height, column.implicitHeight)

                ColumnLayout { // TODO: to common menu
                    id: column
                    anchors.centerIn: parent
                    height: parent.height
                    spacing: palette.spacing

                    Repeater {
                        id: repeater
                        model: menuModel

                        Controls.Button {
                            text: modelData.text ? modelData.text : ""
                            iconSource: modelData.icon ? modelData.icon : ""
                            iconColor: modelData.iconColor ? modelData.iconColor : iconColor
                            highlighted: loader.sourceComponent === modelData.comp
                            Layout.preferredWidth: palette.controlBaseSize * 7
                            Layout.fillWidth: true
                            onClicked: {
                                if (modelData.comp) {
                                    loader.sourceComponent = highlighted ? null : modelData.comp;
                                }
                                if (modelData.menu) {
                                    repeater.model = modelData.menu;
                                }
                            }
                            Component.onDestruction: {
                                if (modelData.comp && highlighted) loader.sourceComponent = null;
                            }
                        }
                    }

                    Item { Layout.fillHeight: true }

                    Controls.Button {
                        text: qsTr("Back")
                        iconSource: "qrc:/icons/left.svg"
                        onClicked: repeater.model = menuModel
                        visible: repeater.model !== menuModel
                        Layout.fillWidth: true
                    }

                    Controls.Button {
                        text: qsTr("Exit")
                        iconSource: "qrc:/icons/quit.svg"
                        iconColor: palette.dangerColor
                        onClicked: Qt.quit()
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
*/
