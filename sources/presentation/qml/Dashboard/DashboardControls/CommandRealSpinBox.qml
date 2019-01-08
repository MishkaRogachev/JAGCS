import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.RealSpinBox {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: [ realValue ]

    font.pixelSize: industrial.auxFontSize
    font.bold: true

    onValueModified: {
        if (status == Command.Sending)
        {
            presenter.rejectCommand(command);
        }
        presenter.executeCommand(command, args);
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

    color: {
        if (status == Command.Rejected) return industrial.colors.selectedTextColor;
        if (status == Command.Sending) return industrial.colors.selectedTextColor;
        if (status == Command.Completed) return industrial.colors.selectedTextColor;
        return industrial.colors.onSurface;
    }

    backgroundColor: {
        if (status == Command.Rejected) return industrial.colors.danger;
        if (status == Command.Sending) return industrial.colors.caution;
        if (status == Command.Completed) return industrial.colors.positive;
        return industrial.colors.background;
    }
}
