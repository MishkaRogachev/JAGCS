import QtQuick 2.6

import "../Common"

Item {
    id: root

    MapView {
        id: map
        anchors.fill: parent
    }

    VideoView {
        id: video
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: parent.width / 3
        height: parent.height / 3
    }

}
