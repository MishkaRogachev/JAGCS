import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: column

    function updateProtocol() {
        protocolBox.currentIndex = availableProtocols.indexOf(presenter.protocol)
    }

    spacing: sizings.spacing

    Connections {
        target: presenter
        onProtocolChanged: updateProtocol()
    }

    Connections {
        target: linkList
        onAvailableProtocolsChanged: updateProtocol()
    }

    Component.onCompleted: updateProtocol()

    Controls.TextField {
        text: presenter.name
        labelText: qsTr("Name")
        readOnly: minimized
        horizontalAlignment: Text.AlignHCenter
        onEditingFinished: presenter.setName(text)
        Layout.leftMargin: connectButton.width
        Layout.rightMargin: minimizeButton.width
        Layout.fillWidth: true
    }

// TODO: edit link type
//    Controls.ComboBox {
//        id: protocolBox
//        labelText: qsTr("Type")
//        visible: !minimized
//        model: availableProtocols
//        onDisplayTextChanged: presenter.setProtocol(displayText)
//        Layout.fillWidth: true
//    }

    Controls.ComboBox {
        id: protocolBox
        labelText: qsTr("Protocol")
        visible: !minimized
        model: availableProtocols
        onDisplayTextChanged: presenter.setProtocol(displayText)
        Layout.fillWidth: true
    }
}
