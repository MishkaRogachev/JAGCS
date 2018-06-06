import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: notificationView

    property int urgency: Notification.Common
    property var notifications

    clickEnabled: list.count > 0
    onClicked: notifications.removeLast()

    NotificationsPresenter {
        id: presenter
        view: notificationView
    }

    Controls.ColoredIcon {
        anchors.centerIn: parent
        source: "qrc:/icons/info.svg"
        color: customPalette.textColor
        visible: list.count == 0
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 2
        radius: height / 2
        visible: list.count > 0
        color: {
            switch (urgency) {
            case Notification.Positive:
                return customPalette.positiveColor;
            case Notification.Warning:
                return customPalette.cautionColor;
            case Notification.Critical:
                return customPalette.dangerColor;
            case Notification.Common:
            default:
                return customPalette.textColor;
            }
        }

        Controls.Label {
            anchors.centerIn: parent
            color: customPalette.selectedTextColor
            text: list.count
        }
    }

    NotificationListView {
        id: list
        y: parent.height + sizings.margins
        model: notifications
        visible: count > 0
        onRemove: notifications.remove(header)
    }
}
