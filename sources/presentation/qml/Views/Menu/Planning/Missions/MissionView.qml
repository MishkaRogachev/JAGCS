import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: missionView

    property int missionId: 0
    property int count: 0
    property int progress: 0
    property bool missionVisible: false
    property bool vehicleOnline: false
    property int assignedVehicleId: 0
    property int status: MissionAssignment.NotActual

    property alias name: nameEdit.text

    onAssignedVehicleIdChanged: updateSelectedVehicle()

    Connections {
        target: planning
        onVehiclesChanged: updateSelectedVehicle()
    }

    function updateSelectedVehicle() {
        for (var i = 0; i < vehicles.length; ++i) {
            if (vehicles[i].id === assignedVehicleId) {
                vehicleBox.currentIndex = i;
                vehicleOnline = vehicles[i].online;
                return;
            }
        }
        vehicleBox.currentIndex = -1;
        vehicleOnline = false;
    }

    MissionPresenter {
        id: presenter
        view: missionView
        Component.onCompleted: setMission(missionId)
    }

    GridLayout {
        anchors.fill: parent
        columns: 4
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: qsTr("Name")
        }

        Controls.TextField {
            id: nameEdit
            onEditingFinished: presenter.rename(text)
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
            iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            onClicked: presenter.setMissionVisible(!missionVisible)
        }

        Controls.DelayButton {
            tipText: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            onActivated: presenter.remove()
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
                onActivated: presenter.assignVehicle(vehicles[currentIndex].id)
                Layout.fillWidth: true
            }

            Controls.ComboBox { // NOTE: for mission slot
                enabled: false
                Layout.maximumWidth: sizings.controlBaseSize
            }
        }

        Controls.Button {
            tipText: qsTr("Download mission from MAV")
            iconSource: "qrc:/icons/download.svg"
            enabled: assignedVehicleId > 0 && vehicleOnline
            highlighted: status === MissionAssignment.Downloading
            onClicked: highlighted ? presenter.cancelSyncMission() : presenter.downloadMission()
        }

        Controls.Button {
            tipText: qsTr("Upload mission to MAV")
            iconSource: "qrc:/icons/upload.svg"
            enabled: assignedVehicleId > 0 && vehicleOnline
            highlighted: status === MissionAssignment.Uploading
            onClicked: highlighted ? presenter.cancelSyncMission() : presenter.uploadMission()
        }

        Controls.Label {
            text: qsTr("Commands")
        }

       Controls.ProgressBar {
            to: count
            value: progress
            text: progress + "/" + count
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Edit commands")
            iconSource: "qrc:/icons/edit.svg"
            enabled: missionId > 0
            onClicked: deepIn("Planning/Missions/MissionItemListView.qml", name,
                              { "missionId": missionId });
        }

        Controls.Button {
            tipText: qsTr("Export mission")
            iconSource: "qrc:/icons/save.svg"
            enabled: false
            //onClicked: TODO: export()
        }
    }
}
