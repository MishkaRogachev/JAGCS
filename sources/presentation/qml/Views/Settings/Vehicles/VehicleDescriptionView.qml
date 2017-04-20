import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

Frame {
    id: root

    property alias name: nameField.text
    property alias mavId: idBox.value

    signal setName(string name)
    signal setMavId(int id)
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
            onValueChanged: setMavId(value)
        }

        Button {
            text: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            onClicked: remove()
            Layout.alignment: Qt.AlignRight
        }
    }
}
