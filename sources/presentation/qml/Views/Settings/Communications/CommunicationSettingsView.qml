import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ColumnLayout {
    id: root

    property var links: []

    signal addUdpLink()
    signal addSerialLink()

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: column.height
        clip: true

        ScrollBar.vertical: ScrollBar {}

        Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + palette.margins * 2

            Label {
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
                model: links

                CommunicationLinkView {
                    id: linkView
                    Layout.fillWidth: true
                    Component.onCompleted: modelData.setView(linkView)
                }
            }
        }
    }

    Button {
        id: addButton
        Layout.fillWidth: true
        text: qsTr("Add Link")
        iconSource: "qrc:/icons/add.svg"
        anchors.right: parent.right
        onClicked: if (!addMenu.visible) addMenu.open()

        Menu {
            id: addMenu
            implicitWidth: parent.width
            y: parent.height

            MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: addUdpLink()
            }

            MenuItem {
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: addSerialLink()
            }
        }
    }
}
