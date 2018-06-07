import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "../Shaders" as Shaders

T.DelayButton {
    id: control

    property string tipText
    property bool flat: false

    property alias iconSource: content.iconSource
    property alias textColor: content.textColor
    property alias iconColor: content.iconColor
    property alias backgroundColor: backgroundItem.color

    onActivated: progress = 0

    delay: 1000
    font.pixelSize: sizings.fontSize
    implicitWidth: Math.max(sizings.controlBaseSize, content.implicitWidth)
    implicitHeight: Math.max(sizings.controlBaseSize, content.implicitHeight)

    background: Rectangle {
        id: backgroundItem
        anchors.fill: parent
        border.color: control.activeFocus ? customPalette.highlightColor : "transparent"
        radius: 2
        color: control.flat ? "transparent" : customPalette.buttonColor

        Rectangle {
            anchors.fill: parent
            color: customPalette.textColor
            radius: parent.radius
            opacity: 0.1
            visible: control.hovered
        }

        ContentItem {
            id: content
            anchors.centerIn: parent
            height: parent.height
            text: control.text
            font: control.font
            textColor: customPalette.textColor
        }

        Rectangle {
            radius: parent.radius
            height: parent.height
            width: parent.width * control.progress
            color: customPalette.highlightColor
            clip: true

            ContentItem {
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height
                x: (backgroundItem.width - implicitWidth) / 2
                text: control.text
                font: control.font
                iconSource: control.iconSource
                textColor: customPalette.selectedTextColor
            }
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

    contentItem: Item {}

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
