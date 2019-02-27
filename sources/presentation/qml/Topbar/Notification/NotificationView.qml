import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: notification

    property string header
    property int urgency: Notification.Common
    property var messages

    property alias time: timer.interval

    signal dropped()

    function restart() {
        notification.opacity = 1.0;
        if (fadeAnimation.running) fadeAnimation.stop();
        if (timer.running) timer.stop();
        timer.start();
    }

    function drop() {
        if (fadeAnimation.running) fadeAnimation.stop();
        if (timer.running) timer.stop();
        dropped();
    }

    onMessagesChanged: restart()

    padding: industrial.padding
    height: visible ? row.height + padding * 2 : 0
    backgroundColor: {
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

    Timer {
        id: timer
        running: true
        onTriggered: fadeAnimation.start()
    }

    MouseArea {
        anchors.fill: parent
        onPressed: restart()
    }

    PropertyAnimation on opacity {
        id: fadeAnimation
        duration: 2000
        from: 1.0
        to: 0.0
        running: false
        onStopped: if (!opacity) drop()
    }

    ColumnLayout {
        id: row
        width: parent.width
        clip: true

        RowLayout {
            Controls.Label {
                text: header
                color: industrial.colors.surface
                Layout.fillWidth: true
            }

            Controls.Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: industrial.colors.surface
                flat: true
                onClicked: drop()
            }
        }

        Repeater {
            model: messages

            Controls.Label {
                text: modelData
                color: industrial.colors.surface
                font.pixelSize: industrial.auxFontSize
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }
    }
}
