import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: linkList

    property alias availableProtocols: presenter.availableProtocols
    property alias baudRates: presenter.baudRates

    LinkListPresenter {
        id: presenter
    }

    ListView {
        id: list
        model: presenter.links
        anchors.fill: parent
        anchors.margins: sizings.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Controls.Frame {
            id: linkFrame

            property LinkPresenter presenter: model.display
            property bool minimized: true

            width: parent.width
            implicitHeight: linkView.implicitHeight + recvSent.implicitHeight + sizings.margins * 3

            Loader {
                id: linkView
                width: parent.width
                source: {
                    switch (presenter.type) {
                    case LinkDescription.Serial: return "SerialLinkView.qml";
                    case LinkDescription.Udp: return "UdpLinkView.qml";
                    case LinkDescription.Tcp: return "TcpLinkView.qml";
                    case LinkDescription.Bluetooth: return "BluetoothLinkView.qml";
                    default: return "";
                    }
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

            RecvSentRow {
                id: recvSent
                anchors.bottom: parent.bottom
                width: parent.width
            }
        }
    }

    Controls.Label {
        anchors.centerIn: parent
        text: qsTr("No links present")
        visible: list.count === 0
    }

    Controls.RoundButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add Mission")
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            x: (parent.width - width) / 2
            width: list.width

            Controls.MenuItem {
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: presenter.addSerialLink()
            }

            Controls.MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: presenter.addUdpLink()
            }

            Controls.MenuItem {
                text: qsTr("Tcp")
                implicitWidth: parent.width
                onTriggered: presenter.addTcpLink()
            }

            Controls.MenuItem {
                text: qsTr("Bluetooth")
                implicitWidth: parent.width
                onTriggered: presenter.addBluetoothLink()
            }
        }
    }
}
