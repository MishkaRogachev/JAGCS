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
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
