import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: []

    Connections {
        target: commander
        onCommandStatusChanged: if (type == command) control.status = status
    }

    onClicked: status == Command.Sending ? commander.rejectCommand(command) :
                                           commander.executeCommand(command, args)
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()
    onCommandChanged: {
        if (timer.running) timer.stop();
        status = Command.Idle;
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    backgroundColor: {
        if (status == Command.Rejected) return palette.dangerColor
        if (status == Command.Sending) return palette.cautionColor
        if (status == Command.Completed) return palette.positiveColor
        if (control.pressed) return palette.highlightColor;
        return control.flat ? "transparent" : palette.buttonColor;
    }

    iconColor: control.pressed || status == Command.Rejected ||
               status == Command.Sending || status == Command.Completed ?
                   palette.selectedTextColor: palette.textColor
}
