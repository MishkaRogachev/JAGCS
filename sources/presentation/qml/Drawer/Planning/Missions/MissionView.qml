import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Card {
    id: missionView

    property int missionId: 0
    property bool missionVisible: false
    property alias name: nameEdit.text

    function edit() {
        if (!missionVisible) presenter.setMissionVisible(true);
        selectedMissionId = missionId;
    }

    onDeepIn: edit()
    onMissionIdChanged: presenter.setMission(missionId)

    menuItems: [
        Controls.MenuItem {
            text: qsTr("Edit")
            iconSource: "qrc:/icons/edit.svg"
            onTriggered: edit()
        },
        Controls.MenuItem {
            text: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
            iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            onTriggered: presenter.setMissionVisible(!missionVisible)
        },
        Controls.MenuItem {
            text: qsTr("Download")
            iconSource: "qrc:/icons/download.svg"
            enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                     assignment.status !== MissionAssignment.Downloading &&
                     assignment.status !== MissionAssignment.Uploading
            onTriggered: assignment.download()
        },
        Controls.MenuItem {
            text: qsTr("Upload")
            iconSource: "qrc:/icons/upload.svg"
            enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                     assignment.status !== MissionAssignment.Downloading &&
                     assignment.status !== MissionAssignment.Uploading
            onTriggered: assignment.upload()
        },
        Controls.MenuItem {
            text: qsTr("Cancel sync")
            iconSource: "qrc:/icons/cancel.svg"
            enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                     (assignment.status === MissionAssignment.Downloading ||
                      assignment.status === MissionAssignment.Uploading)
            onTriggered: assignment.upload()
        },
        // TODO: download
        Controls.MenuItem {
            text: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: industrial.colors.negative
            onTriggered: presenter.remove
        }
    ]

    implicitWidth: col.implicitWidth + industrial.margins * 2
    implicitHeight: col.implicitHeight + industrial.margins * 2

    MissionPresenter {
        id: presenter
        view: missionView
    }

    ColumnLayout {
        id: col
        anchors.fill: parent
        anchors.margins: industrial.margins
        anchors.rightMargin: missionView.margin
        spacing: industrial.spacing

        Controls.TextField {
            id: nameEdit
            labelText: qsTr("Mission name")
            flat: true
            onEditingFinished: presenter.rename(text)
            Layout.fillWidth: true
        }

        MissionAssignmentView {
            id: assignment
            missionId: missionView.missionId
            Layout.fillWidth: true
        }

        MissionItemListView {
            id: listView
            missionId: missionView.missionId
            Layout.fillWidth: true
        }
    }
}
