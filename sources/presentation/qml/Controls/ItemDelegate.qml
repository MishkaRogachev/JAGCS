import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.ItemDelegate {
    id: control

    property alias horizontalAlignment: text.horizontalAlignment

    font.pixelSize: palette.fontPixelSize
    implicitWidth: palette.controlBaseSize * 4
    implicitHeight: palette.controlBaseSize

    contentItem: Text {
        id: text
        text: control.text
        padding: palette.margins
        verticalAlignment: Text.AlignVCenter
        font: control.font
        color: control.highlighted ? palette.selectedTextColor : palette.textColor
    }

    background: Rectangle {
        implicitHeight: palette.controlBaseSize
        border.color: control.activeFocus ? palette.selectionColor : "transparent"
        color: {
            if (control.down) return palette.highlightColor;
            if (control.highlighted) return palette.selectionColor;
            return palette.sunkenColor;
        }
    }
}
