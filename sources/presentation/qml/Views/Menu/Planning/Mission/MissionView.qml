import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property string name
    property bool missionVisible: false
    property int assignedVehicle: -1
    property int status: MissionAssignment.NotActual

    property bool changed: false

    signal restore()
    signal save()
    signal remove()
    signal setMissionVisible(bool visible)
    signal uploadMission()
    signal downloadMission()
    signal cancelSyncMission()

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: palette.spacing
        columnSpacing: palette.spacing

        Controls.Label {
            text: qsTr("Name")
        }

        Controls.TextField {
            text: name
            onEditingFinished: changed = true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Actions")
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Controls.Button {
                tipText: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
                iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                onClicked: setMissionVisible(!missionVisible)
            }

            Controls.Button {
                tipText: qsTr("Download mission from MAV")
                iconSource: "qrc:/icons/download.svg"
                enabled: assignedVehicle > 0
                highlighted: status === MissionAssignment.Downloading
                onClicked: highlighted ? cancelSyncMission() : downloadMission()
            }

            Controls.Button {
                tipText: qsTr("Upload mission to MAV")
                iconSource: "qrc:/icons/upload.svg"
                enabled: assignedVehicle > 0
                highlighted: status === MissionAssignment.Uploading
                onClicked: highlighted ? cancelSyncMission() : uploadMission()
            }

            Controls.Button {
                tipText: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()
                enabled: changed
            }

            Controls.Button {
                tipText: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: changed
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: remove()
                iconColor: palette.dangerColor
            }
        }
    }
}
