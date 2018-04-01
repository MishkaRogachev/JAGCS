import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

GridLayout {
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

    columns: 2
    anchors.fill: parent
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    NetworkSettingsPresenter {
        id: presenter
        view: networkSettings
        Component.onCompleted: updateView()
    }


    Controls.Label {
        Layout.fillWidth: true
        text: qsTr("Proxy type")
    }

    Controls.ComboBox {
        id: typeItem
        Layout.fillWidth: true
        model: typeModel
        onActivated: changed = true
    }

    Controls.Label {
        Layout.fillWidth: true
        text: qsTr("Host name")
    }

    Controls.TextField {
        id: hostNameItem
        Layout.fillWidth: true
        placeholderText: qsTr("Enter hostname")
        onEditingFinished: changed = true
    }

    Controls.Label {
        Layout.fillWidth: true
        text: qsTr("Port")
    }

    Controls.SpinBox {
        id: portItem
        Layout.fillWidth: true
        from: 0
        to: 99999
        onValueChanged: changed = true
    }

    Controls.Label {
        Layout.fillWidth: true
        text: qsTr("User name")
    }

    Controls.TextField {
        id: userItem
        Layout.fillWidth: true
        placeholderText: qsTr("Enter user name")
        onEditingFinished: changed = true
    }

    Controls.Label {
        Layout.fillWidth: true
        text: qsTr("User password")
    }

    Controls.TextField {
        id: passwordItem
        Layout.fillWidth: true
        placeholderText: qsTr("Enter password")
        echoMode: TextInput.Password
        onEditingFinished: changed = true
    }

    Item {
        Layout.fillHeight: true
    }

    SaveRestore {
        enabled: changed
        onSave: presenter.save()
        onRestore: presenter.updateView()
        Layout.columnSpan: 2
    }
}
