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
        spacing: 1

        Image {
            source: "qrc:/icons/jagcs.svg"
            anchors.verticalCenter: parent.verticalCenter
            sourceSize.width: palette.controlBaseSize
            sourceSize.height: palette.controlBaseSize
        }

        Label {
            text: "JAGCS"
        }

        Item { Layout.fillWidth: true }

        ConnectionStatusView {
            anchors.verticalCenter: parent.verticalCenter
        }

        StatusModeButton {
            mode: "control"
            iconSource: "qrc:/icons/flight.svg"
            anchors.verticalCenter: parent.verticalCenter
        }

        StatusModeButton {
            mode: "mission"
            iconSource: "qrc:/icons/map-marker.svg"
            anchors.verticalCenter: parent.verticalCenter
        }

        StatusModeButton {
            mode: "settings"
            iconSource: "qrc:/icons/settings.svg"
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            iconSource: "qrc:/icons/quit.svg"
            iconColor: palette.negativeColor
            anchors.verticalCenter: parent.verticalCenter
            onClicked: quit()
        }
    }
}
