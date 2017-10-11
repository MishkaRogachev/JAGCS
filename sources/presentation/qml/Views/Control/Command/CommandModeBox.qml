import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.ComboBox {
    id: control

    property int mode: Domain.None
    onActivated: commander.executeCommand(Command.SetMode, [ model[index] ])

    model: [
        Domain.Manual,
        Domain.Stabilize,
        Domain.Guided,
        Domain.Loiter,
        Domain.Circle,
        Domain.Return,
        Domain.Takeoff,
        Domain.Landing,
        Domain.Mission ] // TODO: available modes for vehicle

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
            Layout.margins: palette.padding
        }

        Item { Layout.fillWidth: true }
    }
}
