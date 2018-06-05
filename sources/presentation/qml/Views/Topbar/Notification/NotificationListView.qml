import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ListView {
    id: list

    property ListModel messages: ListModel {}
    property bool running: true

    model: messages
    width: sizings.controlBaseSize * 10
    implicitHeight: contentHeight + sizings.shadowSize
    spacing: sizings.spacing
    flickableDirection: Flickable.AutoFlickIfNeeded
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    Controls.ScrollBar.vertical: Controls.ScrollBar {
        visible: parent.contentHeight > parent.height
    }

    delegate: NotificationView {
        message: msg
        width: parent.width - sizings.shadowSize
        running: list.running
        onDropped: messages.remove(index, 1)
    }
}
