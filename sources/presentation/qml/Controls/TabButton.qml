import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.TabButton {
    id: control

    property alias iconSource: icon.source
    property color iconColor: label.color
    property alias backgroundColor: backgroundItem.color

    font.pixelSize: palette.fontPixelSize
    implicitWidth: Math.max(backgroundItem.implicitWidth, content.implicitWidth)
    implicitHeight: Math.max(backgroundItem.implicitHeight, content.implicitHeight)

    background: Rectangle {
        id: backgroundItem
        implicitWidth: palette.controlBaseSize * 4
        implicitHeight: palette.controlBaseSize
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        color: {
            if (control.checked) return palette.selectionColor;
            if (control.pressed) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }
    }

    contentItem: Item {
        id: content
        // TODO: common content item
        implicitWidth: row.width
        implicitHeight: row.height

        Row {
            id: row
            anchors.centerIn: parent
            height: parent.availableHeight
            spacing: 5

            ColoredIcon {
                id: icon
                color: iconColor
                anchors.verticalCenter: parent.verticalCenter
                height: control.height * 0.6
                width: height
                visible: source != ""
            }

            Label {
                id: label
                font: control.font
                text: control.text
                color: control.pressed || control.checked ?
                           palette.selectedTextColor: palette.textColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
