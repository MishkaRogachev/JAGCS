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

        Label {
            text: qsTr("Serial device")
        }

        ComboBox {
            Layout.fillWidth: true
            model: presenter.serialDevices
            currentIndex: model.indexOf(linkItem.portName)
            onCurrentIndexChanged: linkItem.setPortName(model[currentIndex])
        }

        Label {
            text: qsTr("Baud rate")
        }

        ComboBox {
            Layout.fillWidth: true
            model: presenter.serialBaudRates
            currentIndex: model.indexOf(linkItem.baudRate)
            onCurrentIndexChanged: linkItem.setBaudRate(model[currentIndex])
        }
    }

    ColumnLayout {
        Button {
            text: qsTr("Up")
            enabled: linkItem ? !linkItem.isUp : false
            onClicked: linkItem.up()
        }

        Button {
            text: qsTr("Down")
            enabled: linkItem ? linkItem.isUp : false
            onClicked: linkItem.down()
        }
    }

    Button {
        text: qsTr("Remove")
        enabled: linkItem
        onClicked: presenter.removeLink(linkItem)
    }
}
