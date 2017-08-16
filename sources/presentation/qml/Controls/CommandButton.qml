import QtQuick 2.6
import JAGCS 1.0

import "./" as Custum

Custum.Button {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property bool boolCommand: false

    Connections {
        target: parent
        onCommandStatusChanged:  if (command == control.command) control.status = status
    }

    onClicked: {
        if (status == Command.Sending) rejectCommand(command);
        else boolCommand ? executeBoolCommand(command, !checked) : executeCommand(command)
    }

    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    backgroundColor: {
        if (status == Command.Rejected) return palette.negativeColor
        if (status == Command.Sending) return palette.neutralColor
        if (status == Command.Completed) return palette.positiveColor
        if (control.checked) return palette.selectionColor;
        if (!enabled) return palette.disabledColor;
        if (control.pressed) return palette.highlightColor;
        return control.flat ? "transparent" : palette.buttonColor;
    }
}
