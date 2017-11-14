import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

T.RadioButton {
    id: control

    font.pixelSize: palette.fontPixelSize
    height: palette.controlBaseSize
    leftPadding: 0
    spacing: palette.spacing
    implicitWidth: text.length > 0 ? contentItem.implicitWidth + spacing : indicator.implicitWidth

    indicator: Rectangle {
        implicitWidth: palette.controlBaseSize * 0.8
        implicitHeight: palette.controlBaseSize * 0.8
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: width / 2
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Rectangle {
            anchors.centerIn: parent
            width: parent.width / 2
            height: parent.height / 2
            radius: width / 2
            color: control.down ? palette.highlightColor : palette.selectionColor
            visible: control.checked || control.down
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: Label {
        text: control.text
        font: control.font
        leftPadding: indicator.width + spacing
        verticalAlignment: Text.AlignVCenter
    }
}
