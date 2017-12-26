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
    property string contextText

    color: palette.raisedColor
    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        id: unitRow
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: nav.left
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
        id: nav
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: menuButton.right
        spacing: sizings.spacing
        width: menuDrawer.width
        clip: true
        visible: menu.visible

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: !menu.atHome
            onClicked: menu.home()
        }

        Repeater {
            model: contextModel

            Controls.Button {
                text: model.text
                flat: true
                visible: index + 1 < contextModel.count
                onClicked: menu.backOut(index)
            }
        }

        Controls.Label {
            text: contextText
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Controls.Button {
        id: menuButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        tipText: menu.visible ? qsTr("Menu") : qsTr("Close menu")
        iconSource: menu.visible ? "qrc:/icons/right.svg" : "qrc:/icons/burger.svg"
        flat: true
        onClicked: menu.visible ? menuDrawer.close() : menuDrawer.open()
    }
}
