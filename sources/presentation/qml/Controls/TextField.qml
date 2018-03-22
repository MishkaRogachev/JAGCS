import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.TextField {
    id: control

    font.pixelSize: sizings.fontPixelSize
    color: customPalette.textColor
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
    implicitWidth: sizings.controlBaseSize * 4
    implicitHeight: sizings.controlBaseSize
    leftPadding: sizings.padding
    verticalAlignment: Text.AlignVCenter
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: customPalette.sunkenColor
        border.color: control.activeFocus ? customPalette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }
}
