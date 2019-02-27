import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.ComboBox {
    id: control

    property int mode: vehicle.mode
    property int status: Command.Idle

    enabled: vehicle.online
    model: vehicle.availableModes
    labelText: qsTr("Mode")
    font.pixelSize: industrial.auxFontSize
    font.bold: true
    displayText: translator.translateVehicleMode(mode)

    onActivated: presenter.executeCommand(Command.SetMode, [ model[index] ])
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()
    currentIndex: {
        for (var i = 0; i < model.length; ++i) {
            if (mode == model[i]) return i; // works only with ==
        }
        return -1;
    }
    labelColor: {
        if (status == Command.Idle) {
            return control.activeFocus ? industrial.colors.highlight :
                                         industrial.colors.onBackground
        }
        return industrial.colors.selectedTextColor;
    }
    backgroundColor: {
        switch (status) {
        case Command.Rejected: return industrial.colors.danger;
        case Command.Sending: return industrial.colors.caution;
        case Command.Completed: return industrial.colors.positive;
        default: return "transparent"
        }
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    delegate: Controls.ItemDelegate {
        width: control.width
        horizontalAlignment: Text.AlignHCenter
        text: translator.translateVehicleMode(modelData)
        font: control.font
        highlighted: control.highlightedIndex === index
    }

    contentItem: Text {
        id: content
        font: control.font
        text: displayText
        color: {
            if (status != Command.Idle) return industrial.colors.surface;
            return industrial.colors.onSurface;
        }
            /*status == Command.Idle ? industrial.colors.onSurface:
                                        industrial.colors.surface*/
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }
}
