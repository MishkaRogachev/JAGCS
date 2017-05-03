import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

TextField {
    id: control

    font.pixelSize: palette.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor

    background: Rectangle {
        implicitWidth: palette.controlBaseWidth
        implicitHeight: palette.controlBaseSize
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
    }
}
