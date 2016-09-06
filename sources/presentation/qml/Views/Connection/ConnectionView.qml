import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createConnectionPresenter(root)

    ColumnLayout {
        id: column
        anchors.fill: parent

        Repeater {
            model: presenter.links

            ConnectionItemView {
                presenter: modelData
                onRemoveMe: root.presenter.removeLink(index)
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

        Item {
            Layout.fillHeight: true
        }
    }
}
