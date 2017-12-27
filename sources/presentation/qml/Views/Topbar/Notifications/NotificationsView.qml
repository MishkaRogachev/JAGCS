import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: connection

    property int count: 0
    property var messages: []

    function logAdded(message) {
        if (messagePopup.visible) {
            messages.push(message);
            enabled = true;
            count = messages.length;
        }
        else {
            messagePopup.show(message);
        }
    }

    enabled: false
    // TODO: go to log onClicked:

    NotificationsPresenter {
        id: presenter
        view: connection
    }

    flat: true
    iconSource: "qrc:/icons/notify.svg"
    iconColor: enabled ? palette.textColor : palette.sunkenColor;

    Text {
        anchors.centerIn: parent
        color: parent.iconColor
        font.pixelSize: sizings.fontPixelSize * 0.6
        text: enabled ? count : "!"
    }

    NotificationMessage {
        id: messagePopup
        x: 0
        y: connection.height + sizings.margins
        width: Math.min(implicitWidth, substrate.width - connection.x - sizings.margins)
        onDropped: {
            if (messages.length > 0) messagePopup.show(messages.pop());
            connection.enabled = messages.length;
            count = messages.length;
        }
    }
}
