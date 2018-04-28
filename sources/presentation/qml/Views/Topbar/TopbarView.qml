import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"

Item {
    id: topbar

    property bool instrumentsUnlocked: false

    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.left: parent.left
        height: parent.height
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Menu")
            flat: true
            onClicked: menu.home()
        }

        Controls.Button {
            iconSource: "qrc:/icons/planning.svg"
            tipText: qsTr("Planning")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Planning/PlanningView.qml", qsTr("Planning"), {})
        }

        Controls.Button {
            iconSource: "qrc:/icons/fleet.svg"
            tipText: qsTr("Vehicles")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Vehicles/VehicleListView.qml", qsTr("Vehicles"), {})
        }

        Controls.Button {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" :
                                               "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? customPalette.textColor :
                                              customPalette.dangerColor
            tipText: qsTr("Links")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Links/LinkListView.qml", qsTr("Links"), {})
        }
    }

    RowLayout {
        anchors.right: parent.right
        height: parent.height
        spacing: sizings.spacing

        ConnectionView {
            id: connection
        }

        RadioStatusView {
            id: radioStatus
            Layout.preferredWidth: sizings.controlBaseSize * 5
        }

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            tipText: qsTr("Overview")
            enabled: dashboard.selectedVehicle !== undefined
            flat: true
            onClicked: dashboard.selectVehicle(0)
        }

        Controls.Button {
            id: lockButton
            visible: dashboard.selectedVehicle !== undefined
            iconSource: instrumentsUnlocked ? "qrc:/icons/lock.svg" : "qrc:/icons/unlock.svg"
            tipText: (instrumentsUnlocked ? qsTr("Lock") : qsTr("Unlock")) + " " + qsTr("indicators")
            flat: true
            onClicked: instrumentsUnlocked = !instrumentsUnlocked
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
            iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                           "qrc:/icons/show_dashboard.svg"
            tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                     " " + qsTr("dashboard")
            flat: true
            onClicked: dashboardVisible = !dashboardVisible
        }
    }
}
