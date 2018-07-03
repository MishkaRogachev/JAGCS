import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "Missions"

Item {
    id: planning

    property var vehicles: []
    property int selectedMissionId: 0

    onSelectedMissionIdChanged: plot.setMission(selectedMissionId)
    Component.onCompleted: plotAvailable = true;
    Component.onDestruction: {
        plot.setMission(0);
        plotAvailable = false;
    }

    implicitWidth: sizings.controlBaseSize * 8

    Connections {
        target: map
        onSelectItem: {
            if (selectedMissionId != missionId) selectedMissionId = missionId;
            missionEdit.selectedItemId = itemId;
        }
    }

    Connections {
        target: drawer
        onCloseSubmode: selectedMissionId = 0
    }

    PlanningPresenter {
        id: presenter
        view: planning
        Component.onCompleted: updateVehicles()
    }

    MissionListView {
        id: missionList
        anchors.fill: parent
        visible: selectedMissionId == 0
    }

    MissionEditView {
        id: missionEdit
        anchors.fill: parent
        missionId: selectedMissionId
        visible: selectedMissionId > 0
    }
}
