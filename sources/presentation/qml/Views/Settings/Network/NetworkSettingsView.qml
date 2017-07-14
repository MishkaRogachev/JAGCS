import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ColumnLayout {
    id: root

    property alias type: typeItem.currentText
    property alias hostName: hostNameItem.text
    property alias port: portItem.value
    property alias user: userItem.text
    property alias password: passwordItem.text

    property alias typeModel: typeItem.model

    signal apply()
    signal restore()

    function setProxyType(proxyType) {
        typeItem.currentIndex = typeModel.indexOf(proxyType);
    }

    Frame {
        Layout.fillWidth: true

        GridLayout {
            columns: 2
            anchors.fill: parent

            Label {
                Layout.fillWidth: true
                text: qsTr("Proxy type")
            }

            ComboBox {
                id: typeItem
                Layout.fillWidth: true
                model: typeModel
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("Host name")
            }

            TextField {
                id: hostNameItem
                Layout.fillWidth: true
                placeholderText: qsTr("Enter hostname")
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("Port")
            }

            SpinBox {
                id: portItem
                Layout.fillWidth: true
                from: 0
                to: 99999
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("User name")
            }

            TextField {
                id: userItem
                Layout.fillWidth: true
                placeholderText: qsTr("Enter user name")
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("User password")
            }

            TextField {
                id: passwordItem
                Layout.fillWidth: true
                placeholderText: qsTr("Enter password")
                echoMode: TextInput.Password
            }
        }
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            Layout.fillWidth: true
            text: qsTr("Restore")
            onClicked: restore()
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Apply")
            onClicked: apply()
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
