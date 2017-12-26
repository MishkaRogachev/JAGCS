import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: connection

    property int type: 0
    property var messages: []

    function logAdded(message) {

        if (messagePopup.visible) {
            type = message.type;
            messages.push(message);
            //FIXME : notify messages has changed
        }
        else {
            messagePopup.show(message);
        }
    }

    enabled: messages.length > 0
    onClicked: {
        if (messages.length > 0) messagePopup.show(messages.pop());
        if (messages.length > 0) type = messages[messages.length - 1].type;
    }

    NotificationsPresenter {
        id: presenter
        view: connection
        Component.onCompleted: initLog()
    }

    flat: true
    iconSource: "qrc:/icons/notify.svg"
    iconColor: {
        if (!enabled) return palette.sunkenColor;

        switch (type) {
        case LogMessage.Positive:
            return palette.positiveColor;
        case LogMessage.Warning:
            return palette.cautionColor;
        case LogMessage.Critical:
            return palette.dangerColor;
        case LogMessage.Common:
        default:
            return palette.textColor;
        }
    }

    Text {
        anchors.centerIn: parent
        color: parent.iconColor
        font.pixelSize: sizings.fontPixelSize * 0.6
        text: enabled ? messages.length : "!"
    }

    NotificationMessage {
        id: messagePopup
        x: 0
        y: connection.height + sizings.margins
        width: (menuDrawer.x > 0 ? menuDrawer.x : main.width) - connection.x - sizings.margins
    }
}
