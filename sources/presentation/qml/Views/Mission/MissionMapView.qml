import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    signal picked(var coordinate)

    MouseArea {
        anchors.fill: parent
        onClicked: map.picked(map.toCoordinate(Qt.point(mouseX, mouseY)));
    }
}
