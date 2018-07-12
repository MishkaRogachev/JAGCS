import QtQuick 2.6
import QtQuick.Controls 2.2

import "./"

Pane {
    id: control

    padding: sizings.padding

    background: Rectangle {
        id: rect
        anchors.fill: parent
        color: customPalette.backgroundColor
        radius: 2

        Shadow {
            source: parent
        }
    }
}
