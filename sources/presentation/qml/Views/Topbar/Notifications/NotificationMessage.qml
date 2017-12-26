import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: popup

    property string text: ""
    property int type: 0

    signal dropped()

    function show(message) {
        text = message.message;
        type = message.type;
        opacity = 1.0;
        open();
        startHidingLoop();
    }

    function drop() {
        text = "";
        type = 0;
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
    implicitWidth: row.implicitWidth
    implicitHeight: row.implicitHeight + padding * 2
    closePolicy: Controls.Popup.NoAutoClose

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
            text: popup.text
            color: {
                console.log(type)
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
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/remove.svg"
            flat: true
            onClicked: drop()
        }
    }
}
