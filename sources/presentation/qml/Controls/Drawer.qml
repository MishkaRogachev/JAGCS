import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Drawer {
    id: control

    dragMargin: sizings.margins
    closePolicy: Popup.NoAutoClose
    modal: false

    background: Rectangle {
        color: palette.backgroundColor
    }
}
