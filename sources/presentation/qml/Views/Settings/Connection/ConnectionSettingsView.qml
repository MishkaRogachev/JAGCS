import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ColumnLayout {
    id: root

    property alias systemId: systemIdBox.value
    property alias componentId: componentIdBox.value
    property var links
    property alias isAddEnabled: addButton.enabled

    property var serialDevices
    property var serialBaudRates

    signal requestSystemId(int systemId)
    signal requestComponentId(int componentId)
    signal requestNewUdp()
    signal requestNewSerial()
    signal requestRemoveLink(QtObject link)

    Frame {
        Layout.fillWidth: true

        RowLayout {
            anchors.fill: parent

            Label {
                text: qsTr("System ID")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
            }

            SpinBox {
                id: systemIdBox
                Layout.fillWidth: true
                from: 0
                to: 255
                onValueChanged: requestSystemId(value)
            }

            Label {
                text: qsTr("Component ID")
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
            }

            SpinBox {
                id: componentIdBox
                Layout.fillWidth: true
                from: 0
                to: 255
                onValueChanged: requestComponentId(value)
            }
        }
    }

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: column.height
        clip: true

        ScrollBar.vertical: ScrollBar { }

        Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + 32

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
            anchors.centerIn: parent
            spacing: 8

            Repeater {
                id: repeater
                model: links

                ConnectionItemView {
                    Layout.fillWidth: true
                    link: modelData
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
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: requestNewSerial()
            }

            MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: requestNewUdp()
            }
        }
    }
}
