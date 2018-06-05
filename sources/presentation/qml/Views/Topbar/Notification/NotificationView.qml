import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: notification

    property var message

    signal dropped()

    function drop() {
        if (fadeAnimation.running) fadeAnimation.stop();
        if (timer.running) timer.stop();
        dropped();
    }

    padding: sizings.padding
    implicitWidth: row.implicitWidth
    implicitHeight: row.height + padding * 2
    backgroundColor: {
        switch (message.type) {
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

    Timer {
        id: timer
        interval: 5000
        running: true
        onTriggered: fadeAnimation.start()
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            notification.opacity = 1.0;
            if (fadeAnimation.running) fadeAnimation.stop();
            if (timer.running) timer.stop();
            timer.start();
        }
    }

    PropertyAnimation on opacity {
        id: fadeAnimation
        duration: 2000
        from: 1.0
        to: 0.0
        running: false
        onStopped: if (!opacity) drop()
    }

    RowLayout {
        id: row
        width: parent.width
        spacing: sizings.spacing
        clip: true

        Controls.Label {
            id: label
            text: message.message
            color: customPalette.selectedTextColor
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/remove.svg"
            iconColor: customPalette.selectedTextColor
            flat: true
            onClicked: drop()
        }
    }
}
