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

    Flickable { // TODO: to listView
        anchors.fill: parent
        anchors.bottomMargin: addRow.height
        contentHeight: Math.max(column.height, frame.height)
        visible: selectedMissionId == 0
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        ColumnLayout {
            id: column
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - sizings.shadowSize * 2
            height: implicitHeight + sizings.shadowSize
            spacing: sizings.spacing

            Controls.Frame {
                id: frame
                visible: missionList.missionIds.count === 0
                width: parent.width
                height: label.height + sizings.margins * 2

                Controls.Label {
                    id: label
                    text: qsTr("No items present")
                    width: parent.width
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                }
            }

            MissionListView {
                id: missionList
                Layout.fillWidth: true
            }
        }
    }

    MissionEditView {
        anchors.fill: parent
        missionId: selectedMissionId
        visible: missionId > 0
    }

    RowLayout {
        id: addRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: sizings.spacing
        visible: selectedMissionId == 0

        Controls.Button {
            text: qsTr("Add Mission")
            iconSource: "qrc:/icons/add.svg"
            onClicked: missionList.addMission()
            Layout.fillWidth: true
        }

        // TODO: add Area, add Survey
    }
}
