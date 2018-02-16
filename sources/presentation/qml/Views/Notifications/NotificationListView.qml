import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: notificationsList

    function addLog(message) {
        messages.append({ "msg": message });
        list.positionViewAtEnd();
    }

    NotificationsPresenter {
        id: presenter
        view: notificationsList
    }

    clip: true

    ListView {
        id: list
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: sizings.shadowSize
        width: Math.min(sizings.controlBaseSize * 11,
                        notificationsList.width) - sizings.shadowSize
        height: Math.min(contentHeight, parent.height)
        spacing: sizings.spacing
        model: ListModel { id: messages }
        verticalLayoutDirection: ListView.BottomToTop
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: NotificationView {
            message: msg
            width: parent.width
            onDropped: messages.remove(index, 1)
        }
    }
}
