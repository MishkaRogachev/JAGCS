import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int mode: Domain.None
    property int status: Command.Idle

    onActivated: commander.executeCommand(Command.SetMode, [ model[index] ])
    onStatusChanged: if (status == Command.Completed || status == Command.Rejected) timer.start()

    Connections {
        target: commander
        onCommandStatusChanged: if (type == Command.SetMode) control.status = status
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    Rectangle {
        z: -1
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
        text: translator.translateMode(modelData)
        font: control.font
        highlighted: control.highlightedIndex === index
    }

    contentItem: RowLayout {
        Controls.ContentItem {
            text: translator.translateMode(mode)
            font: control.font
            textColor: status == Command.Idle ? palette.textColor: palette.selectedTextColor
            Layout.margins: palette.padding
        }

        Item { Layout.fillWidth: true }
    }
}
