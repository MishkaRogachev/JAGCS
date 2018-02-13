import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property var mode: Command.UnknownCommand
    property int status: Command.Idle

    model: []
    tipText: qsTr("Select mode")
    font.pixelSize: sizings.fontPixelSize * 0.75
    font.bold: true

    onActivated: presenter.executeCommand(Command.SetMode, [ model[index] ])
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()
    currentIndex: {
        for (var i = 0; i < model.length; ++i) {
            if (mode == model[i]) return i; // works only with ==
        }
        return -1;
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    Rectangle {
        anchors.fill: parent
        radius: 3
        color: {
            if (status == Command.Rejected) return palette.dangerColor;
            if (status == Command.Sending) return palette.cautionColor;
            if (status == Command.Completed) return palette.positiveColor;
            return "transparent";
        }
    }

    delegate: Controls.ItemDelegate {
        width: control.width
        horizontalAlignment: control.horizontalAlignment
        text: translator.translateVehicleMode(modelData)
        font: control.font
        highlighted: control.highlightedIndex === index
    }

    contentItem: Text {
        id: content
        font: control.font
        text: translator.translateVehicleMode(mode)
        color: status == Command.Idle ? palette.textColor: palette.selectedTextColor
        verticalAlignment: Text.AlignVCenter
        z: 10
    }
}
