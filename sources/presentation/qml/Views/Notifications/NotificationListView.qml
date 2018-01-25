import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: notificationsList

    function addLog(message) {
        messages.append({ "msg": message });
    }

    NotificationsPresenter {
        id: presenter
        view: notificationsList
    }

    ListView {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: Math.min(sizings.controlBaseSize * 11, notificationsList.width)
        height: Math.min(contentHeight, parent.height)
        clip: true
        model: ListModel { id: messages }
        verticalLayoutDirection: ListView.BottomToTop
        spacing: sizings.spacing

        delegate: NotificationView {
            message: msg
            width: parent.width
            onDropped: messages.remove(index, 1)
        }
    }
}
