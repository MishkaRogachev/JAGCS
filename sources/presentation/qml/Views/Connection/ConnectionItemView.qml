import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

RowLayout {
    id: root

    property QtObject presenter

    signal removeMe()

    TextField {
        Layout.fillWidth: true
        text: presenter ? presenter.objectName : qsTr("None")
        onEditingFinished: presenter.objectName = text
    }

    ColumnLayout {
        Button {
            text: qsTr("Up")
            enabled: presenter ? !presenter.isUp : false
            onClicked: presenter.up()
        }

        Button {
            text: qsTr("Down")
            enabled: presenter ? presenter.isUp : false
            onClicked: presenter.down()
        }
    }

    Button {
        text: qsTr("Remove")
        enabled: presenter
        onClicked: removeMe()
    }
}
