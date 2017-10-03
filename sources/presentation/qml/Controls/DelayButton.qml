import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

Button {
    id: control

    property int delay: 1500
    property real progress: 0.0

    signal activated()

    background: Rectangle {
        anchors.fill: parent
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        radius: 3
        clip: true
        color:  control.flat ? "transparent" : palette.buttonColor;

        Shaders.Pie {
            anchors.centerIn: parent
            width: parent.height
            height: parent.width
            rotation: 90
            angle: progress * Math.PI * 2
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    Timer {
        id: counter
        repeat: true
        interval: delay / 100
        onTriggered: {
            if (progress < 1)
            {
                progress += 0.01;
            }
            else
            {
                progress = 0;
                control.stop();
                control.activated();
            }
        }
    }

    onPressed: start()
    onCanceled: stop()
    onReleased: stop()
    onVisibleChanged: if (!visible) stop()
    onEnabledChanged: if (!enabled) stop()

    function start() {
        progress = 0;
        counter.start();
    }

    function stop() {
        progress = 0;
        counter.stop();
    }
}
