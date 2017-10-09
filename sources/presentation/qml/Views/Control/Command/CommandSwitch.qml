import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Switch {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle

    Connections {
        target: commander
        onCommandStatusChanged: if (type == command) control.status = status
    }

    onCheckedChanged: {
        if (status == Command.Sending) commander.rejectCommand(command);
        else if (inputChecked != checked) commander.executeCommand(command, [checked]);
    }

    onStatusChanged: {
        if (status == Command.Rejected) checked = inputChecked;
        if (status == Command.Completed || status == Command.Rejected) timer.start();
    }

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
