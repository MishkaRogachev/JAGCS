import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

    property QtObject presenter: factory.createNetworkSettingsPresenter(root)

    property alias hostname: hostnameItem.text
    property alias port: portItem.value
    property alias username: usernameItem.text
    property alias password: passwordItem.text

    Component.onCompleted: presenter.restore()

    GridLayout {
        columns: 2
        anchors.fill: parent

        Label {
            text: qsTr("Proxy type")
        }

        ComboBox {
            id: typeItem
            textRole: "key"
            model: ListModel {
                ListElement { key: qsTr("No Proxy"); value: 2 }
                ListElement { key: qsTr("Default"); value: 0 }
                ListElement { key: qsTr("SOCKS5"); value: 1 }
                ListElement { key: qsTr("HTTP"); value: 3 }
                ListElement { key: qsTr("Caching HTTP"); value: 4 }
                ListElement { key: qsTr("Caching FTP"); value: 5 }
            }
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
