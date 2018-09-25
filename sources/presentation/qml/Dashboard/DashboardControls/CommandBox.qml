import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

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
    font.pixelSize: controlSize.secondaryFontSize
    font.bold: true

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
            if (status == Command.Rejected) return customPalette.dangerColor;
            if (status == Command.Sending) return customPalette.cautionColor;
            if (status == Command.Completed) return customPalette.positiveColor;
            return "transparent";
        }
    }

    contentItem: Text {
        id: content
        font: control.font
        text: processingText
        color: status == Command.Idle ? customPalette.textColor: customPalette.selectedTextColor
        verticalAlignment: Text.AlignVCenter
        visible: currentIndex != -1
        z: 10
    }
}
