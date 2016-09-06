import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Pane {
    id: root

    property QtObject presenter: factory.createConnectionPresenter(root)

    ColumnLayout {
        id: column
        anchors.fill: parent

        Repeater {
            model: presenter.links

            Frame {
                Layout.preferredWidth: column.width

                RowLayout {
                    anchors.fill: parent

                    Label {
                        text: qsTr("Link") + " " + (index + 1).toString()
                    }
                }
            }
        }

        Button {
            text: qsTr("Add Link")
            anchors.right: parent.right
            onClicked: addMenu.open()

            Menu {
                id: addMenu

                MenuItem {
                    text: qsTr("Serial")
                    onTriggered: presenter.addSerialLink()
                }

                MenuItem {
                    text: qsTr("Udp")
                    onTriggered: presenter.addUdpLink()
                }

                MenuItem {
                    text: qsTr("Close")
                    onTriggered: addMenu.close()
                }
            }
        }
    }
}
