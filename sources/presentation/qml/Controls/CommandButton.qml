import QtQuick 2.6
import JAGCS 1.0

Button {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle

    Connections {
        target: root
        onCommandStatusChanged: if (command == control.command) control.status = status
    }

    onClicked: status == Command.Sending ? rejectCommand(command) : executeCommand(command)
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    backgroundColor: {
        if (status == Command.Rejected) return palette.negativeColor
        if (status == Command.Sending) return palette.neutralColor
        if (status == Command.Completed) return palette.positiveColor
        if (!enabled) return palette.disabledColor;
        if (control.pressed) return palette.highlightColor;
        return control.flat ? "transparent" : palette.buttonColor;
    }

    iconColor: control.pressed || status == Command.Rejected ||
               status == Command.Sending || status == Command.Completed ?
                   palette.selectedTextColor: palette.textColor
}
