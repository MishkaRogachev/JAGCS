import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Button {
    id: control

    property alias iconSource: content.iconSource
    property alias iconColor: content.iconColor
    property alias textColor: content.textColor
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: palette.fontPixelSize
    implicitWidth: Math.max(backgroundItem.implicitWidth, content.implicitWidth)
    implicitHeight: Math.max(backgroundItem.implicitHeight, content.implicitHeight)
    clip: true

    background: Rectangle {
        id: backgroundItem
        anchors.fill: parent
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: 3
        color: {
            if (control.checked || control.highlighted) return palette.selectionColor;
            if (control.pressed) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }

        Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: ContentItem {
        id: content
        text: control.text
        textColor: pressed || checked || highlighted ? palette.selectedTextColor: palette.textColor
    }
}
