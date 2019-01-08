import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "../DashboardControls" as DashboardControls

Controls.Popup {
    id: popup

    property int fails: 0

    width: industrial.baseSize * 5
    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    Connections {
        target: display
        ignoreUnknownSignals: true
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            default:
                break;
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: industrial.spacing

        Repeater {
            model: [
                { text: qsTr("AHRS"), subsystem: vehicle.ahrs },
                { text: qsTr("SNS"), subsystem: vehicle.satellite },
                { text: qsTr("Barometric"), subsystem: vehicle.barometric },
                { text: qsTr("Pitot"), subsystem: vehicle.pitot },
                { text: qsTr("Radalt"), subsystem: vehicle.radalt },
                { text: qsTr("Battery"), subsystem: vehicle.battery }
            ]

            delegate: DashboardControls.ChecklistItem {
                property bool failed: modelData.subsystem.present && !modelData.subsystem.operational
                text: modelData.text
                state: {
                    if (modelData.subsystem.present) {
                        if (modelData.subsystem.operational) return "OK";
                        else return "BAD";
                    }
                    else {
                        return "UNACTIVE";
                    }
                }
                onFailedChanged: failed ? fails++ : fails --
                Layout.fillWidth: true
            }
        }

        DashboardControls.ChecklistItem {
            text: qsTr("Mission")
            state: {
                if (!vehicle.mission.assigned) return "UNACTIVE";

                switch (vehicle.mission.status) {
                case MissionAssignment.Actual: return "OK";
                case MissionAssignment.Downloading: return "INPROCESS";
                case MissionAssignment.Uploading: return "INPROCESS";
                case MissionAssignment.NotActual:
                default: return "CAUTION";
                }
            }
        }


        DashboardControls.DelayCommandButton {
            id: armDisarm
            text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            args: [ !vehicle.armed ]
            command: Command.ArmDisarm
            Layout.fillWidth: true
        }
    }
}


