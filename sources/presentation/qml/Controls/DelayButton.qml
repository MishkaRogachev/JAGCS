import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

Button {
    id: control

    property int delay: 1500
    property real progress: 0.0

    signal activated()

    Shaders.Pie {
        anchors.fill: background
        rotation: 90
        angle: progress * Math.PI * 2 - Math.PI
        z: -1
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
                counter.stop();
                activated();
            }
        }
    }

    onPressed: counter.start()
    onCanceled: {
        progress = 0;
        counter.stop();
    }
    onReleased: {
        progress = 0;
        counter.stop();
    }
}
