import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls    
import "../"

TopBarDelegateBase {
    id: topbarDelegate

    Controls.Button {
        id: lockButton
        visible: dashboard.selectedVehicle !== undefined
        iconSource: dashboard.display.instrumentsUnlocked ? "qrc:/icons/lock.svg" :
                                                            "qrc:/icons/unlock.svg"
        tipText: (dashboard.display.instrumentsUnlocked ?
                      qsTr("Lock") : qsTr("Unlock")) + " " + qsTr("indicators")
        flat: true
        onClicked: dashboard.display.instrumentsUnlocked = !dashboard.display.instrumentsUnlocked
    }

    Controls.Button {
        visible: dashboard.selectedVehicle !== undefined
        iconSource: "qrc:/icons/joystick.svg"
        tipText: (manual.enabled ? qsTr("Disable") : qsTr("Enable")) +
                " " + qsTr("manual control")
        iconColor: manual.enabled ? customPalette.selectionColor : customPalette.textColor
        flat: true
        onClicked: manual.setEnabled(!manual.enabled)
    }

    Controls.Label {
        text: dashboard.selectedVehicle !== undefined ?
                dashboard.selectedVehicle.name : qsTr("All MAVs")
        font.bold: true
    }

    Controls.Button {
        iconSource: "qrc:/icons/left.svg"
        tipText: qsTr("Overview")
        enabled: dashboard.selectedVehicle !== undefined
        flat: true
        onClicked: dashboard.selectVehicle(0)
    }
}
