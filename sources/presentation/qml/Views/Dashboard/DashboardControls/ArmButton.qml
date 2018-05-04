import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: control

    property alias status: armDisarm.status

    flat: true
    enabled: !popup.visible && vehicle.online
    iconSource: vehicle.armed ? "qrc:/icons/armed.svg" : "qrc:/icons/disarmed.svg"
    iconColor: vehicle.armed ? customPalette.cautionColor : customPalette.textColor
    tipText: vehicle.armed ? qsTr("ARMED") : qsTr("DISARMED")
    onClicked: popup.open()

    Controls.Popup {
        id: popup
        y: control.height

        DelayCommandButton {
            id: armDisarm
            text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            args: [ !vehicle.armed ]
            command: Command.ArmDisarm
            implicitWidth: sizings.controlBaseSize * 3
        }
    }
}
