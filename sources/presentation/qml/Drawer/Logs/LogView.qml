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
        font.pixelSize: controlSize.secondaryFontSize
        font.bold: true
        color: label.color
    }

    Controls.Label {
        id: label
        text: msg ? msg.head + ": " + msg.message : ""
        font.pixelSize: controlSize.secondaryFontSize
        color: {
            if (!msg) return customPalette.backgroundColor;

            switch (msg.urgency) {
            case Notification.Common: return customPalette.textColor;
            case Notification.Positive: return customPalette.positiveColor;
            case Notification.Warning: return customPalette.cautionColor;
            case Notification.Critical: return customPalette.dangerColor;
            default:
                return customPalette.backgroundColor;
            }
        }
        Layout.fillWidth: true
    }
} 
