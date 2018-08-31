import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: linkFrame

    property LinkPresenter presenter
    property bool minimized: true

    //    Component.onCompleted: {
    //        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

    //        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
    //        removeItem.iconColor = customPalette.dangerColor;
    //        removeItem.triggered.connect(presenter.remove);
    //    }
    implicitWidth: column.implicitWidth + sizings.margins * 2
    implicitHeight: column.implicitHeight + sizings.margins * 2

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            visible: minimized
            text: presenter.name
            horizontalAlignment: Text.AlignHCenter
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

        Loader {
            id: linkView
            visible: !minimized
            Layout.fillWidth: true
            source: {
                switch (presenter.type) {
                case LinkDescription.Serial: return "SerialLinkEditView.qml";
                case LinkDescription.Udp: return "UdpLinkEditView.qml";
                case LinkDescription.Tcp: return "TcpLinkEditView.qml";
                case LinkDescription.Bluetooth: return "BluetoothLinkEditView.qml";
                default: return "";
                }
            }
        }

        RecvSentRow {
            id: recvSent
            Layout.fillWidth: true
        }
    }

    Controls.Button {
        id: connectButton
        anchors.left: parent.left
        anchors.top: parent.top
        flat: true
        iconSource: presenter.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        iconColor: presenter.connected ? customPalette.positiveColor : customPalette.dangerColor
        tipText: presenter.connected ? qsTr("Disconnect") : qsTr("Connect");
        onClicked: presenter.setConnected(!presenter.connected)
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
