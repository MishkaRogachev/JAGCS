import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: linkView

    property int linkId: 0
    property bool connected: false
    property string name
    property int type: LinkDescription.UnknownType
    property int protocol: LinkDescription.UnknownProtocol
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    contentHeight: grid.height

    LinkPresenter {
        id: presenter
        view: linkView

        Component.onCompleted: setLink(linkId)
    }

    GridLayout {
        id: grid
        anchors.centerIn: parent
        width: parent.width
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: name
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (type) {
                case LinkDescription.Udp: return qsTr("UDP");
                case LinkDescription.Serial: return qsTr("Serial");
                default: return qsTr("Unknown");
                }
            }
            horizontalAlignment: Text.AlignHCenter
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
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Recv") + ": " + bytesRecv.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.positiveColor
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Sent") + ": " + bytesSent.toFixed(1) + " " + qsTr("B/s")
            horizontalAlignment: Text.AlignHCenter
            color: customPalette.skyColor
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Actions")
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight
            enabled: linkId > 0

            Controls.Button {
                tipText: connected ? qsTr("Disconnect") : qsTr("Connect")
                iconSource: connected ? "qrc:/icons/disconnect.svg" :
                                        "qrc:/icons/connect.svg"
                onClicked: presenter.setConnected(!connected)
            }

            Controls.Button {
                tipText: qsTr("Edit link")
                iconSource: "qrc:/icons/edit.svg"
                enabled: linkId > 0
                onClicked: deepIn("qrc:/Views/Drawer/Links/LinkEditView.qml",
                                  name, { "linkId": linkId });
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                iconColor: customPalette.dangerColor
                onActivated: presenter.remove()
            }
        }
    }
}
