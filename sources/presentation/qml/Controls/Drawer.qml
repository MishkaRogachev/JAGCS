import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Drawer {
    id: control

    dragMargin: sizings.controlBaseSize * 0.5
    closePolicy: Controls.Popup.NoAutoClose
    modal: false

    background: Rectangle {
        color: palette.backgroundColor
    }
}
