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

//    Component.onCompleted: {
//        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

//        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
//        removeItem.iconColor = customPalette.dangerColor;
//        removeItem.triggered.connect(presenter.remove);
//    }

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

    RowLayout {
        spacing: sizings.spacing
        visible: minimized

        Controls.Label {
            text: {
                switch (presenter.type) {
                case LinkDescription.Serial:
                    return qsTr("Serial");
                case LinkDescription.Udp:
                    return qsTr("UDP");
                case LinkDescription.Tcp:
                    return qsTr("TCP");
                case LinkDescription.Bluetooth:
                    return qsTr("Bluetooth");
                default:
                    return qsTr("Unknown");
                }
            }
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.Label {
            text: presenter.protocol.length ? presenter.protocol : "-"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }
    }

// TODO: types
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
