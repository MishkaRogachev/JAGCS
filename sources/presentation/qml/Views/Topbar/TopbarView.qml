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

        Controls.Button { // TODO: goto Vehicle settings
            iconSource: "qrc:/icons/settings.svg"
            flat: true
            enabled: false
        }

        RadioStatusView {
            id: radioStatus
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
            id: menuButton
            tipText: menu.visible ? qsTr("Menu") : qsTr("Close menu")
            iconSource: menu.visible ? "qrc:/icons/right.svg" : "qrc:/icons/burger.svg"
            flat: true
            onClicked: menu.visible ? menuDrawer.close() : menuDrawer.open()
        }
    }
}
