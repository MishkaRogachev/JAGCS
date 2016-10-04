import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

RowLayout {
    id: root

    property QtObject link
    property QtObject presenter

    TextField {
        Layout.fillWidth: true
        text: link ? link.objectName : qsTr("None")
        onEditingFinished: link.objectName = text
    }

    GridLayout {
        id: serialSettings
        columns: 2
        visible: link ? 'portName' in link : false

        Label { text: qsTr("Serial device") }

        ComboBox {
            Layout.fillWidth: true
            enabled: count > 0
            model: presenter.serialDevices
            currentIndex: link && 'portName' in link ?
                              model.indexOf(link.portName) : 0
            onCurrentIndexChanged: if (link && 'portName' in link)
                                       link.setPortName(model[currentIndex])
        }

        Label { text: qsTr("Baud rate") }

        ComboBox {
            Layout.fillWidth: true
            model: presenter.serialBaudRates
            currentIndex: link && 'baudRate' in link ?
                              model.indexOf(link.baudRate) : 0
            onCurrentIndexChanged: if (link && 'baudRate' in link)
                                       link.setBaudRate(model[currentIndex])
        }
    }

    GridLayout {
        id: udpSettings
        columns: 2
        visible: link ? 'rxPort' in link : false

        Label { text: qsTr("Recieve port") }

        SpinBox {
            Layout.fillWidth: true
            editable: true
            from: 0
            to: 99999
            value: link && 'rxPort' in link ? link.rxPort : 0
            onValueChanged: if (link) link.setRxPort(value)
        }

        Label { text: qsTr("Transmit address") }

        TextField {
            Layout.fillWidth: true
            placeholderText: qsTr("Enter address")
            text: link && 'address' in link? link.address : ""
            onTextChanged: if (link) link.setAddress(text)
        }

        Label { text: qsTr("Transmit port") }

        SpinBox {
            Layout.fillWidth: true
            editable: true
            from: 0
            to: 99999
            value: link && 'txPort' in link ? link.txPort : 0
            onValueChanged: if (link) link.setTxPort(value)
        }
    }

    Button {
        text: link && link.isUp ? qsTr("Down") : qsTr("Up")
        onClicked: link && link.isUp ? link.down() : link.up()
    }

    Button {
        text: qsTr("Remove")
        enabled: link
        onClicked: presenter.removeLink(link)
    }
}
