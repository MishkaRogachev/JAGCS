import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ListView {
    id: list

    signal remove(string header)

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
        property bool last: index == list.count - 1
        onLastChanged: if (last) notification.urgency = urgency
        onUrgencyChanged: if (last) notification.urgency = urgency
        width: parent.width - sizings.shadowSize
        header: model.header
        messages: model.messages
        urgency: model.urgency
        time: model.time
        onDropped: remove(header)
    }
}
