import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.ScrollBar {
    id: control

    contentItem: Rectangle {
        implicitWidth: palette.controlBaseSize / 8
        color: control.active ? palette.selectionColor : "transparent"
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: width / 2
    }
}
