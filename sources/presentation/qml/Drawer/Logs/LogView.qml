import QtQuick 2.6
import QtQuick.Layouts 1.3
import Industrial.Controls 1.0 as Controls
import JAGCS 1.0

RowLayout {
    id: logView

    property var msg

    // TODO: global helper
    function pad(num, size) {
        var str = num.toString();
        while (str.length < size) str = "0" + str;
        return str;
    }

    function formatTime(time) {
        return pad(time.getHours(), 2) + ":" +
                pad(time.getMinutes(), 2) + ":" +
                pad(time.getSeconds(), 2);
    }

    LogListPresenter {
        id: presenter
        view: logView
        Component.onCompleted: updateLogs()
    }

    Controls.Label {
        id: timestamp
        anchors.verticalCenter: parent.verticalCenter
        text: msg ? "[" + formatTime(msg.timestamp) + "]" : ""
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
            case Notification.Warning: return industrial.colors.neutral;
            case Notification.Critical: return industrial.colors.negative;
            default:
                return industrial.colors.background;
            }
        }
        Layout.fillWidth: true
    }
} 
