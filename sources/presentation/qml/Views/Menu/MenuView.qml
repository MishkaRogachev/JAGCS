import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    padding: 0

    // NOTE: function in model does not work properly
    // https://stackoverflow.com/questions/43175574/how-to-store-a-function-and-call-it-later-in-qml-javascript
    property var menuModel:[
        { text: qsTr("Data Base") },
        { text: qsTr("Communications") },
        { text: qsTr("Vehicles") },
        { text: qsTr("Video") },
        { text: qsTr("Map") },
        { text: qsTr("Joystick") },
        { text: qsTr("GUI") },
        { text: qsTr("Networking") },
        { text: qsTr("About"), func: function() { loader.source = "About/AboutView.qml" } },
        { text: qsTr("Quit"), func: function() { Qt.quit() } },
    ]

    RowLayout {
        anchors.fill: parent
        spacing: palette.spacing
        implicitWidth: loader.item ? 800 : flickable.width

        Loader {
            id: loader
            Layout.fillHeight: true
            Layout.fillWidth: true
            //Layout.preferredWidth: item ? item.implicitWidth : 0
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
                        model: menuModel

                        Controls.Button {
                            text: modelData.text ? modelData.text : ""
                            iconSource: modelData.icon ? modelData.icon : ""
                            onClicked: if (menuModel[index].func) menuModel[index].func()
                            Layout.preferredWidth: palette.controlBaseSize * 7
                            Layout.fillWidth: true
                        }
                    }

                    Item { Layout.fillHeight: true }
                }
            }
        }
    }
}
