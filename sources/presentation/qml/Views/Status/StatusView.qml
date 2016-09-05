import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Connection"

ToolBar {
    id: root

    property QtObject presenter: factory.createStatusPresenter(root)

    RowLayout {
        anchors.fill: parent

        Item { Layout.fillWidth: true }


        Button {
            id: connectionButton
            text: qsTr("Connection")
            checkable: true
            anchors.verticalCenter: parent.verticalCenter
        }

        Button {
            text: qsTr("Settings")
            checkable: true
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged: settings.visible = checked
        }

        Button {
            text: qsTr("Quit")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: presenter.quit()
        }
    }

    ConnectionView {
        id: connection
        visible: connectionButton.checked
        anchors.top: parent.bottom
        x: connectionButton.x
    }
}
