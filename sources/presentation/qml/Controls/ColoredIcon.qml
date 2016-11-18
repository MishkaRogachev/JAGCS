import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: root

    property alias source: image.source
    property alias sourceSize: image.sourceSize
    property alias color: overlay.color

    width: image.sourceSize.width
    height: image.sourceSize.height

    Image {
        id: image
        anchors.fill: parent
        visible: false
    }

    ColorOverlay {
        id: overlay
        anchors.fill: parent
        source: image
        cached: true
    }
}

