import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Pane {
    id: root

    property QtObject presenter: factory.createConnectionPresenter(root)

    ColumnLayout {
        anchors.fill: parent

        Button {
            text: qsTr("Add Link")
            anchors.verticalCenter: parent.verticalCenter
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
