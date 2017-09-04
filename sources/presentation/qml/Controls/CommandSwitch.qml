import QtQuick 2.6
import JAGCS 1.0

Switch {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle

    Connections {
        target: parent
        onCommandStatusChanged: if (command == control.command) control.status = status
    }

    onCheckedChanged: {
        if (status == Command.Sending) rejectCommand(command);
        else if (inputChecked != checked) executeBoolCommand(command, checked);
    }

    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    backgroundColor: {
        if (status == Command.Rejected) return palette.dangerColor
        if (status == Command.Sending) return palette.cautionColor
        if (status == Command.Completed) return palette.positiveColor
        if (control.inputChecked) return palette.selectionColor;
        return palette.sunkenColor ;
    }
}
