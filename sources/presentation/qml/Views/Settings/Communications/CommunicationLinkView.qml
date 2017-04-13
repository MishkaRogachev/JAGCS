import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

Frame {
    id: root

    property bool connected: false
    property int type: LinkDescription.UnknownType
    property alias name: nameField.text
    property alias port: portBox.value
    property string device
    property alias devices: deviceBox.model
    property int baudRate
    property alias baudRates: baudBox.model

    signal setName(string name)
    signal setPort(int port)
    signal setDevice(string device)
    signal setBaudRate(int baudRate)
    signal remove()
    signal setConnected(bool connected)

    onDeviceChanged: deviceBox.currentIndex = deviceBox.model.indexOf(device)
    onBaudRateChanged: baudBox.currentIndex = baudBox.model.indexOf(baudRate)

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: palette.spacing

        Label {
            text: qsTr("Type:");
            enabled: false
            Layout.fillWidth: true
        }

        Label {
            Layout.fillWidth: true
            text: {
                switch (type) {
                case LinkDescription.Udp: return qsTr("UDP");
                case LinkDescription.Serial: return qsTr("Serial");
                default: return qsTr("Unknown");
                }
            }
        }

        Label {
            text: qsTr("Name:");
            Layout.fillWidth: true
        }

        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: qsTr("Enter name")
            onEditingFinished: setName(text)
        }

        Label {
            text: qsTr("Port:");
            Layout.fillWidth: true
            visible: type == LinkDescription.Udp
        }

        SpinBox {
            id: portBox
            Layout.fillWidth: true
            from: 0
            to: 65535
            decimals: 0
            visible: type == LinkDescription.Udp
            onValueChanged: setPort(value)
        }

        Label {
            text: qsTr("Device:");
            Layout.fillWidth: true
            visible: type == LinkDescription.Serial
        }

        ComboBox {
            id: deviceBox
            Layout.fillWidth: true
            visible: type == LinkDescription.Serial
            onCurrentTextChanged: setDevice(currentText)
        }

        Label {
            text: qsTr("Baud rate:");
            Layout.fillWidth: true
            visible: type == LinkDescription.Serial
        }

        ComboBox {
            id: baudBox
            Layout.fillWidth: true
            visible: type == LinkDescription.Serial
            onCurrentTextChanged: setBaudRate(currentText)
        }

        RowLayout {
            Layout.columnSpan: 2

            Item {
                height: parent.height
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onClicked: remove()
            }

            Button {
                text: connected ? qsTr("Disconnect") : qsTr("Connect")
                iconSource: connected ? "qrc:/icons/disconnect.svg" :
                                        "qrc:/icons/connect.svg"
                onClicked: setConnected(!connected)
            }
        }
    }
}
