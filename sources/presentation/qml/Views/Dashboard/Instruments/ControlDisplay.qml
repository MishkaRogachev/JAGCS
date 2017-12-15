import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

Controls.Pane {
    id: controlDisplay

    property int mode: Domain.None
    property var availableModes: []
    property bool armed: false

    enabled: online

    function updateCommandStatus(command, status) {
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

    ControlDisplayPresenter {
        id: presenter
        view: controlDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        CommandControls.DelayButton {
            id: armDisarm
            text: armed ? qsTr("DISARM") : qsTr("ARM")
            args: [ !armed ]
            delay: 1000
            command: Command.ArmDisarm
            Layout.preferredWidth: sizings.controlBaseSize * 4
            Layout.fillWidth: true
        }

        CommandControls.ModeBox {
            id: modeBox
            mode: controlDisplay.mode
            model: availableModes
            tipText: qsTr("Select mode")
            Layout.fillWidth: true
        }

        CommandControls.Button {
            id: rtl
            tipText: qsTr("Return to launch")
            iconSource: "qrc:/icons/home.svg"
            command: Command.Return
            Layout.alignment: Qt.AlignRight
        }
    }
}
