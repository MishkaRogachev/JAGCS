import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ToolBar {
    id: root

    signal setMode(string mode)
    signal quit()

    RowLayout {
        anchors.fill: parent

        Item { Layout.fillWidth: true }

        ConnectionStatusView {
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            iconSource: "qrc:/icons/flight.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: setMode("flight")
            checked: main.mode == "flight" // TODO: mode button
        }

        Button {
            iconSource: "qrc:/icons/settings.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: setMode("settings")
            checked: main.mode == "settings" // TODO: mode button
        }

        Button {
            iconSource: "qrc:/icons/quit.svg"
            iconColor: palette.negativeColor
            anchors.verticalCenter: parent.verticalCenter
            onClicked: quit()
        }
    }
}
