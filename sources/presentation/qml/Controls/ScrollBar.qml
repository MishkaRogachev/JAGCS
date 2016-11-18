import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

ScrollBar {
    id: control

    contentItem: Rectangle {
        implicitWidth: palette.controlBaseSize / 8
        color: control.active ? palette.selectionColor : "transparent"
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
    }
}
