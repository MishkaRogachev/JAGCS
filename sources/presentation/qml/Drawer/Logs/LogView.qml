import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.JS 1.0 as JS
import Industrial.Controls 1.0 as Controls
import JAGCS 1.0

RowLayout {
    id: logView

    property var msg

    LogListPresenter {
        id: presenter
        view: logView
        Component.onCompleted: updateLogs()
    }

    Controls.Label {
        id: timestamp
        anchors.verticalCenter: parent.verticalCenter
        text: msg ? "[" + JS.Helper.formatTime(msg.timestamp) + "]" : ""
        font.pixelSize: industrial.auxFontSize
        font.bold: true
        color: label.color
    }

    Controls.Label {
        id: label
        text: msg ? msg.head + ": " + msg.message : ""
        font.pixelSize: industrial.auxFontSize
        color: {
            if (!msg) return industrial.colors.background;

            switch (msg.urgency) {
            case Notification.Common: return industrial.colors.onSurface;
            case Notification.Positive: return industrial.colors.positive;
            case Notification.Warning: return industrial.colors.caution;
            case Notification.Critical: return industrial.colors.danger;
            default:
                return industrial.colors.background;
            }
        }
        Layout.fillWidth: true
    }
} 
