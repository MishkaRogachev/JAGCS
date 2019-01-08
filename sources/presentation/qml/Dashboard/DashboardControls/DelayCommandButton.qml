import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.DelayButton {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: []

    delay: status == Command.Sending ? 0 : 1000
    onActivated: status == Command.Sending ? presenter.rejectCommand(command):
                                             presenter.executeCommand(command, args);
    onStatusChanged: if (status == Command.Completed ||
                         status == Command.Rejected ||
                         status == Command.Canceled) timer.start()
    onCommandChanged: {
        if (timer.running) timer.stop();
        status = Command.Idle;
    }

    backgroundColor: {
        if (status == Command.Rejected) return industrial.colors.danger;
        if (status == Command.Sending) return industrial.colors.caution;
        if (status == Command.Completed) return industrial.colors.positive;
        return control.flat ? "transparent" : industrial.colors.buttonColor;
    }

    textColor: {
        if (status == Command.Rejected ||
            status == Command.Sending ||
            status == Command.Completed) return industrial.colors.selectedTextColor;
        return industrial.colors.onSurface;
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    font.pixelSize: industrial.auxFontSize
    font.bold: true
}
