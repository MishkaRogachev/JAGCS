import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "About"

Controls.Frame {
    id: root

    padding: 0

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

                ColumnLayout {
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
                            onClicked: {
                                if (modelData.comp) {
                                    loader.sourceComponent = highlighted ? null : modelData.comp;
                                }
                                if (modelData.menu) {
                                    repeater.model = modelData.menu;
                                }
                            }
                            highlighted: loader.sourceComponent === modelData.comp
                            Layout.preferredWidth: palette.controlBaseSize * 7
                            Layout.fillWidth: true
                        }
                    }

                    Item { Layout.fillHeight: true }

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
