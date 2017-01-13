import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias source: image.source
    property alias color: overlay.color

    width: image.width
    height: image.height

    Image {
        id: image
        anchors.centerIn: parent
        sourceSize.width: parent.width
        sourceSize.height: parent.height
        visible: false
    }

    ColorOverlay {
        id: overlay
        anchors.fill: parent
        source: image
    }
}

