import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ToolBar {
    id: root

    signal showSettings()
    signal hideSettings()
    signal quit()

    RowLayout {
        anchors.fill: parent

        Item { Layout.fillWidth: true }

        ConnectionStatusView {
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            // text: qsTr("Settings")
            iconSource: "qrc:/icons/settings.svg"
            checkable: true
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged: checked ? showSettings() : hideSettings()
        }

        Button {
            // text: qsTr("Quit")
            iconSource: "qrc:/icons/quit.svg"
            iconColor: palette.negativeColor
            anchors.verticalCenter: parent.verticalCenter
            onClicked: quit()
        }
    }
}
