import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.DelayButton {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: []

    signal beforeSended()

    onActivated: {
        if (status == Command.Sending)
        {
            presenter.rejectCommand(command);
        }
        else
        {
            beforeSended();
            presenter.executeCommand(command, args);
        }
    }
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
        if (status == Command.Rejected) return palette.dangerColor;
        if (status == Command.Sending) return palette.cautionColor;
        if (status == Command.Completed) return palette.positiveColor;
        return control.flat ? "transparent" : palette.buttonColor;
    }

    textColor: {
        if (status == Command.Rejected ||
            status == Command.Sending ||
            status == Command.Completed) return palette.selectedTextColor;
        return palette.textColor;
    }
}
