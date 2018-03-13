import QtQuick 2.6
import QtQuick.Controls 2.2 as T

T.Drawer {
    id: control

    // NOTE: QTBUG-59141
    closePolicy: T.Popup.NoAutoClose
    modal: false

    background: Rectangle {
        color: palette.backgroundColor
    }
}
