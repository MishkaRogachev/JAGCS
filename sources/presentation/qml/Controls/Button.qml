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
    property alias textColor: content.textColor
    property alias contentWidth: content.width
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: Math.max(sizings.controlBaseSize, content.implicitWidth)
    implicitHeight: sizings.controlBaseSize

    background: Rectangle {
        id: backgroundItem
        border.color: !control.flat && control.activeFocus ? customPalette.highlightColor : "transparent"
        radius: round ? Math.min(width, height) / 2 : 2
        color: {
            if (control.checked || control.highlighted) return customPalette.selectionColor;
            if (control.pressed | control.pressedImpl) return customPalette.highlightColor;
            return control.flat ? "transparent" : customPalette.buttonColor;
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
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
            textColor: pressed || checked || highlighted ? customPalette.selectedTextColor: customPalette.textColor
        }
    }

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
