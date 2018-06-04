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
    property alias hasMenu: menuIndicator.visible
    property alias menuOpened: menuIndicator.opened
    property alias contentWidth: content.width
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: sizings.fontSize
    implicitWidth: Math.max(sizings.controlBaseSize, content.implicitWidth)
    implicitHeight: sizings.controlBaseSize

    background: Rectangle {
        id: backgroundItem
        border.color: !control.flat && control.activeFocus ? customPalette.highlightColor : "transparent"
        radius: round ? Math.min(width, height) / 2 : 2
        color: {
            if (control.pressed | control.pressedImpl) return customPalette.highlightColor;
            if (control.checked || control.highlighted) return customPalette.selectionColor;
            return control.flat ? "transparent" : customPalette.buttonColor;
        }

        MenuIndicator {
            id: menuIndicator
            x: parent.width - width
            y: parent.height - height
            visible: false
            focused: control.activeFocus
        }

        Rectangle {
            anchors.fill: parent
            color: customPalette.textColor
            radius: parent.radius
            opacity: 0.1
            visible: control.hovered
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
            height: sizings.controlBaseSize
            text: control.text
            font: control.font
            textColor: control.pressed || control.checked ||
                       control.highlighted || control.pressedImpl ?
                           customPalette.selectedTextColor: customPalette.textColor
        }
    }

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
