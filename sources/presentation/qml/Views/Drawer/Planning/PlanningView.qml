import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "Missions"

Item {
    id: planning

    property var vehicles: []
    property int selectedMissionId: 0

    implicitWidth: sizings.controlBaseSize * 11

    PlanningPresenter {
        id: presenter
        view: planning
        Component.onCompleted: updateVehicles()
    }

    MissionListView {
        id: missionList
        anchors.fill: parent
    }

    MissionEditView {
        anchors.fill: parent
        missionId: selectedMissionId
        visible: missionId > 0
    }
}
