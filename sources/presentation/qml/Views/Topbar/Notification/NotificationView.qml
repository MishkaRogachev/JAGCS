import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: notification

    property string header
    property int urgency: Notification.Common
    property var messages

    property alias time: timer.interval

    signal dropped()

    function drop() {
        if (fadeAnimation.running) fadeAnimation.stop();
        if (timer.running) timer.stop();
        dropped();
    }

    padding: sizings.padding
    height: row.height + padding * 2
    backgroundColor: {
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

    Timer {
        id: timer
        running: true
        onTriggered: fadeAnimation.start()
        onIntervalChanged: {
            stop();
            start();
        }
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

    ColumnLayout {
        id: row
        width: parent.width
        clip: true

        RowLayout {
            Controls.Label {
                text: header
                color: customPalette.selectedTextColor
                Layout.fillWidth: true
            }

            Controls.Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: customPalette.selectedTextColor
                flat: true
                onClicked: drop()
            }
        }

        Repeater {
            model: messages

            Controls.Label {
                text: modelData
                color: customPalette.selectedTextColor
                font.pixelSize: sizings.secondaryFontSize
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }
        }
    }
}
