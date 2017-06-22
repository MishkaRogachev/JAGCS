import QtQuick 2.6

import "../Controls" as Controls

Item {
    id: root

    property real rssi: 0
    property real maxRssiValue: -120

    implicitWidth: palette.controlBaseSize
    implicitHeight: implicitWidth

    Row {
        id: row
        spacing: root.width / 20
        anchors.centerIn: parent

        Repeater {
            id: repeater
            model: 5

            Rectangle {
                anchors.bottom: parent.bottom
                width: root.width / repeater.count - row.spacing
                height: root.height - (repeater.count - index + 1) * root.height /
                        (repeater.count + 2)
                color: maxRssiValue / (repeater.count - index) >= rssi ?
                           palette.selectionColor : palette.disabledColor
            }
        }
    }
}

