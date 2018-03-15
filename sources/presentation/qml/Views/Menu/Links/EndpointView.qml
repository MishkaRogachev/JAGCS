import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

RowLayout {
    id: root

    property string endpoint

    signal remove()

    spacing: sizings.spacing

    Controls.Label {
        text: qsTr("Address")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Port")
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    Controls.DelayButton {
        tipText: qsTr("Remove")
        iconSource: "qrc:/icons/remove.svg"
        iconColor: palette.dangerColor
        onActivated: remove()
    }
}

