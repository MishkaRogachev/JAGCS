import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

Frame {
    id: root

    signal setName(string name)
    signal setId(int id)
    signal remove()

    GridLayout {
        anchors.fill: parent
        columns: 6
        rowSpacing: palette.spacing

        Label {
            text: qsTr("Name:")
        }

        TextField {
            id: nameField
            placeholderText: qsTr("Enter name")
            onEditingFinished: setName(text)
        }

        Label {
            text: qsTr("Id:")
        }

        SpinBox {
            id: idBox
            from: 0
            to: 255
            decimals: 0
            onValueChanged: setId(value)
        }

        Label {
            text: qsTr("Type:")
        }

        ComboBox {
            model: [ qsTr("Fixed Wing") ] // TODO: types
        }

        Button {
            text: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            onClicked: remove()
        }
    }
}
