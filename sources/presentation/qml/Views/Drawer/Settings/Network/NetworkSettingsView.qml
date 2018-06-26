import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

ColumnLayout {
    id: networkSettings

    property bool changed: false

    property alias type: typeItem.currentText
    property alias hostName: hostNameItem.text
    property alias port: portItem.value
    property alias user: userItem.text
    property alias password: passwordItem.text

    property alias typeModel: typeItem.model

    function setProxyType(proxyType) {
        typeItem.currentIndex = typeModel.indexOf(proxyType);
    }

    Component.onDestruction: if (changed) presenter.updateView()

    anchors.fill: parent
    spacing: sizings.spacing

    NetworkSettingsPresenter {
        id: presenter
        view: networkSettings
        Component.onCompleted: updateView()
    }

    RowLayout {
        spacing: sizings.spacing

        Controls.ComboBox {
            id: typeItem
            labelText: qsTr("Proxy type")
            model: typeModel
            onActivated: changed = true
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: changed
            onSave: presenter.save()
            onRestore: presenter.updateView()
        }
    }

    Controls.TextField {
        id: hostNameItem
        labelText: qsTr("Host name")
        Layout.fillWidth: true
        placeholderText: qsTr("Enter hostname")
        onEditingFinished: changed = true
    }

    Controls.SpinBox {
        id: portItem
        labelText: qsTr("Port")
        Layout.fillWidth: true
        from: 0
        to: 99999
        onValueChanged: changed = true
    }

    Controls.TextField {
        id: userItem
        labelText: qsTr("User name")
        Layout.fillWidth: true
        placeholderText: qsTr("Enter user name")
        onEditingFinished: changed = true
    }

    Controls.TextField {
        id: passwordItem
        labelText: qsTr("User password")
        Layout.fillWidth: true
        placeholderText: qsTr("Enter password")
        echoMode: TextInput.Password
        onEditingFinished: changed = true
    }

    Item { Layout.fillHeight: true }
}
