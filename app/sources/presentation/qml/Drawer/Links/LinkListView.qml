import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: linkList

    property int expandedLinkIndex: -1

    implicitWidth: sizings.controlBaseSize * 10

    LinkListProvider {
        id: provider
    }

    ListView {
        id: list
        model: provider.links
        anchors.fill: parent
        anchors.margins: sizings.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            source: {
                switch (model.linkType) {
                case LinkDescription.Serial: return "SerialLinkView.qml";
                case LinkDescription.Udp: return "UdpLinkView.qml";
                case LinkDescription.Tcp: return "TcpLinkView.qml";
                case LinkDescription.Bluetooth: return "BluetoothLinkView.qml";
                default: return "LinkView.qml";
                }
            }
            onItemChanged: {
                if (!item) return;

                item.provider.description = model.link;
                item.minimized = Qt.binding(function() { return expandedLinkIndex != index; });
            }

            Connections {
                target: item
                ignoreUnknownSignals: true

                onMinimize: expandedLinkIndex = minimize ? -1 : index
                onRemoveRequest: provider.removeLink(model.link)
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
                onTriggered: provider.addSerialLink()
            }

            Controls.MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: provider.addUdpLink()
            }

            Controls.MenuItem {
                text: qsTr("Tcp")
                implicitWidth: parent.width
                onTriggered: provider.addTcpLink()
            }

            Controls.MenuItem {
                text: qsTr("Bluetooth")
                implicitWidth: parent.width
                onTriggered: provider.addBluetoothLink()
            }
        }
    }
}
