import QtQuick 2.6
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

ApplicationWindow {
    visibility: "Maximized"
    visible: true

    header: StatusView {
        id: status
        height: 48
    }

    MapView {
        id: map
        anchors.fill: parent
    }

    VideoView {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: parent.width / 3
        height: parent.height / 3
    }
}
