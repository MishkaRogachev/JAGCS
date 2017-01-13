import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

TabButton {
    id: control

    property alias backgroundColor: backgroundItem.color

    font.pointSize: 11

    background: Rectangle {
        id: backgroundItem
        implicitWidth: palette.controlBaseSize
        implicitHeight: implicitWidth
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        color: {
            if (!enabled) return palette.disabledColor;
            if (control.pressed) return palette.highlightColor;
            if (control.checked) return palette.selectionColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }
    }
}
