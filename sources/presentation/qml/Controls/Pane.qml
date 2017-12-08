import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Pane {
    id: control

    background: Rectangle {
        id: rect
        anchors.fill: parent
        color: palette.backgroundColor

        Shadow {
            source: parent
        }
    }
}
