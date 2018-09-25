import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.RealSpinBox {
    id: control

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: [ realValue ]

    font.pixelSize: controlSize.secondaryFontSize
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
        if (status == Command.Rejected) return customPalette.selectedTextColor;
        if (status == Command.Sending) return customPalette.selectedTextColor;
        if (status == Command.Completed) return customPalette.selectedTextColor;
        return customPalette.textColor;
    }

    backgroundColor: {
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        return customPalette.sunkenColor;
    }
}
