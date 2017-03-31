import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

Frame {
    id: root

    property int type: LinkDescription.UnknownType
    property alias name: nameField.text
    property alias typeName: typeBox.currentText
    property alias typeNames: typeBox.model
    property alias port: portBox.value
    property alias device: deviceBox.currentText
    property alias devices: deviceBox.model
    property alias baudRate: baudBox.currentText
    property alias baudRates: baudBox.model
    property alias autoConnect: autoconnectBox.checked

    signal save()
    signal reset()

    GridLayout {
        anchors.fill: parent
        columns: 4
        rowSpacing: palette.spacing

        Label {
            text: qsTr("Name:");
            Layout.fillWidth: true
        }

        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: qsTr("Enter name")
        }

        Label {
            text: qsTr("Type:");
            Layout.fillWidth: true
        }

        ComboBox {
            id: typeBox
            Layout.fillWidth: true
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
        }

        RowLayout {
            Layout.columnSpan: 4

            Item {
                height: parent.height
                Layout.fillWidth: true
            }

            CheckBox {
                id: autoconnectBox
                text: tr("Autoconnect")
            }

            Button {
                text: qsTr("Connect")
            }

            Button {
                text: qsTr("Remove")
            }
        }
    }
}
