import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property alias source: sourceField.text
    property bool changed: false

    signal save()
    signal restore()
    signal remove()

    ColumnLayout {
        anchors.fill: parent
        spacing: palette.spacing

        RowLayout {

            Controls.Label {
                text: qsTr("Source:")
                Layout.fillWidth: true
            }

            Controls.TextField {
                id: sourceField
                placeholderText: qsTr("Enter source")
                onTextChanged: changed = true
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Controls.Button {
                text: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()
                enabled: changed
            }

            Controls.Button {
                text: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: changed
            }

            Controls.Button {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onClicked: remove()
                iconColor: palette.negativeColor
            }
        }
    }
}
