import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

Frame {
    id: root

    property QtObject link

    ColumnLayout {
        width: parent.width
        spacing: 16

        Label {
            text: link ? link.objectName : qsTr("None")
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        RowLayout {

            Label {
                text: qsTr("Serial device")
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
                visible: serialDevice.visible
            }

            ComboBox {
                id: serialDevice
                visible: link ? 'portName' in link : false
                Layout.fillWidth: true
                model: serialDevices
                currentIndex: link && 'portName' in link ?
                                  model.indexOf(link.portName) : 0
                onCurrentIndexChanged: if (link && 'portName' in link)
                                           link.setPortName(model[currentIndex])
            }

            Label {
                text: qsTr("Baud rate")
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
                visible: baudRates.visible
            }

            ComboBox {
                id: baudRates
                visible: link ? 'baudRate' in link : false
                Layout.fillWidth: true
                model: serialBaudRates
                currentIndex: link && 'baudRate' in link ?
                                  model.indexOf(link.baudRate) : 0
                onCurrentIndexChanged: if (link && 'baudRate' in link)
                                           link.setBaudRate(model[currentIndex])
            }

            Label {
                text: qsTr("Recieve port")
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
                visible: rxPort.visible
            }

            SpinBox {
                id: rxPort
                visible: link ? 'rxPort' in link : false
                Layout.fillWidth: true
                editable: true
                from: 0
                to: 99999
                value: link && 'rxPort' in link ? link.rxPort : 0
                onValueChanged: if (link) link.setRxPort(value)
            }

            Label {
                text: qsTr("Transmit address")
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
                visible: address.visible
            }

            TextField {
                id: address
                visible: link ? 'address' in link : false
                Layout.fillWidth: true
                placeholderText: qsTr("Enter address")
                text: link && 'address' in link ? link.address : ""
                onTextChanged: if (link) link.setAddress(text)
            }

            Label {
                text: qsTr("Transmit port")
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
                visible: txPort.visible
            }

            SpinBox {
                id: txPort
                visible: link ? 'txPort' in link : false
                Layout.fillWidth: true
                editable: true
                from: 0
                to: 99999
                value: link && 'txPort' in link ? link.txPort : 0
                onValueChanged: if (link) link.setTxPort(value)
            }
        }

        RowLayout {

            Label {
                text: qsTr("Rx: ") + (link ? link.bytesReceivedSec : "")
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Tx: ") + (link ? link.bytesSentSec : "")
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
        }

        RowLayout {
            anchors.right: parent.right

            Button {
                iconSource: link && link.isUp ?
                                "qrc:/icons/connect.svg" :
                                "qrc:/icons/disconnect.svg"
                onClicked: link && link.isUp ? link.down() : link.up()
                checked: link && link.isUp
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                enabled: link
                onClicked: requestRemoveLink(link)
            }
        }
    }
}
