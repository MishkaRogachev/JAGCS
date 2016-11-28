import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

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
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Serial device")
                visible: serialDevice.visible
            }

            ComboBox {
                id: serialDevice
                Layout.fillWidth: true
                visible: link ? 'portName' in link : false
                model: serialDevices
                currentIndex: visible ? model.indexOf(link.portName) : 0
                onCurrentIndexChanged: if (visible) link.setPortName(model[currentIndex])
            }

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Baud rate")
                visible: baudRates.visible
            }

            ComboBox {
                id: baudRates
                Layout.fillWidth: true
                visible: link ? 'baudRate' in link : false
                model: serialBaudRates
                currentIndex: link && 'baudRate' in link ?
                                  model.indexOf(link.baudRate) : 0
                onCurrentIndexChanged: if (visible) link.setBaudRate(model[currentIndex])
            }

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Port")
                visible: port.visible
            }

            SpinBox {
                id: port
                Layout.fillWidth: true
                visible: link ? 'port' in link : false
                editable: true
                from: 0
                to: 99999
                value: visible ? link.port : 0
                onValueChanged: if (visible) link.setPort(value)
            }

            CheckBox {
                visible: link ? 'autoResponse' in link : false
                text: qsTr("Auto response")
                checked: visible ? link.autoResponse : false
                onCheckedChanged: if (visible) link.setAutoResponse(checked)
            }
        }

        RowLayout {

            Label {
                iconSource: "qrc:/icons/rx.svg"
                text: (link ? link.bytesReceivedSec : "") + qsTr(" b/s")
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 102
            }

            Label {
                iconSource: "qrc:/icons/tx.svg"
                text: (link ? link.bytesSentSec : "") + qsTr(" b/s")
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 102
            }

            Label {
                visible: link
                text: qsTr("Drops: ") + link.packetsDrops + "/" + link.packetsReceived
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 102
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: link && link.isUp ?
                          qsTr("Disconnect"):
                          qsTr("Connect")
                iconSource: link && link.isUp ?
                                "qrc:/icons/disconnect.svg" :
                                "qrc:/icons/connect.svg"
                onClicked: link && link.isUp ? link.down() : link.up()
                checked: link && link.isUp
            }

            Button {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                enabled: link
                onClicked: requestRemoveLink(link)
            }
        }
    }
}
