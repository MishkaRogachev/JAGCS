import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: missionList

    property var missionIds: []

    function addMission() { presenter.addMission(); }

    spacing: palette.spacing

    MissionListPresenter {
        id: presenter
        view: missionList
        Component.onCompleted: updateMissions()
    }

    Repeater {
        model: missionIds

        MissionView {
            Layout.fillWidth: true
            missionId: modelData
        }
    }
}
