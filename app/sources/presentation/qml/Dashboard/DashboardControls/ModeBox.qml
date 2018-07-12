import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int mode: vehicle.mode
    property int status: Command.Idle

    enabled: vehicle.online
    model: vehicle.availableModes
    labelText: qsTr("Mode")
    font.pixelSize: sizings.secondaryFontSize
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
            return control.activeFocus ? customPalette.highlightColor :
                                         customPalette.secondaryTextColor
        }
        return customPalette.selectedTextColor;
    }
    backgroundColor: {
        switch (status) {
        case Command.Rejected: return customPalette.dangerColor;
        case Command.Sending: return customPalette.cautionColor;
        case Command.Completed: return customPalette.positiveColor;
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
            if (status != Command.Idle) return customPalette.balloonTextColor;
            return customPalette.textColor;
        }
            /*status == Command.Idle ? customPalette.textColor:
                                        customPalette.balloonTextColor*/
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }
}
