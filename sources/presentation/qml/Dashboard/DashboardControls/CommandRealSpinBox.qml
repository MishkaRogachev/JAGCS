import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

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
        if (status == Command.Rejected) return industrial.colors.onSelection;
        if (status == Command.Sending) return industrial.colors.onSelection;
        if (status == Command.Completed) return industrial.colors.onSelection;
        return industrial.colors.onSurface;
    }

    backgroundColor: {
        if (status == Command.Rejected) return Indicators.Theme.dangerColor;
        if (status == Command.Sending) return Indicators.Theme.cautionColor;
        if (status == Command.Completed) return Indicators.Theme.positiveColor;
        return industrial.colors.background;
    }
}
