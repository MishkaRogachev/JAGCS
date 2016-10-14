import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

ColumnLayout {
    id: root

    property QtObject presenter: factory.createConnectionSettingsPresenter(root)

    Frame {
        Layout.fillWidth: true

        GridLayout {
            anchors.fill: parent
            columns: 2

            Label {
                text: qsTr("System ID")
                Layout.fillWidth: true
            }

            SpinBox {
                value: presenter.systemId
                Layout.fillWidth: true
                from: 0
                to: 255
                onValueChanged: presenter.setSystemId(value)
            }

            Label {
                text: qsTr("Component ID")
                Layout.fillWidth: true
            }

            SpinBox {
                value: presenter.componentId
                Layout.fillWidth: true
                from: 0
                to: 255
                onValueChanged: presenter.setComponentId(value)
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
                model: presenter.links

                ConnectionItemView {
                    presenter: root.presenter
                    Layout.fillWidth: true
                    link: modelData
                }
            }
        }
    }

    Button {
        Layout.fillWidth: true
        text: qsTr("Add Link")
        iconSource: "qrc:/icons/add.svg"
        anchors.right: parent.right
        onClicked: if (!addMenu.visible) addMenu.open()
        enabled: presenter.addEnabled

        Menu {
            id: addMenu
            implicitWidth: parent.width
            y: parent.height

            MenuItem {
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: presenter.addSerialLink()
            }

            MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: presenter.addUdpLink()
            }
        }
    }
}
