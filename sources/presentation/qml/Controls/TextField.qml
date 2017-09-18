import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

T.TextField {
    id: control

    font.pixelSize: palette.fontPixelSize
    color: palette.textColor
    selectionColor: palette.selectionColor
    selectedTextColor: palette.selectedTextColor
    selectByMouse: true
    implicitWidth: palette.controlBaseSize * 4
    implicitHeight: palette.controlBaseSize
    padding: palette.margins
    verticalAlignment: Text.AlignVCenter
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }
}
