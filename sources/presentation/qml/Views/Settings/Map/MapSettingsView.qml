import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool changed: false

    property string cacheFolder

    signal save()
    signal restore()

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 2

        Controls.Label {
            text: qsTr("Map type")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            enabled: false
            model: [ "QtLocation" ] // TODO: map types
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Cache folder")
            Layout.fillWidth: true
        }

        Controls.TextField {
            text: cacheFolder
            placeholderText: qsTr("Enter map cache folder")
            Layout.fillWidth: true
            onTextChanged: {
                cacheFolder = text;
                changed = true;
            }
        }

        Item {
            Layout.fillHeight: true
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
            onClicked: save();
            enabled: changed
            Layout.fillWidth: true
        }
    }
}

