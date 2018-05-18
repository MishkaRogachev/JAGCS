import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: missionAssignmentView

    property bool vehicleOnline: true

    property int progress: 0
    property int assignedVehicleId: 0
    property int status: MissionAssignment.NotActual

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

    function download() {
        presenter.downloadMission()
    }

    function upload() {
        presenter.uploadMission()
    }

    function cancelSync() {
        presenter.cancelSyncMission()
    }

    onAssignedVehicleIdChanged: updateSelectedVehicle()

    spacing: sizings.spacing

    Connections {
        target: planning
        onVehiclesChanged: updateSelectedVehicle()
    }

    MissionAssignmentPresenter {
        id: presenter
        view: missionAssignmentView
        Component.onCompleted: setMission(missionId)
    }

    Controls.ComboBox {
        id: vehicleBox
        model: vehicles
        textRole: "name"
        onActivated: presenter.assignVehicle(vehicles[currentIndex].id)
        Layout.fillWidth: true
    }

    Controls.ComboBox { // NOTE: for mission slot
        enabled: false
        Layout.maximumWidth: sizings.controlBaseSize * 2
    }
}
