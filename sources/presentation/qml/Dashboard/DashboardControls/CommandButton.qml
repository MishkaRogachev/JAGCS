import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

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
        if (status == Command.Rejected) return Indicators.Theme.dangerColor;
        if (status == Command.Sending) return Indicators.Theme.cautionColor;
        if (status == Command.Completed) return Indicators.Theme.positiveColor;
        if (control.pressed) return industrial.colors.highlight;
        return control.flat ? "transparent" : industrial.colors.buttonColor;
    }

    iconColor: control.pressed || status == Command.Rejected ||
               status == Command.Sending || status == Command.Completed ?
                   industrial.colors.onSelection: industrial.colors.onSurface
    textColor: iconColor
    font.pixelSize: industrial.auxFontSize
    font.bold: true
}
