import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Controls.Card {
    id: linkView

    property LinkPresenter presenter

    property bool recv: false
    property bool sent: false

    function edit() {
        selectedLinkId = linkId;
    }

    function toggleConnection() {
        presenter.setConnected(!presenter.connected)
    }

    Connections {
        target: presenter

        onRecv: recv = true
        onSent: sent = true
    }

    onDeepIn: edit()
    Component.onCompleted: {
        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

        var connectItem = menu.addEntry();
        connectItem.triggered.connect(toggleConnection);
        connectItem.text = Qt.binding(function() {
            return presenter.connected ? qsTr("Disconnect") : qsTr("Connect"); });
        connectItem.iconSource = Qt.binding(function() {
            return presenter.connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"; });

        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
        removeItem.iconColor = customPalette.dangerColor;
        removeItem.triggered.connect(presenter.remove);
    }

    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    Timer {
        running: sent
        interval: 100
        onTriggered: sent = false
    }

    Timer {
        running: recv
        interval: 100
        onTriggered: recv = false
    }

    Controls.ColoredIcon {
        anchors.left: grid.left
        anchors.top: grid.top
        source: presenter.connected ? "qrc:/icons/arrow_up.svg" : "qrc:/icons/arrow_down.svg"
        color: presenter.connected ? customPalette.positiveColor : customPalette.sunkenColor
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: linkView.margin
        columns: 4
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: presenter.name
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 4
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (presenter.type) {
                case LinkDescription.Serial: return qsTr("Serial");
                case LinkDescription.Udp: return qsTr("UDP");
                case LinkDescription.Tcp: return qsTr("TCP");
                case LinkDescription.Bluetooth: return qsTr("Bluetooth");
                default: return qsTr("Unknown");
                }
            }
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: presenter.protocol
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Indicators.Led {
            color: recv ? customPalette.positiveColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + presenter.bytesRecv.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.positiveColor
            Layout.fillWidth: true
        }

        Indicators.Led {
            color: sent ? customPalette.skyColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + presenter.bytesSent.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.skyColor
            Layout.fillWidth: true
        }
    }
}
