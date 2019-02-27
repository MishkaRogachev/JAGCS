import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "../"

TopbarButton {
    id: notificationView

    property int urgency: Notification.Common
    property var notifications

    clickEnabled: list.count > 0
    onClicked: presenter.removeLast()

    NotificationsPresenter {
        id: presenter
        view: notificationView
    }

    Controls.ColoredIcon {
        anchors.centerIn: parent
        width: parent.height * 0.8
        height: parent.height * 0.8
        source: "qrc:/icons/info.svg"
        color: industrial.colors.background
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
                return industrial.colors.positive;
            case Notification.Warning:
                return industrial.colors.neutral;
            case Notification.Critical:
                return industrial.colors.negative;
            case Notification.Common:
            default:
                return industrial.colors.onSurface;
            }
        }

        Controls.Label {
            anchors.centerIn: parent
            color: industrial.colors.surface
            font.pixelSize: industrial.auxFontSize
            font.bold: true
            text: list.count
        }
    }

    NotificationListView {
        id: list
        y: parent.height + industrial.margins
        model: notifications
        visible: count > 0
        onRemove: presenter.remove(header)
    }
}
