import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

TextField {
    id: control

    font.pixelSize: palette.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor
    selectByMouse: true

    background: Rectangle {
        implicitWidth: palette.controlBaseSize * 4
        implicitHeight: palette.controlBaseSize
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
    }
}
