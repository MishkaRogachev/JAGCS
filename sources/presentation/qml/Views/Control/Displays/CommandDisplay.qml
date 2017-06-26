import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

GridLayout {
    id: root

    property bool armed: false

    signal commandArmDisarm(bool arm)

    columns: 2

    Controls.Switch {
        text: armed ? qsTr("DISARM") : qsTr("ARM")
        inputChecked: armed
        onCheckedChanged: commandArmDisarm(checked)
        Layout.fillWidth: true
        Layout.columnSpan: 2
    }
}
