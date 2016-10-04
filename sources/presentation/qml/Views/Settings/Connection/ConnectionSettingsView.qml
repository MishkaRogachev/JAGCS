import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial";

Frame {
    id: root

    property QtObject presenter: factory.createConnectionSettingsPresenter(root)

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: 16

        Repeater {
            model: presenter.links

            ConnectionItemView {
                presenter: root.presenter
                link: modelData
            }
        }

        Button {
            text: qsTr("Add Link")
            anchors.right: parent.right
            onClicked: addMenu.open()
            enabled: presenter.addEnabled

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
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
