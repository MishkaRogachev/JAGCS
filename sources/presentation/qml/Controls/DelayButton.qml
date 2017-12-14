import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "../Shaders" as Shaders

T.DelayButton {
    id: control

    property url iconSource
    property string tipText
    property alias textColor: content.textColor

    property alias backgroundColor: backgroundItem.color

    onActivated: progress = 0

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

        ContentItem {
            id: content
            anchors.centerIn: parent
            text: control.text
            font: control.font
            iconSource: control.iconSource
            textColor: palette.textColor
        }

        Rectangle {
            radius: parent.radius
            height: parent.height
            width: parent.width * control.progress
            color: palette.selectionColor
            clip: true

            ContentItem {
                anchors.verticalCenter: parent.verticalCenter
                x: (backgroundItem.width - width) / 2
                text: control.text
                font: control.font
                iconSource: control.iconSource
                textColor: palette.selectedTextColor
            }
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

    contentItem: Item {}

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
