import QtQuick 2.6
import QtMultimedia 5.6

Rectangle {
    id: root

    property QtObject presenter: factory.createVideoPresenter(root)

    color: "black"

    VideoOutput {
        id: videoOutput
        source: presenter
        anchors.fill: parent
    }
}
