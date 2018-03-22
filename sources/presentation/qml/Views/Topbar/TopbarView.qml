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
        anchors.right: parent.right
        spacing: sizings.spacing

        RadioStatusView {
            id: radioStatus
        }

        ConnectionView {
            id: connection
        }

        TopbarButton {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" :
                                               "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? customPalette.textColor :
                                              customPalette.dangerColor
            tipText: qsTr("Links")
            entry: "qrc:/Views/Menu/Links/LinkListView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/flight.svg"
            tipText: qsTr("Vehicles")
            entry: "qrc:/Views/Menu/Vehicles/VehicleListView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/planning.svg"
            tipText: qsTr("Planning")
            entry: "qrc:/Views/Menu/Planning/PlanningView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Settings")
            entry: "qrc:/Views/Menu/Settings/SettingsMenu.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/info.svg"
            tipText: qsTr("About")
            entry: "qrc:/Views/Menu/About/AboutView.qml"
        }

        TopbarButton {
            iconSource: "qrc:/icons/quit.svg"
            tipText: qsTr("Quit")
            entry: "qrc:/Views/Menu/Quit/QuitView.qml"
        }
    }
}
