import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Card {
    id: missionView

    property int missionId: 0
    property bool missionVisible: false
    property alias name: nameEdit.text

    function edit() {
        if (!missionVisible) presenter.setMissionVisible(true);
        selectedMissionId = missionId;
    }

    function toggleMissionVisibility() {
        presenter.setMissionVisible(!missionVisible);
    }

    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    onDeepIn: edit()
    Component.onCompleted: {
        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

        var visibilityItem = menu.addEntry();
        visibilityItem.triggered.connect(toggleMissionVisibility);
        visibilityItem.text = Qt.binding(function() {
            return missionVisible ? qsTr("Hide mission") : qsTr("Show mission"); });
        visibilityItem.iconSource = Qt.binding(function() {
            return missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"; });

        var downloadItem = menu.addEntry(qsTr("Download"), "qrc:/icons/download.svg");
        downloadItem.enabled = Qt.binding(function() {
            return assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                   assignment.status !== MissionAssignment.Downloading &&
                   assignment.status !== MissionAssignment.Uploading });
        downloadItem.triggered.connect(assignment.download);

        var uploadItem = menu.addEntry(qsTr("Upload"), "qrc:/icons/upload.svg");
        uploadItem.enabled = Qt.binding(function() {
            return assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                   assignment.status !== MissionAssignment.Downloading &&
                   assignment.status !== MissionAssignment.Uploading });
        uploadItem.triggered.connect(assignment.upload);

        var uploadItem = menu.addEntry(qsTr("Cancel sync"), "qrc:/icons/cancel.svg");
        uploadItem.enabled = Qt.binding(function() {
            return assignment.assignedVehicleId > 0 && assignment.vehicleOnline &&
                   (assignment.status === MissionAssignment.Downloading ||
                   assignment.status === MissionAssignment.Uploading) });
        uploadItem.triggered.connect(assignment.cancelSync);

        // TODO: export mission to file
        menu.addEntry(qsTr("Export mission"), "qrc:/icons/save.svg").enabled = false;

        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
        removeItem.iconColor = customPalette.dangerColor;
        removeItem.triggered.connect(presenter.remove);
    }

    MissionPresenter {
        id: presenter
        view: missionView
        Component.onCompleted: setMission(missionId)
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: parent.margin
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: qsTr("Mission")
        }

        Controls.TextField {
            id: nameEdit
            onEditingFinished: presenter.rename(text)
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Vehicle")
        }

        MissionAssignmentView {
            id: assignment
            Layout.fillWidth: true
        }

        MissionItemListView {
            id: listView
            missionId: missionView.missionId
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }
    }
}
