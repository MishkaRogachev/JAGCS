import QtQuick 2.6

import "../Controls"

ArtificialHorizont {
    id: root

    Label {
        anchors.top: parent.top
        anchors.left: parent.left
        text: qsTr("GS") + (vehicle ? Math.round(vehicle.groundSpeed) : 0.0)
    }

    Label {
        anchors.top: parent.top
        anchors.right: parent.right
        text: vehicle ? Math.round(vehicle.gps.coordinate.altitude) : 0.0
    }
}
