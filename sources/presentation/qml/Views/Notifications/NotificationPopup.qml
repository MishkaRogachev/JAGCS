import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: popup

    property var message

    signal dropped()

    function show(message) {
        popup.message = message;
        opacity = 1.0;
        open();
        startHidingLoop();
    }

    function drop() {
        if (animation.running) animation.stop();
        if (timer.running) timer.stop();
        close();
        dropped();
    }

    function startHidingLoop() {
        opacity = 1.0;
        if (animation.running) animation.stop();
        if (timer.running) timer.stop();
        timer.start();
    }

    padding: sizings.padding
    implicitWidth: sizings.controlBaseSize * 11
    implicitHeight: row.implicitHeight + padding * 2
    closePolicy: Controls.Popup.NoAutoClose
    clip: true
    backgroundColor: {
        switch (message.type) {
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

    Timer {
        id: timer
        interval: 3000
        onTriggered: animation.start()
    }

    MouseArea {
        anchors.fill: parent
        onPressed: startHidingLoop();
    }

    PropertyAnimation on opacity {
        id: animation
        duration: 2000
        from: 1.0
        to: 0.0
        onStopped: if (!opacity) drop()
    }

    RowLayout {
        id: row
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            id: label
            text: message.message
            color: palette.selectedTextColor
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/remove.svg"
            iconColor: palette.selectedTextColor
            flat: true
            onClicked: drop()
            Layout.alignment: Qt.AlignTop
        }
    }
}
