import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

Controls.Popup {
    id: popup
    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    width: sizings.controlBaseSize * 5

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
        spacing: sizings.spacing

        Repeater {
            model: [
                { text: qsTr("AHRS"), subsystem: vehicle.ahrs },
                { text: qsTr("SNS"), subsystem: vehicle.satellite },
                { text: qsTr("Barometric"), subsystem: vehicle.barometric },
                { text: qsTr("Pitot"), subsystem: vehicle.pitot },
                { text: qsTr("Radalt"), subsystem: vehicle.radalt },
                { text: qsTr("Battery"), subsystem: vehicle.battery }
            ]

            RowLayout {
                DashboardControls.Label {
                    text: modelData.text
                    Layout.fillWidth: true
                }

                Controls.ColoredIcon {
                    source: {
                        if (modelData.subsystem.present) {
                            if (modelData.subsystem.operational) return "qrc:/ui/ok.svg";
                            else return "qrc:/icons/remove.svg"
                        }
                        else {
                            return "qrc:/icons/cancel.svg"
                        }
                    }

                    color: {
                        if (modelData.subsystem.present) {
                            if (modelData.subsystem.operational) return customPalette.positiveColor;
                            else return customPalette.dangerColor;
                        }
                        else {
                            return customPalette.sunkenColor;
                        }
                    }
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


