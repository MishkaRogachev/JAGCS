import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Drawer {
    id: control

    dragMargin: 0 //sizings.margins NOTE: QTBUG-59141
    closePolicy: T.Popup.NoAutoClose
    modal: false

    background: Rectangle {
        color: palette.backgroundColor
    }
}
