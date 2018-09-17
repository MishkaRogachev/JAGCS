import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: linkList

    property int expandedLinkIndex: -1

    implicitWidth: sizings.controlBaseSize * 10

    onVisibleChanged: drawer.filterEnabled = visible
    Component.onCompleted: if (visible) drawer.filterEnabled = true

    Connections{
        target: drawer
        onFilter: viewModel.filter(text)
    }

    LinkListVm { id: viewModel }

    ListView {
        id: list
        model: viewModel.links
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

                item.viewModel.description = model.link;
                item.minimized = Qt.binding(function() { return expandedLinkIndex != index; });
            }

            Connections {
                target: item
                ignoreUnknownSignals: true

                onMinimize: expandedLinkIndex = -1
                onToggleMaxMin: expandedLinkIndex = item.minimized ? index : -1
                onRemoveRequest: {
                    if (expandedLinkIndex == index) expandedLinkIndex = -1;
                    viewModel.removeLink(model.link);
                }
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
        tipText: qsTr("Add Link")
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            x: (parent.width - width) / 2
            width: list.width

            Repeater {
                model: [
                    { text: qsTr("Serial"), type: LinkDescription.Serial },
                    { text: qsTr("Udp"), type: LinkDescription.Udp },
                    { text: qsTr("Tcp"), type: LinkDescription.Tcp },
                    { text: qsTr("Bluetooth"), type: LinkDescription.Bluetooth },
                ]

                Controls.MenuItem {
                    text: modelData.text
                    implicitWidth: parent.width
                    onTriggered: viewModel.addLink(modelData.type, modelData.text)
                }
            }
        }
    }
}
