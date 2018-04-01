import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.ScrollBar {
    id: control

    interactive: false
    implicitWidth: sizings.controlBaseSize / 6
    implicitHeight: sizings.controlBaseSize / 6

    background: Item { }

    contentItem: Rectangle {
        color: active && enabled ? customPalette.selectionColor : "transparent"
        radius: width / 2
    }
}
