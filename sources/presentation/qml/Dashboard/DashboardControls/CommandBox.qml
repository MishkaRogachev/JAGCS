import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Controls.ComboBox {
    id: control

    property int status: Command.Idle
    property string processingText: qsTr("Processing")

    function updateCommandStatus(command, status) {
        for (var i = 0; i < model.length; ++i) {
            if (command == model[i].command) {
                control.status = status;
                return;
            }
        }
    }

    currentIndex: -1
    font.pixelSize: industrial.auxFontSize
    font.bold: true
    displayText: processingText
    contentColor: status == Command.Idle ? industrial.colors.onSurface: industrial.colors.onHighlight
    labelColor: {
        if (!enabled) return industrial.colors.disabled;
        return status == Command.Idle ? industrial.colors.onSurface : industrial.colors.onHighlight;
    }
    onActivated: presenter.executeCommand(model[index].command, [])
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    Timer {
        id: timer
        onTriggered: {
            status = Command.Idle;
            currentIndex = -1;
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: 3
        color: {
            if (status == Command.Rejected) return Indicators.Theme.dangerColor;
            if (status == Command.Sending) return Indicators.Theme.cautionColor;
            if (status == Command.Completed) return Indicators.Theme.positiveColor;
            return "transparent";
        }
    }
}
