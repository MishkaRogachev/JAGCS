import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: connection

    property int count: 0
    property var messages: []

    function logAdded(message) {
        if (messagePopup.visible) {
            messages.push(message);
            count = messages.length;
        }
        else {
            messagePopup.show(message);
        }
    }

    tipText: qsTr("Logbook")
    entry: "../../Menu/Log/LogListView.qml"

    NotificationsPresenter {
        id: presenter
        view: connection
    }

    iconSource: "qrc:/icons/notify.svg"
    iconColor: enabled ? palette.textColor : palette.sunkenColor;

    Text {
        anchors.centerIn: parent
        color: parent.iconColor
        font.pixelSize: sizings.fontPixelSize * 0.6
        text: count
    }

    NotificationMessage {
        id: messagePopup
        x: 0
        y: connection.height + sizings.margins
        width: Math.min(implicitWidth, substrate.width - connection.x - sizings.margins)
        onDropped: {
            if (messages.length > 0) messagePopup.show(messages.pop());
            count = messages.length;
        }
    }
}
