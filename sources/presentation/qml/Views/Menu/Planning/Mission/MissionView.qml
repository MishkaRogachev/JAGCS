import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool missionVisible: false
    property int count: 0
    property int assignedVehicleId: -1
    property int status: MissionAssignment.NotActual

    property alias name: nameEdit.text

    signal rename(string name)
    signal setMissionVisible(bool visible)
    signal remove()
    signal assignVehicle(int id)
    signal uploadMission()
    signal downloadMission()
    signal cancelSyncMission()

    onAssignedVehicleIdChanged: updateSelectedVehicle()

    Connections {
        target: planning
        onVehiclesChanged: updateSelectedVehicle()
    }

    function updateSelectedVehicle() {
        for (var i = 0; i < vehicles.length; ++i) {
            if (vehicles[i].id === assignedVehicleId) {
                vehicleBox.currentIndex = i;
                return;
            }
        }
        vehicleBox.currentIndex = -1;
    }

    GridLayout {
        anchors.fill: parent
        columns: 4
        rowSpacing: palette.spacing
        columnSpacing: palette.spacing

        Controls.Label {
            text: qsTr("Name")
        }

        Controls.TextField {
            id: nameEdit
            onEditingFinished: rename(text)
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
            iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            onClicked: setMissionVisible(!missionVisible)
        }

        Controls.DelayButton {
            tipText: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            onActivated: remove()
            iconColor: palette.dangerColor
        }

        Controls.Label {
            text: qsTr("Vehicle")
        }

        RowLayout {
            Controls.ComboBox {
                id: vehicleBox
                model: vehicles
                textRole: "name"
                onActivated: assignVehicle(vehicles[currentIndex].id)
                Layout.fillWidth: true
            }

            Controls.ComboBox { // NOTE: for mission slot
                enabled: false
                Layout.maximumWidth: palette.controlBaseSize
            }
        }

        Controls.Button {
            tipText: qsTr("Download mission from MAV")
            iconSource: "qrc:/icons/download.svg"
            enabled: assignedVehicleId > 0
            highlighted: status === MissionAssignment.Downloading
            onClicked: highlighted ? cancelSyncMission() : downloadMission()
        }

        Controls.Button {
            tipText: qsTr("Upload mission to MAV")
            iconSource: "qrc:/icons/upload.svg"
            enabled: assignedVehicleId > 0
            highlighted: status === MissionAssignment.Uploading
            onClicked: highlighted ? cancelSyncMission() : uploadMission()
        }

        Controls.Label {
            text: qsTr("Commands")
        }

        Controls.Label { // Items Row
            text: count
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Edit commands")
            iconSource: "qrc:/icons/edit.svg"
            onClicked: deepIn("Planning/Mission/MissionItemEditView.qml", name);
        }

        Controls.Button {
            tipText: qsTr("Export mission")
            iconSource: "qrc:/icons/save.svg"
            enabled: false
            //onClicked: TODO: export()
        }
    }
}
