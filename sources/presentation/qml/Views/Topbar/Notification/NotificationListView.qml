import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ListView {
    id: list

    function addLog(message) {
        messages.append({ "msg": message });
        list.positionViewAtEnd();
    }

    NotificationsPresenter {
        id: presenter
        view: list
    }

    model: ListModel { id: messages }

    width: sizings.controlBaseSize * 10
    height: Math.min(main.height / 2, contentHeight)
    spacing: sizings.spacing
    verticalLayoutDirection: ListView.BottomToTop
    flickableDirection: Flickable.AutoFlickIfNeeded
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    Controls.ScrollBar.vertical: Controls.ScrollBar {
        visible: parent.contentHeight > parent.height
    }

    delegate: NotificationView {
        message: msg
        width: parent.width - sizings.shadowSize
        onDropped: messages.remove(index, 1)
    }
}
