import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createNetworkSettingsPresenter(root)

    property alias proxyType: typeItem.currentText
    property alias hostName: hostNameItem.text
    property alias port: portItem.value
    property alias user: userItem.text
    property alias password: passwordItem.text

    function setProxyType(proxyType) {
        typeItem.currentIndex = presenter.typeModel.indexOf(proxyType);
    }

    Component.onCompleted: presenter.restore()

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
            model: presenter.typeModel
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
            editable: true
            from: 0
            to: 9999
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

        Button {
            Layout.fillWidth: true
            text: qsTr("Restore")
            onClicked: presenter.restore()
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Apply")
            onClicked: presenter.apply()
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
