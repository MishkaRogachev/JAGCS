import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

ColumnLayout {
    id: database

    property bool changed: false
    property string migration
    property bool connected: false
    property var log: []

    property alias path: pathField.text

    spacing: sizings.spacing

    DatabasePresenter {
        id: presenter
        view: database
        Component.onCompleted: {
            updatePath();
            updateLog();
            updateConnected();
        }
    }

    Info {
        message: changed ? qsTr("Application will be restarted") : ""
        Layout.fillWidth: true
        Layout.leftMargin: sizings.padding
        Layout.rightMargin: sizings.padding
    }

    RowLayout {
        spacing: sizings.spacing

        Controls.TextField {
            id: pathField
            labelText: qsTr("SQLite data base file")
            placeholderText: qsTr("Enter filepath")
            onEditingFinished: changed = true
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: changed
            onSave: presenter.savePath()
            onRestore: presenter.updatePath()
        }
    }

    Controls.Label {
        text: qsTr("Migration") + ": " + migration
    }

    Controls.Frame {
        Layout.fillWidth: true
        Layout.margins: sizings.padding
        Layout.fillHeight: true

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
        Layout.leftMargin: sizings.padding
        Layout.rightMargin: sizings.padding
    }

    RowLayout {
        spacing: sizings.spacing
        Layout.fillWidth: true
        Layout.leftMargin: sizings.padding
        Layout.rightMargin: sizings.padding

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
