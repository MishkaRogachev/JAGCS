import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: info

    property alias messages: list.messages

    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent
    width: list.width + sizings.margins * 2
    height: list.height + sizings.margins * 2

    NotificationListView {
        id: list
        anchors.centerIn: parent
        height: Math.min(implicitHeight, sizings.controlBaseSize * 8)
        running: false
    }
}
