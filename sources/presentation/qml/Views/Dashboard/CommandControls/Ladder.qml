import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Indicators" as Indicators

Indicators.Ladder {
    id: root

    property int command: Command.UnknownCommand

    property int newValue: value
    property var args: [newValue]

    property bool controlEnabled: true

    Button {
        iconSource: "qrc:/icons/up.svg"
        flat: true
        x: root.mirrored ? root.width - width : 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -parent.height / 3
        visible: controlEnabled
        command: root.command
        args: root.args
        onBeforeSended: newValue = value + 1
    }

    Button {
        iconSource: "qrc:/icons/down.svg"
        flat: true
        x: root.mirrored ? root.width - width : 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height / 3
        visible: controlEnabled
        command: root.command
        args: root.args
        onBeforeSended: newValue = value - 1
    }
}
