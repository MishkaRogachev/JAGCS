import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: linkFrame

    property LinkProvider provider: LinkProvider {}

    property bool minimized: true
    property bool changed: false
    default property alias content: contentColumn.children

    signal removeRequest()

    implicitWidth: column.implicitWidth + sizings.margins * 2
    implicitHeight: column.implicitHeight + sizings.margins * 2

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            visible: minimized
            text: provider.name
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: sizings.spacing
            visible: minimized

            Controls.Label {
                text: {
                    switch (provider.type) {
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
                text: provider.protocol.length ? provider.protocol : "-"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
        }

        ColumnLayout {
            id: contentColumn
            spacing: sizings.spacing
            visible: !minimized

            Controls.TextField {
                text: provider.name
                labelText: qsTr("Name")
                readOnly: minimized
                horizontalAlignment: Text.AlignHCenter
                onEditingFinished: provider.setName(text)
                Layout.leftMargin: connectButton.width
                Layout.rightMargin: minimizeButton.width
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: protocolBox
                labelText: qsTr("Protocol")
                visible: !minimized
                model: provider.availableProtocols
                onDisplayTextChanged: provider.setProtocol(displayText)
                Layout.fillWidth: true
            }
        }

        RecvSentRow {
            id: recvSent
            Layout.fillWidth: true
        }

        RowLayout {
            visible: !minimized
            spacing: sizings.spacing

            Controls.Button {
                flat: true
                iconSource: "qrc:/icons/save.svg"
                text: qsTr("Save")
                enabled: changed
                //onClicked:
                Layout.fillWidth: true
            }

            Controls.Button {
                flat: true
                iconSource: "qrc:/icons/restore.svg"
                text: qsTr("Restore")
                enabled: changed
                //onClicked: provider.setConnected(!provider.connected)
                Layout.fillWidth: true
            }

            Controls.DelayButton {
                flat: true
                iconSource: "qrc:/icons/remove.svg"
                text: qsTr("Remove");
                onClicked: listProvider.removeLink(provider.description)
                Layout.fillWidth: true
            }
        }
    }

    Controls.Button {
        id: connectButton
        anchors.left: parent.left
        anchors.top: parent.top
        flat: true
        iconSource: provider.connected ? "qrc:/icons/arrow_up.svg" : "qrc:/icons/arrow_down.svg"
        iconColor: provider.connected ? customPalette.positiveColor : customPalette.sunkenColor
        tipText: provider.connected ? qsTr("Disconnect") : qsTr("Connect");
        onClicked: provider.setConnected(!provider.connected)
    }

    Controls.Button {
        id: minimizeButton
        anchors.right: parent.right
        anchors.top: parent.top
        flat: true
        iconSource: minimized ? "qrc:/ui/down.svg" : "qrc:/ui/up.svg"
        tipText: minimized ? qsTr("Maximize") : qsTr("Minimize");
        onClicked: minimized = !minimized
    }
}
