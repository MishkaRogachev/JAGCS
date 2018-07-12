import QtQuick 2.6
import QtQuick.Controls 2.2 as T

T.Drawer {
    id: control

    closePolicy: T.Popup.NoAutoClose
    modal: false
    dragMargin: 0

    background: Rectangle {
        color: customPalette.backgroundColor

        Shadow {
            source: parent
        }
    }
}
