import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.Button { // TODO: clickable
    id: control

    property bool round: false
    property bool pressedImpl: false
    property string tipText

    property alias iconSource: content.iconSource
    property alias iconScaling: content.iconScaling
    property alias iconColor: content.iconColor
    property alias backgroundColor: backgroundItem.color
    property alias textColor: content.textColor

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: Math.max(sizings.controlBaseSize, content.implicitWidth)
    implicitHeight: sizings.controlBaseSize

    background: Rectangle {
        id: backgroundItem
        border.color: !control.flat && control.activeFocus ? palette.highlightColor : "transparent"
        radius: round ? Math.min(width, height) / 2 : 2
        color: {
            if (control.checked || control.highlighted) return palette.selectionColor;
            if (control.pressed | control.pressedImpl) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled && !control.flat
        }

        Shadow {
            visible: !control.flat
            source: parent
        }
    }

    contentItem: Item {
            ContentItem {
            id: content
            anchors.centerIn: parent
            height: parent.height
            text: control.text
            font: control.font
            textColor: pressed || checked || highlighted ? palette.selectedTextColor: palette.textColor
        }
    }

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
