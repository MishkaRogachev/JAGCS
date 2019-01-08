import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ListView {
    id: list

    property int maxCount: 5

    signal remove(string header)

    width: industrial.baseSize * 10
    implicitHeight: contentHeight + industrial.shadowSize
    spacing: industrial.spacing
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
        width: parent.width - industrial.shadowSize
        header: model.header
        messages: model.messages
        urgency: model.urgency
        time: model.time
        visible: index < maxCount
        onDropped: remove(header)
    }
}
