import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool changed: false

    signal save()
    signal restore()

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 3

        Controls.Label {
            text: qsTr("Map type")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            enabled: false
            model: [ "QtLocation" ] // TODO: map types
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
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
            onClicked: {
                save();
                main.updateUiSettings();
            }
            enabled: changed
            Layout.fillWidth: true
        }
    }
}

