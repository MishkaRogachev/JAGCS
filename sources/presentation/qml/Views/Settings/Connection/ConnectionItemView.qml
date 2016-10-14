import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

RowLayout {
    id: root

    property QtObject link
    property QtObject presenter

    GridLayout {
        columns: 2

        Label {
            text: qsTr("Name")
            Layout.fillWidth: true
        }

        TextField {
            text: link ? link.objectName : qsTr("None")
            onEditingFinished: link.objectName = text
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Serial device")
            Layout.fillWidth: true
            visible: serialDevice.visible
        }

        ComboBox {
            id: serialDevice
            visible: link ? 'portName' in link : false
            Layout.fillWidth: true
            enabled: count > 0
            model: presenter.serialDevices
            currentIndex: link && 'portName' in link ?
                              model.indexOf(link.portName) : 0
            onCurrentIndexChanged: if (link && 'portName' in link)
                                       link.setPortName(model[currentIndex])
        }

        Label {
            text: qsTr("Baud rate")
            Layout.fillWidth: true
            visible: baudRates.visible
        }

        ComboBox {
            id: baudRates
            visible: link ? 'baudRate' in link : false
            Layout.fillWidth: true
            model: presenter.serialBaudRates
            currentIndex: link && 'baudRate' in link ?
                              model.indexOf(link.baudRate) : 0
            onCurrentIndexChanged: if (link && 'baudRate' in link)
                                       link.setBaudRate(model[currentIndex])
        }

        Label {
            text: qsTr("Recieve port")
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

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter

        Button {
            iconSource: link && link.isUp ?
                            "qrc:/icons/connect.svg" :
                            "qrc:/icons/disconnect.svg"
            onClicked: link && link.isUp ? link.down() : link.up()
        }

        Button {
            iconSource: "qrc:/icons/remove.svg"
            enabled: link
            onClicked: presenter.removeLink(link)
        }
    }
}
