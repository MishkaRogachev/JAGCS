import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"
import "Notifications"

Rectangle {
    id: topbar

    property string unitName

    color: palette.raisedColor
    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        id: unitRow
        anchors.left: parent.left
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            enabled: unitName.length > 0
            onClicked: dashboard.selectVehicle(0, "")
            flat: true
        }

        Controls.Label {
            text: unitName.length ? unitName : qsTr("All MAVs")
            font.bold: true
        }

        TopbarButton {
            iconSource: "qrc:/icons/settings.svg"
            tipText: qsTr("Vehicles")
            entry: "../Menu/Vehicles/VehicleListView.qml"
        }

        RadioStatusView {
            id: radioStatus
        }

        TopbarButton {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? palette.textColor : palette.dangerColor
            tipText: qsTr("Links")
            entry: "../Menu/Links/LinkListView.qml"
        }

        ConnectionView {
            id: connection
        }

        NotificationsView {
            id: notification
        }
    }

    RowLayout {
        anchors.right: parent.right
        spacing: sizings.spacing

        TopbarButton {
            iconSource: "qrc:/icons/planning.svg"
            tipText: qsTr("Planning")
            entry: "../Menu/Planning/PlanningView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Settings")
            entry: "../Menu/Settings/SettingsMenu.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/info.svg"
            tipText: qsTr("About")
            entry: "../Menu/About/AboutView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/quit.svg"
            tipText: qsTr("Quit")
            entry: "../Menu/Quit/QuitView.qml"
        }
    }
}
