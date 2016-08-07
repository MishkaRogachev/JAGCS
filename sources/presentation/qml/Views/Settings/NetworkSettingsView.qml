import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createNetworkSettingsPresenter(root)

    property alias proxyType: typeItem.currentText
    property alias hostname: hostnameItem.text
    property alias port: portItem.value
    property alias username: usernameItem.text
    property alias password: passwordItem.text

    function setProxyType(proxyType) {
        typeItem.currentIndex = presenter.typeModel.indexOf(proxyType);
    }

    Component.onCompleted: presenter.restore()

    GridLayout {
        columns: 2
        anchors.fill: parent

        Label {
            text: qsTr("Proxy type")
        }

        ComboBox {
            id: typeItem
            model: presenter.typeModel
        }

        Label {
            text: qsTr("Host name")
        }

        TextField {
            id: hostnameItem
            placeholderText: qsTr("Enter hostname")
        }

        Label {
            text: qsTr("Port")
        }

        SpinBox {
            id: portItem
            editable: true
            from: 0
            to: 9999
        }

        Label {
            text: qsTr("User name")
        }

        TextField {
            id: usernameItem
            placeholderText: qsTr("Enter user name")
        }

        Label {
            text: qsTr("User password")
        }

        TextField {
            id: passwordItem
            placeholderText: qsTr("Enter password")
            echoMode: TextInput.Password
        }

        Button {
            text: qsTr("Restore")
            onClicked: presenter.restore()
        }

        Button {
            text: qsTr("Apply")
            onClicked: presenter.apply()
        }
    }
}
