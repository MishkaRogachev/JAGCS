import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Card {
    id: linkView

    property int linkId: 0
    property bool connected: false
    property string name
    property int type: LinkDescription.UnknownType
    property int protocol: LinkDescription.UnknownProtocol
    property real bytesRecv: 0.0
    property real bytesSent: 0.0
    property bool sent: false
    property bool recv: false

    function edit() {
        selectedLinkId = linkId;
    }

    function toggleConnection() {
        presenter.setConnected(!connected)
    }

    onDeepIn: edit()
    Component.onCompleted: {
        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

        var connectItem = menu.addEntry();
        connectItem.triggered.connect(toggleConnection);
        connectItem.text = Qt.binding(function() {
            return connected ? qsTr("Disconnect") : qsTr("Connect"); });
        connectItem.iconSource = Qt.binding(function() {
            return connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"; });

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

    LinkPresenter {
        id: presenter
        view: linkView

        Component.onCompleted: setLink(linkId)
    }

    Controls.ColoredIcon {
        anchors.left: grid.left
        anchors.top: grid.top
        source: connected ? "qrc:/icons/arrow_up.svg" : "qrc:/icons/arrow_down.svg"
        color: connected ? customPalette.positiveColor : customPalette.sunkenColor
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
            text: name
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 4
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (type) {
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
            text: {
                switch (protocol) {
                case LinkDescription.MavLink1: return "MAVLink v1";
                case LinkDescription.MavLink2: return "MAVLink v2";
                case LinkDescription.UnknownProtocol: return qsTr("Unknown");
                default: return qsTr("Unknown");
                }
            }
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Indicators.Led {
            color: recv ? customPalette.positiveColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.positiveColor
            Layout.fillWidth: true
        }

        Indicators.Led {
            color: sent ? customPalette.skyColor : customPalette.sunkenColor
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.skyColor
            Layout.fillWidth: true
        }
    }
}
