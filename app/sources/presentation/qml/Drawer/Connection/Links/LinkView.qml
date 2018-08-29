import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Controls.Frame {
    id: linkView

    property LinkPresenter presenter

    property bool minimized: true
    property bool recv: false
    property bool sent: false

    function updateProtocol() {
        protocolBox.currentIndex = availableProtocols.indexOf(presenter.protocol)
    }

    Connections {
        target: presenter

        onRecv: recv = true
        onSent: sent = true
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

    implicitWidth: column.implicitWidth + sizings.margins * 2
    implicitHeight: column.implicitHeight + sizings.margins * 2

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

    ColumnLayout {
        id: column
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: linkView.margin
        spacing: sizings.spacing

        Controls.TextField {
            text: presenter.name
            readOnly: minimized
            horizontalAlignment: Text.AlignHCenter
            onEditingFinished: presenter.setName(text)
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                var type = qsTr("Type") + ": ";

                switch (presenter.type) {
                case LinkDescription.Serial:
                    type += qsTr("Serial");
                    break;
                case LinkDescription.Udp:
                    type += qsTr("UDP");
                    break;
                case LinkDescription.Tcp:
                    type += qsTr("TCP");
                    break;
                case LinkDescription.Bluetooth:
                    type += qsTr("Bluetooth");
                    break;
                default:
                    type += qsTr("Unknown");
                    break;
                }

                return type;
            }
            visible: !minimized
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: protocolBox
            labelText: qsTr("Protocol")
            visible: !minimized
            model: availableProtocols
            onDisplayTextChanged: presenter.setProtocol(displayText)
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: sizings.spacing

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

    Controls.Button {
        anchors.left: parent.left
        anchors.top: parent.top
        flat: true
        iconSource: presenter.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        iconColor: presenter.connected ? customPalette.positiveColor : customPalette.dangerColor
        tipText: presenter.connected ? qsTr("Disconnect") : qsTr("Connect");
        onClicked: presenter.setConnected(!presenter.connected)
    }

    Controls.Button {
        anchors.right: parent.right
        anchors.top: parent.top
        flat: true
        iconSource: minimized ? "qrc:/ui/down.svg" : "qrc:/ui/up.svg"
        tipText: minimized ? qsTr("Maximize") : qsTr("Minimize");
        onClicked: minimized = !minimized
    }
}
