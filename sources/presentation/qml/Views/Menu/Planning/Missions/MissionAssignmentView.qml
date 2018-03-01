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

    spacing: sizings.spacing

    MissionAssignmentPresenter {
        id: presenter
        view: missionAssignmentView
        Component.onCompleted: setMission(missionId)
    }

    Controls.ProgressBar {
         to: count
         value: progress
         text: assignedVehicleId > 0 ? (progress + "/" + count) : qsTr("None")
         Layout.fillWidth: true
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
}
