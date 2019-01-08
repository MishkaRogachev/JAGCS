import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Button {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: []

    signal beforeSended()

    onClicked: {
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
    onStatusChanged: {
        if (status == Command.Completed ||
            status == Command.Rejected) timer.start()
    }
    onCommandChanged: {
        if (timer.running) timer.stop();
        status = Command.Idle;
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    backgroundColor: {
        if (status == Command.Rejected) return industrial.colors.danger;
        if (status == Command.Sending) return industrial.colors.caution;
        if (status == Command.Completed) return industrial.colors.positive;
        if (control.pressed) return industrial.colors.highlight;
        return control.flat ? "transparent" : industrial.colors.buttonColor;
    }

    iconColor: control.pressed || status == Command.Rejected ||
               status == Command.Sending || status == Command.Completed ?
                   industrial.colors.selectedTextColor: industrial.colors.onSurface
    textColor: iconColor
    font.pixelSize: industrial.auxFontSize
    font.bold: true
}
