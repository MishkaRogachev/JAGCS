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
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        if (control.pressed) return customPalette.highlightColor;
        return control.flat ? "transparent" : customPalette.buttonColor;
    }

    iconColor: control.pressed || status == Command.Rejected ||
               status == Command.Sending || status == Command.Completed ?
                   customPalette.selectedTextColor: customPalette.textColor
    textColor: iconColor
    font.pixelSize: controlSize.secondaryFontSize
    font.bold: true
}
