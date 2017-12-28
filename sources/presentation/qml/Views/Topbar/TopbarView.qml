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

        Controls.Button {
            iconSource: "qrc:/icons/settings.svg"
            flat: true
            tipText: qsTr("Vehicles")
            onClicked: menu.goTo("Vehicles/VehicleListView.qml", tipText, {})
        }

        RadioStatusView {
            id: radioStatus
        }

        Controls.Button {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? palette.textColor : palette.dangerColor
            flat: true
            tipText: qsTr("Links")
            onClicked: menu.goTo("Links/LinkListView.qml", tipText, {})
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

        Controls.Button {
            iconSource: "qrc:/icons/map-marker.svg"
            flat: true
            tipText: qsTr("Planning")
            onClicked: menu.goTo("Planning/PlanningView.qml", tipText, {})
        }

        Controls.Button {
            id: menuButton
            iconSource: "qrc:/icons/burger.svg"
            flat: true
            tipText: qsTr("Menu")
            onClicked: menu.goTo();
        }

        Controls.Button {
            iconSource: "qrc:/icons/quit.svg"
            flat: true
            tipText: qsTr("Quit")
            onClicked: menu.goTo("Quit/QuitView.qml", tipText, {})
        }
    }
}
