import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ListView {
    id: list

    signal remove(string header)

    width: controlSize.controlBaseSize * 10
    implicitHeight: contentHeight + controlSize.shadowSize
    spacing: controlSize.spacing
    flickableDirection: Flickable.AutoFlickIfNeeded
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    Controls.ScrollBar.vertical: Controls.ScrollBar {
        visible: parent.contentHeight > parent.height
    }

    delegate: NotificationView {
        property bool last: index == list.count - 1
        onLastChanged: if (last) notificationView.urgency = urgency
        onUrgencyChanged: if (last) notificationView.urgency = urgency
        width: parent.width - controlSize.shadowSize
        header: model.header
        messages: model.messages
        urgency: model.urgency
        time: model.time
        onDropped: remove(header)
    }
}
