import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

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

    onLinkIdChanged: presenter.setLink(linkId)
    onDeepIn: edit()

    implicitWidth: grid.implicitWidth + industrial.margins * 2
    implicitHeight: grid.implicitHeight + industrial.margins * 2

    menuItems: [
        Controls.MenuItem {
            text: qsTr("Edit")
            iconSource: "qrc:/icons/edit.svg"
            onTriggered: edit()
        },
        Controls.MenuItem {
            text: connected ? qsTr("Disconnect") : qsTr("Connect")
            iconSource: connected ? "qrc:/icons/disconnect.svg" : "qrc:/icons/connect.svg"
            onTriggered: presenter.setConnected(!connected)
        },
        Controls.MenuItem {
            text: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: industrial.colors.negative
            onTriggered: presenter.remove()
        }
    ]

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
        color: connected ? industrial.colors.positive : industrial.colors.background
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: industrial.margins
        anchors.rightMargin: linkView.margin
        columns: 4
        rowSpacing: industrial.spacing
        columnSpacing: industrial.spacing

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

        Controls.Led {
            color: recv ? industrial.colors.positive : industrial.colors.background
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: industrial.colors.positive
            Layout.fillWidth: true
        }

        Controls.Led {
            color: sent ? Indicators.Theme.skyColor : industrial.colors.background
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: Indicators.Theme.skyColor
            Layout.fillWidth: true
        }
    }
}
