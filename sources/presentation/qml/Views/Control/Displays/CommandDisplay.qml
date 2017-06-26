import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

GridLayout {
    id: root

    property bool armed: false

    signal commandArmDisarm(bool arm)
    signal commandReturn()
    signal commandStart()
    signal commandJumpTo(int item)

    columns: 2

    Controls.Switch {
        text: armed ? qsTr("DISARM") : qsTr("ARM")
        inputChecked: armed
        onCheckedChanged: commandArmDisarm(checked)
        Layout.fillWidth: true
    }

    RowLayout {
        Layout.fillWidth: true

        Controls.Button {
            iconSource: "qrc:/icons/home.svg"
            onClicked: commandReturn()
        }

        Controls.Button {
            iconSource: "qrc:/icons/play.svg"
            onClicked: commandStart()
        }

        Controls.Button {
            iconSource: "qrc:/icons/right.svg"
            //onClicked: commandJumpTo()
        }
    }
}
