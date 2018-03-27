import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"

Item {
    id: topbar

    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.fill: parent
        anchors.rightMargin: dashboard.width
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Menu")
            flat: true
            onClicked: menu.home()
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" :
                                               "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? customPalette.textColor :
                                              customPalette.dangerColor
            tipText: qsTr("Links")
            flat: true
            // TODO: connection settings popup
        }

        ConnectionView {
            id: connection
        }

        RadioStatusView {
            id: radioStatus
            Layout.preferredWidth: sizings.controlBaseSize * 2
        }
    }
}
