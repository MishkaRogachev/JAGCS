import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

T.Button {
    id: control

    property alias iconSource: content.iconSource
    property alias iconColor: content.iconColor
    property alias textColor: content.textColor
    property alias backgroundColor: backgroundItem.color
    property string tipText

    font.pixelSize: palette.fontPixelSize
    implicitWidth: Math.max(palette.controlBaseSize, content.implicitWidth)
    implicitHeight: Math.max(palette.controlBaseSize, content.implicitHeight)
    clip: true

    background: Rectangle {
        id: backgroundItem
        anchors.fill: parent
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: 3
        color: {
            if (control.checked || control.highlighted) return palette.selectionColor;
            if (control.pressed) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: ContentItem {
        id: content
        text: control.text
        font: control.font
        textColor: pressed || checked || highlighted ? palette.selectedTextColor: palette.textColor
    }

    ToolTip {
        visible: hovered && tipText
        text: tipText
        delay: 1000
    }
}
