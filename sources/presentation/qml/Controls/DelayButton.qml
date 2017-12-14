import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "../Shaders" as Shaders

T.DelayButton {
    id: control

    property alias iconSource: content.iconSource
    property alias iconColor: content.iconColor
    property alias textColor: content.textColor
    property alias backgroundColor: backgroundItem.color
    property string tipText

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: Math.max(sizings.controlBaseSize, content.implicitWidth)
    implicitHeight: Math.max(sizings.controlBaseSize, content.implicitHeight)

    background: Rectangle {
        id: backgroundItem
        anchors.fill: parent
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: 3
        clip: true
        color: control.flat ? "transparent" : palette.buttonColor

        Rectangle {
            radius: parent.radius
            height: parent.height
            width: parent.width * control.progress
            color: palette.highlightColor
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }

        Shadow {
            visible: !control.flat
            source: parent
        }
    }

    contentItem: ContentItem {
        id: content
        text: control.text
        font: control.font
        textColor: progress > 0.5 || control.highlighted ? palette.selectedTextColor: palette.textColor
    }

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
