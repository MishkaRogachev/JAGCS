import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../DashboardControls" as DashboardControls

RowLayout {
    id: root

    spacing: sizings.spacing

    Connections {
        target: display
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
            default:
                break;
            }
        }
    }

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
