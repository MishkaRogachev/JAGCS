import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: communication

    property var linkIds: []

    implicitWidth: palette.controlBaseSize * 11

    CommunicationPresenter {
        id: presenter
        view: communication
        Component.onCompleted: updateLinks()
    }

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addButton.height
        contentHeight: column.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + palette.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No links present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            spacing: palette.spacing

            Repeater {
                id: repeater
                model: linkIds

                CommunicationLinkView {
                    Layout.fillWidth: true
                    linkId: modelData
                }
            }
        }
    }

    Controls.Button {
        id: addButton
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: qsTr("Add Link")
        iconSource: "qrc:/icons/add.svg"
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            implicitWidth: parent.width
            y: parent.height

            Controls.MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: presenter.addUdpLink()
            }

            Controls.MenuItem {
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: presenter.addSerialLink()
            }
        }
    }
}
