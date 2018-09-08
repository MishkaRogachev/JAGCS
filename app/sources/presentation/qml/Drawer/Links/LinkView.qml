import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "../../Common" as Common

Controls.Frame {
    id: linkView

    property LinkProvider provider: LinkProvider {}

    default property alias content: contentColumn.children

    property bool minimized: true

    signal removeRequest()
    signal minimize(bool minimize)

    Connections {
        target: provider

        onRecv: { console.log("recv"); recvLed.blink() }
        onSent: sentLed.blink()
    }

    Common.MvBinding {
        when: nameField.activeFocus
        viewModelProperty: provider.name;
        viewProperty: nameField.text
    }

    implicitWidth: column.implicitWidth + sizings.margins * 2
    implicitHeight: column.implicitHeight + sizings.margins * 2

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            text: provider.name
            visible: minimized
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        ColumnLayout {
            id: contentColumn
            spacing: sizings.spacing
            visible: !minimized

            Controls.TextField {
                id: nameField
                labelText: qsTr("Name")
                readOnly: minimized
                horizontalAlignment: Text.AlignHCenter
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

        GridLayout {
            columns: 4
            rowSpacing: sizings.spacing
            columnSpacing: sizings.spacing
            visible: minimized

            Controls.Label {
                text: {
                    switch (provider.type) {
                    case LinkDescription.Serial: return qsTr("Serial");
                    case LinkDescription.Udp: return qsTr("UDP");
                    case LinkDescription.Tcp: return qsTr("TCP");
                    case LinkDescription.Bluetooth: return qsTr("Bluetooth");
                    default: return qsTr("Unknown");
                    }
                }
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.columnSpan: 2
            }

            Controls.Label {
                text: provider.protocol.length ? provider.protocol : "-"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.columnSpan: 2
            }

            Indicators.BlinkingLed {
                id: recvLed
                blinkColor: customPalette.positiveColor
            }

            Controls.Label {
                text: qsTr("Recv") + ": " + provider.bytesRecv.toFixed(1) + " " + qsTr("B/s")
                horizontalAlignment: Text.AlignHCenter
                color: customPalette.positiveColor
                Layout.fillWidth: true
            }

            Indicators.BlinkingLed {
                id: sentLed
                blinkColor: customPalette.skyColor
            }

            Controls.Label {
                text: qsTr("Sent") + ": " + provider.bytesSent.toFixed(1) + " " + qsTr("B/s")
                horizontalAlignment: Text.AlignHCenter
                color: customPalette.skyColor
                Layout.fillWidth: true
            }
        }

        Controls.DelayButton {
            iconSource: "qrc:/icons/remove.svg"
            text: qsTr("Remove");
            onActivated: removeRequest()
            flat: true
            visible: !minimized
            Layout.fillWidth: true
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
        onClicked: minimize(!minimized)
    }
}
