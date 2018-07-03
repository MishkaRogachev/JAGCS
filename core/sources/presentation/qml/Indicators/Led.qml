import QtQuick 2.6

import "../Controls" as Controls

Rectangle {
    id: root

    implicitWidth: sizings.controlBaseSize * 0.25
    implicitHeight: width
    radius: width / 2
    opacity: 0.75

    Behavior on color { PropertyAnimation { duration: 100 } }

    Controls.Shadow {
        source: parent
        color: parent.color
    }
}

