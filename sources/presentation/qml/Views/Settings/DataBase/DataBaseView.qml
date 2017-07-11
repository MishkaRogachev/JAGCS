import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool changed: false
    property bool connected: false
    property var log: []

    property alias path: pathField.text
    property alias migration: migrationLabel.text

    signal clearLog()
    signal save()
    signal restore()
    signal migrate()
    signal tryConnect()

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: palette.spacing
        columnSpacing: palette.spacing

        Controls.Label {
            text: qsTr("Data base provider:")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            model: [ "SQLite" ]
            enabled: false // TODO: data base providers
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("SQLite data base file:")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: pathField
            placeholderText: qsTr("Enter filepath")
            onEditingFinished: changed = true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Migration:")
            Layout.fillWidth: true
        }

        Controls.Label {
            id: migrationLabel
            Layout.fillWidth: true
        }

        Controls.Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2

            Flickable {
                id: flick
                anchors.fill: parent
                contentHeight: journalColumn.height
                clip: true
                ScrollBar.vertical: ScrollBar {}

                ColumnLayout {
                    id: journalColumn
                    width: parent.width

                    Repeater {
                        model: log
                        onModelChanged: flick.contentY = flick.contentHeight - flick.height

                        Controls.Label {
                            text: modelData
                            horizontalAlignment: Qt.AlignHCenter
                            wrapMode: Text.WordWrap
                            Layout.fillWidth: true
                        }
                    }
                }
            }
        }

        Controls.Button {
            text: qsTr("Clear DB log")
            iconSource: "qrc:/icons/remove.svg"
            onClicked: clearLog()
            enabled: log.length > 0
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: save()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Migrate")
            iconSource: "qrc:/icons/right.svg"
            onClicked: migrate()
            Layout.fillWidth: true
        }

        Controls.Button {
            text: connected ? qsTr("Reconnect") : qsTr("Connect")
            iconSource: "qrc:/icons/connect.svg"
            onClicked: tryConnect()
            enabled: !changed
            Layout.fillWidth: true
        }
    }
}
