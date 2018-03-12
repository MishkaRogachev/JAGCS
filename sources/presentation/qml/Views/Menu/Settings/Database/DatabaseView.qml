import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

GridLayout {
    id: database

    property bool changed: false
    property bool connected: false
    property var log: []

    property alias path: pathField.text
    property alias migration: migrationLabel.text

    columns: 2
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    DatabasePresenter {
        id: presenter
        view: database
        Component.onCompleted: {
            updatePath();
            updateLog();
            updateConnected();
        }
    }

    Controls.Label {
        text: qsTr("Data base:")
    }

    Controls.ComboBox {
        model: [ "SQLite" ]
        enabled: false // TODO: other data base providers
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("SQLite data base file:")
    }

    Controls.TextField {
        id: pathField
        placeholderText: qsTr("Enter filepath")
        onEditingFinished: changed = true
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Migration:")
    }

    Controls.Label {
        id: migrationLabel
        text: qsTr("Migration not specified")
    }

    Controls.Frame {
        backgroundColor: palette.sunkenColor
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.columnSpan: 2

        Flickable {
            anchors.fill: parent
            contentHeight: column.height
            flickableDirection: Flickable.VerticalFlick
            clip: true

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            ColumnLayout {
                id:column
                width: parent.width
                spacing: sizings.spacing

                Controls.Label {
                    text: qsTr("No records")
                    horizontalAlignment: Qt.AlignHCenter
                    visible: log.length == 0
                    Layout.fillWidth: true
                }

                Repeater {
                    model: log

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
        onClicked: presenter.clearLog()
        enabled: log.length > 0
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }

    SaveRestore {
        enabled: changed
        message: changed ? qsTr("Application will restart") : ""
        onSave: presenter.savePath()
        onRestore: presenter.updatePath()
        Layout.columnSpan: 2
    }

    RowLayout {
        Layout.columnSpan: 2

        Controls.Button {
            text: qsTr("Migrate")
            iconSource: "qrc:/icons/right.svg"
            onClicked: presenter.migrate()
            Layout.fillWidth: true
        }

        Controls.Button {
            text: connected ? qsTr("Reconnect") : qsTr("Connect")
            iconSource: "qrc:/icons/connect.svg"
            onClicked: presenter.tryConnect()
            enabled: !changed
            Layout.fillWidth: true
        }
    }
}
