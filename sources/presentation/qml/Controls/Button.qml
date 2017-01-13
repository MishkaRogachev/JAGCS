import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Button {
    id: control

    property alias iconSource: icon.source
    property color iconColor: label.color
    property alias backgroundColor: backgroundItem.color

    font.pointSize: 11

    background: Rectangle {
        id: backgroundItem
        implicitWidth: palette.controlBaseSize
        implicitHeight: implicitWidth
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        color: {
            if (control.checked) return palette.selectionColor;
            if (!enabled) return palette.disabledColor;
            if (control.pressed) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }
    }

    contentItem: Item {
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
                sourceSize.height: control.height * 0.6
                sourceSize.width: sourceSize.height
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
