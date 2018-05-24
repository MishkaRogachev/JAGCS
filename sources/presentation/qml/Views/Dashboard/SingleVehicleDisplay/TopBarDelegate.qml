import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../DashboardControls" as DashboardControls

RowLayout {
    id: topbarDelegate

    spacing: sizings.spacing

    Connections {
        target: display
        ignoreUnknownSignals: true
        onUpdateCommandStatus: if (command == Command.SetMode) modeBox.status = status
    }

    Controls.Button {
        iconSource: "qrc:/icons/left.svg"
        tipText: qsTr("Overview")
        flat: true
        onClicked: dashboard.selectVehicle(0)
    }

    DashboardControls.VehicleLabel {
        name: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("No vehicle")
        Layout.fillWidth: true
    }

    Controls.Button {
        id: preparationButton
        iconSource: "qrc:/icons/calibrate.svg"
        tipText: (preparationPanel.visible ? qsTr("Close") : qsTr("Open")) + " " +
                 qsTr("preparation panel")
        flat: true
        onClicked: preparationPanel.visible ? preparationPanel.close() : preparationPanel.open()

        PreparationPanel {
            id: preparationPanel
            x: preparationButton.width - width
            y: preparationButton.height + sizings.spacing
            closePolicy: Controls.Popup.NoAutoClose
        }
    }

    RowLayout {
        spacing: sizings.spacing
        Layout.preferredWidth: list.width + sizings.margins

        DashboardControls.ModeBox {
            id: modeBox
            Layout.fillWidth: true
        }

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
}
