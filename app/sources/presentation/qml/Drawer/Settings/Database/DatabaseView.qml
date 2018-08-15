import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Common"

ColumnLayout {
    id: database

    property bool changed: false
    property var migrations: []

    property alias path: pathField.text

    spacing: sizings.spacing

    DatabasePresenter {
        id: presenter
        view: database
        Component.onCompleted: {
            updatePath();
            updateMigrations();
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

    RowLayout {
        spacing: sizings.spacing

        Controls.Label {
            text: qsTr("Migrations")
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/refresh.svg"
            tipText: qsTr("Update migrations")
            flat: true
            onClicked: presenter.updateMigrations()
        }
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
                    text: qsTr("No migrations")
                    horizontalAlignment: Qt.AlignHCenter
                    visible: migrations.length == 0
                    Layout.fillWidth: true
                }

                Repeater {
                    model: migrations

                    Controls.Label {
                        text: modelData
                        wrapMode: Text.WordWrap
                        font.pixelSize: sizings.secondaryFontSize
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
