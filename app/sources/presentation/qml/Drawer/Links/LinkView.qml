import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "../../Common" as Common

Controls.Card {
    id: linkView

    property LinkVm viewModel: LinkVm {}

    default property alias content: contentColumn.children

    property bool minimized: true

    signal removeRequest()
    signal toggleMaxMin()

    function toggleConnected() { viewModel.setConnected(!viewModel.connected); }

    Connections {
        target: viewModel

        onRecv: recvLed.blink()
        onSent: sentLed.blink()
    }

    Common.MvBinding { vm: viewModel; vmProperty: "name"; control: nameField; property: "text" }
    Common.MvBinding { vm: viewModel; vmProperty: "protocol"; control: protocolBox; property: "displayText" }

    deepEnabled: minimized
    contentItem: column

    onDeepIn: toggleMaxMin()
    Component.onCompleted: {
        var minMaxItem = menu.addEntry();
        minMaxItem.triggered.connect(toggleMaxMin);
        minMaxItem.text = Qt.binding(function() {
            return minimized ? qsTr("Maximize") : qsTr("Minimize"); });
        minMaxItem.iconSource = Qt.binding(function() {
            return minimized ? "qrc:/ui/down.svg" : "qrc:/ui/up.svg"; });

        var connectItem = menu.addEntry();
        connectItem.triggered.connect(toggleConnected);
        connectItem.text = Qt.binding(function() {
            return viewModel.connected ? qsTr("Disconnect") : qsTr("Connect"); });
        connectItem.iconSource = Qt.binding(function() {
            return viewModel.connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"; });

        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
        removeItem.iconColor = customPalette.dangerColor;
        removeItem.triggered.connect(removeRequest);
    }

    ColumnLayout {
        id: column
        anchors.fill: parent
        anchors.margins: sizings.margins
        spacing: sizings.spacing

        Controls.Label {
            text: viewModel.name
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
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: protocolBox
                labelText: qsTr("Protocol")
                visible: !minimized
                model: viewModel.availableProtocols
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
                    switch (viewModel.type) {
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
                text: viewModel.protocol.length ? viewModel.protocol : "-"
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
                Layout.columnSpan: 2
            }

            Indicators.BlinkingLed {
                id: recvLed
                blinkColor: customPalette.positiveColor
            }

            Controls.Label {
                text: qsTr("Recv") + ": " + viewModel.bytesRecv.toFixed(1) + " " + qsTr("B/s")
                horizontalAlignment: Text.AlignHCenter
                color: customPalette.positiveColor
                Layout.fillWidth: true
            }

            Indicators.BlinkingLed {
                id: sentLed
                blinkColor: customPalette.skyColor
            }

            Controls.Label {
                text: qsTr("Sent") + ": " + viewModel.bytesSent.toFixed(1) + " " + qsTr("B/s")
                horizontalAlignment: Text.AlignHCenter
                color: customPalette.skyColor
                Layout.fillWidth: true
            }
        }
    }
}
