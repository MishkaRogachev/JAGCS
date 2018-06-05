import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: notification

    clickEnabled: false// info.messages.count > 0

    onClicked: info.visible ? info.close() : info.open()

    function addLog(message) {
        list.messages.append({ "msg": message });
        list.positionViewAtEnd();

//        //if (message.urgency == Notification.Critical || message.time == 0)
//        {
//            info.messages.append({ "msg": message });

//        }
    }

    NotificationsPresenter {
        id: presenter
        view: notification
    }

    Controls.ColoredIcon {
        anchors.centerIn: parent
        source: "qrc:/icons/info.svg"
        color: clickEnabled ? customPalette.textColor : customPalette.sunkenColor
    }

    NotificationListView {
        id: list
        y: parent.height + sizings.margins
        visible: count > 0
    }

    NotificationInfo {
        id: info
        y: parent.height + sizings.margins
    }
}
