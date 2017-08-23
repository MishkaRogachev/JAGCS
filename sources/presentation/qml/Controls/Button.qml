import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Button {
    id: control

    property alias iconSource: icon.source
    property color iconColor: textColor
    property color textColor: pressed || checked || highlighted ? palette.selectedTextColor: palette.textColor
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: palette.fontPixelSize
    implicitWidth: Math.max(backgroundItem.implicitWidth, content.implicitWidth)
    implicitHeight: Math.max(backgroundItem.implicitHeight, content.implicitHeight)

    background: Rectangle {
        id: backgroundItem
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

    contentItem: Item {
        id: content
        implicitWidth: row.width
        implicitHeight: row.height

        Row {
            id: row
            anchors.centerIn: parent
            height: parent.availableHeight
            spacing: palette.spacing

            ColoredIcon {
                id: icon
                color: enabled ? iconColor : palette.sunkenColor
                anchors.verticalCenter: parent.verticalCenter
                height: control.height * 0.6
                width: height
                visible: source != ""
            }

            Label {
                id: label
                font: control.font
                text: control.text
                color: enabled ? textColor : palette.sunkenColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
