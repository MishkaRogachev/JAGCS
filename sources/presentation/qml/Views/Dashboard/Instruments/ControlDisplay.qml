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
        default:
            break;
        }
    }

    ControlDisplayPresenter {
        id: presenter
        view: controlDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    GridLayout {
        anchors.centerIn: parent
        width: parent.width
        columnSpacing: sizings.spacing
        rowSpacing: sizings.spacing
        columns: 2

        CommandControls.Button {
            id: armDisarm
            text: armed ? qsTr("ARMED") : qsTr("DISARMED")
            tipText: armed ? qsTr("Hold to disarm") : qsTr("Hold to arm")
            args: [ !armed ]
            command: Command.ArmDisarm
            Layout.fillWidth: true
        }

        CommandControls.ModeBox {
            id: modeBox
            mode: controlDisplay.mode
            model: availableModes
            tipText: qsTr("Select mode")
            Layout.fillWidth: true
        }
    }
}
