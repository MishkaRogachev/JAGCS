import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls
import "../CommandWidgets" as CommandWidgets

Controls.Pane {
    id: root

    Connections {
        target: vehicleDisplay
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            case Command.SetMode:
                modeBox.status = status;
                break;
            case Command.Return:
                rtl.status = status;
                break;
            case Command.GoTo:
                goTo.status = status;
                break;
            case Command.NavTo:
                navTo.status = status;
                break;
            case Command.ChangeAltitude:
                changeAlt.status = status;
                break;
            case setSpeed.command:
                setSpeed.status = status;
                break;
            default:
                break;
            }
        }
    }

    enabled: vehicle.online

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        RowLayout {
             spacing: sizings.spacing

             DashboardControls.DelayCommandButton {
                 id: armDisarm
                 text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
                 args: [ !vehicle.armed ]
                 command: Command.ArmDisarm
                 Layout.preferredWidth: sizings.controlBaseSize * 2
             }

             DashboardControls.ModeBox {
                 id: modeBox
                 mode: vehicle.mode
                 model: vehicle.availableModes
                 Layout.fillWidth: true
             }

             DashboardControls.CommandButton {
                 id: rtl
                 tipText: qsTr("Return to launch")
                 iconSource: "qrc:/icons/home.svg"
                 command: Command.Return
                 Layout.alignment: Qt.AlignRight
             }
        }

        CommandWidgets.GoTo {
            id: goTo
            visible: vehicle.mode === Domain.Mission
        }

        CommandWidgets.NavTo {
            id: navTo
            visible: vehicle.mode === Domain.NavTo
        }

        CommandWidgets.ChangeAlt {
            id: changeAlt
            visible: vehicle.mode === Domain.Circle ||
                     vehicle.mode === Domain.Loiter ||
//                     vehicle.mode === Domain.Mission ||
                     vehicle.mode === Domain.Return
        }

        CommandWidgets.SetSpd {
            id: setSpeed
            visible: vehicle.mode === Domain.Mission ||
                     vehicle.mode === Domain.NavTo
        }
    }
}
