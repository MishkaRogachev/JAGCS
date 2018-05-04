import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../"
import "../DashboardControls" as DashboardControls

RowLayout {
    id: topbarDelegate

    spacing: sizings.spacing

    Connections {
        target: display
        ignoreUnknownSignals: true
        onUpdateCommandStatus: {
            switch (command) {
            case Command.SetMode:
                modeBox.status = status;
                break;
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            default:
                break;
            }
        }
    }

    Controls.Button {
        iconSource: "qrc:/icons/left.svg"
        tipText: qsTr("Overview")
        flat: true
        onClicked: dashboard.selectVehicle(0)
    }

    Controls.Label {
        text: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("No vehicle")
        font.bold: true
    }

    DashboardControls.ModeBox {
        id: modeBox
        enabled: vehicle.online
        mode: vehicle.mode
        model: vehicle.availableModes
        Layout.preferredWidth: sizings.controlBaseSize * 3
    }

    DashboardControls.ArmButton { id: armDisarm }

    Controls.Button {
        iconSource: "qrc:/icons/joystick.svg"
        tipText: (manual.enabled ? qsTr("Disable") : qsTr("Enable")) +
                " " + qsTr("manual control")
        iconColor: manual.enabled ? customPalette.selectionColor : customPalette.textColor
        flat: true
        onClicked: manual.setEnabled(!manual.enabled)
    }

    Controls.Button {
        id: lockButton
        iconSource: instrumentsUnlocked ? "qrc:/icons/lock.svg" : "qrc:/icons/unlock.svg"
        tipText: (instrumentsUnlocked ? qsTr("Lock") : qsTr("Unlock")) + " " + qsTr("indicators")
        flat: true
        onClicked: instrumentsUnlocked = !instrumentsUnlocked
    }

    Controls.Button {
        iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                       "qrc:/icons/show_dashboard.svg"
        tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                 " " + qsTr("dashboard")
        flat: true
        onClicked: dashboardVisible = !dashboardVisible
    }
}
