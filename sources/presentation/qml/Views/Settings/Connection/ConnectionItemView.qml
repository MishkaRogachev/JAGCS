import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

RowLayout {
    id: root

    property QtObject linkItem
    property QtObject presenter

    TextField {
        Layout.fillWidth: true
        text: linkItem ? linkItem.objectName : qsTr("None")
        onEditingFinished: linkItem.objectName = text
    }

    GridLayout {
        id: serialSettings
        columns: 2
        visible: linkItem ? 'portName' in linkItem : false

        Label { text: qsTr("Serial device") }

        ComboBox {
            Layout.fillWidth: true
            enabled: count > 0
            model: presenter.serialDevices
            currentIndex: linkItem && 'portName' in linkItem ?
                              model.indexOf(linkItem.portName) : 0
            onCurrentIndexChanged: if (linkItem && 'portName' in linkItem)
                                       linkItem.setPortName(model[currentIndex])
        }

        Label { text: qsTr("Baud rate") }

        ComboBox {
            Layout.fillWidth: true
            model: presenter.serialBaudRates
            currentIndex: linkItem && 'baudRate' in linkItem ?
                              model.indexOf(linkItem.baudRate) : 0
            onCurrentIndexChanged: if (linkItem && 'baudRate' in linkItem)
                                       linkItem.setBaudRate(model[currentIndex])
        }
    }

    GridLayout {
        id: udpSettings
        columns: 2
        visible: linkItem ? 'rxPort' in linkItem : false

        Label { text: qsTr("Recieve port") }

        SpinBox {
            Layout.fillWidth: true
            editable: true
            from: 0
            to: 99999
            value: linkItem && 'rxPort' in linkItem ? linkItem.rxPort : 0
            onValueChanged: if (linkItem) linkItem.setRxPort(value)
        }

        Label { text: qsTr("Transmit address") }

        TextField {
            Layout.fillWidth: true
            placeholderText: qsTr("Enter address")
            text: linkItem && 'address' in linkItem? linkItem.address : ""
            onTextChanged: if (linkItem) linkItem.setAddress(text)
        }

        Label { text: qsTr("Transmit port") }

        SpinBox {
            Layout.fillWidth: true
            editable: true
            from: 0
            to: 99999
            value: linkItem && 'txPort' in linkItem ? linkItem.txPort : 0
            onValueChanged: if (linkItem) linkItem.setTxPort(value)
        }
    }

    Button {
        text: linkItem && linkItem.isUp ? qsTr("Down") : qsTr("Up")
        onClicked: linkItem && linkItem.isUp ? linkItem.down() : linkItem.up()
        checkable: true
        checked: linkItem && linkItem.isUp
    }

    Button {
        text: qsTr("Remove")
        enabled: linkItem
        onClicked: presenter.removeLink(linkItem)
    }
}
