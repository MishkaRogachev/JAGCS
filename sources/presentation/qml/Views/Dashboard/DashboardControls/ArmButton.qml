import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: control

    property alias status: armDisarm.status

    flat: true
    enabled: vehicle.online
    iconSource: vehicle.armed ? "qrc:/icons/armed.svg" : "qrc:/icons/disarmed.svg"
    iconColor: vehicle.armed ? customPalette.selectionColor : customPalette.textColor
    tipText: vehicle.armed ? qsTr("ARMED") : qsTr("DISARMED")
    onClicked: popup.visible ? popup.close() : popup.open()

    Controls.Popup {
        id: popup
        y: control.height
        closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

        DelayCommandButton {
            id: armDisarm
            text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            args: [ !vehicle.armed ]
            command: Command.ArmDisarm
            implicitWidth: sizings.controlBaseSize * 3
        }
    }
}
