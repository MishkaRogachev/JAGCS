import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.ScrollBar {
    id: control

    implicitWidth: palette.controlBaseSize / 6
    implicitHeight: palette.controlBaseSize / 6

    background: Item { }

    contentItem: Rectangle {
        color: control.active ? palette.selectionColor : "transparent"
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: width / 2
    }
}
