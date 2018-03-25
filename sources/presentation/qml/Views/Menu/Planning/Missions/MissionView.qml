import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: missionView

    property int missionId: 0
    property alias assignedVehicleId: assignment.assignedVehicleId
    property int count: 0
    property bool missionVisible: false
    property alias name: nameEdit.text

    function updateSelectedVehicle() {
        for (var i = 0; i < vehicles.length; ++i) {
            if (vehicles[i].id === assignedVehicleId) {
                vehicleBox.currentIndex = i;
                assignment.vehicleOnline = vehicles[i].online;
                return;
            }
        }
        vehicleBox.currentIndex = -1;
        assignment.vehicleOnline = false;
    }

    onAssignedVehicleIdChanged: updateSelectedVehicle()

    Connections {
        target: planning
        onVehiclesChanged: updateSelectedVehicle()
    }

    MissionPresenter {
        id: presenter
        view: missionView
        Component.onCompleted: setMission(missionId)
    }

    GridLayout {
        anchors.fill: parent
        columns: 2
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

        Controls.Label {
            text: qsTr("Assignment")
        }

        MissionAssignmentView {
            id: assignment
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Actions")
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Controls.Button {
                tipText: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
                iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                onClicked: presenter.setMissionVisible(!missionVisible)
            }

            Controls.Button {
                tipText: qsTr("Export mission")
                iconSource: "qrc:/icons/save.svg"
                enabled: false
                //onClicked: TODO: export()
            }

            Controls.Button {
                tipText: qsTr("Edit commands")
                iconSource: "qrc:/icons/edit.svg"
                enabled: missionId > 0
                onClicked: deepIn("qrc:/Views/Menu/Planning/Missions/MissionEditView.qml",
                                  name, { "missionId": missionId });
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: presenter.remove()
                iconColor: customPalette.dangerColor
            }
        }
    }
}
