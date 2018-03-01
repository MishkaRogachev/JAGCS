import QtQuick 2.6
import QtMultimedia 5.6

Rectangle {
    id: root

    property alias videoSource: videoOutput.source
    property real ratio: videoOutput.sourceRect.height / videoOutput.sourceRect.width

    implicitWidth: ratio > 0 ? height / ratio : height
    implicitHeight: ratio > 0 ? width * ratio : width

    color: "black"

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }
}
