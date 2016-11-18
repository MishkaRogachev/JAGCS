import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

ItemDelegate {
    id: control

    font.pointSize: palette.fontSize

    contentItem: Text {
        text: control.text
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
