import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: linkList

    property var linkIds: []

    implicitWidth: sizings.controlBaseSize * 11

    LinkListPresenter {
        id: presenter
        view: linkList
        Component.onCompleted: updateLinks()
    }

    ListView {
        anchors.fill: parent
        anchors.bottomMargin: addButton.height
        anchors.rightMargin: sizings.shadowSize
        spacing: sizings.spacing
        model: linkIds

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: LinkView {
            width: parent.width
            linkId: modelData
        }

        Controls.Frame {
            visible: parent.count === 0
            width: parent.width
            height: label.height + sizings.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No links present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
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
