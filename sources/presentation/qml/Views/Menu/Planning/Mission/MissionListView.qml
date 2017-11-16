import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Repeater {
    id: root

    property var visibilities: []

    signal setVisible(int id, bool visible)
    signal restore(int id)
    signal save(int id)
    signal remove(int id)
    signal addMission()

    model: missions

    Controls.Frame {
        id: frame

        property bool changed: false

        Layout.fillWidth: true

        GridLayout {
            anchors.fill: parent
            columns: 2
            rowSpacing: palette.spacing
            columnSpacing: palette.spacing

            Controls.Label {
                text: qsTr("Name")
            }

            Controls.TextField {
                text: modelData.name ? modelData.name : ""
                onEditingFinished: changed = true
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Actions")
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight

                Controls.Button {
                    checked: visibilities[index]
                    iconSource: checked ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                    onCheckedChanged: setVisible(modelData.id, checked)
                }

                Controls.Button {
                    tipText: qsTr("Restore")
                    iconSource: "qrc:/icons/restore.svg"
                    onClicked: restore(modelData.id)
                    enabled: changed
                }

                Controls.Button {
                    tipText: qsTr("Save")
                    iconSource: "qrc:/icons/save.svg"
                    onClicked: save(modelData.id)
                    enabled: changed
                }

                Controls.DelayButton {
                    tipText: qsTr("Remove")
                    iconSource: "qrc:/icons/remove.svg"
                    onActivated: remove(modelData.id)
                    iconColor: palette.dangerColor
                }
            }
        }
    }
}
