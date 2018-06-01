import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.TabButton {
    id: control

    property alias iconSource: content.iconSource
    property alias iconColor: content.iconColor
    property alias textColor: content.textColor
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: sizings.fontSize
    implicitWidth: Math.max(backgroundItem.implicitWidth, content.implicitWidth)
    implicitHeight: Math.max(backgroundItem.implicitHeight, content.implicitHeight)
    clip: true

    background: Rectangle {
        id: backgroundItem
        anchors.fill: parent
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize
        border.color: control.activeFocus ? customPalette.highlightColor : "transparent"
        radius: 3
        color: {
            if (control.checked || control.highlighted) return customPalette.selectionColor;
            if (control.pressed) return customPalette.highlightColor;
            return control.flat ? "transparent" : customPalette.buttonColor;
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: ContentItem {
        id: content
        text: control.text
        font: control.font
        textColor: pressed || checked ? customPalette.selectedTextColor: customPalette.textColor
    }
}

