import QtQuick 2.6

Rectangle {
    id: main
    color: "#37474F"

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 48
    }

    MapView {
        id: map
        anchors.top: status.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }

    VideoView {
        id: video
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 5
        width: parent.width / 3
        height: parent.height / 3
    }
}
