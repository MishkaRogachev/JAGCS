import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.ItemDelegate {
    id: control

    font.pixelSize: palette.fontPixelSize
    implicitWidth: palette.controlBaseSize * 4
    implicitHeight: palette.controlBaseSize

    contentItem: Text {
        text: control.text
        padding: palette.margins
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
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
