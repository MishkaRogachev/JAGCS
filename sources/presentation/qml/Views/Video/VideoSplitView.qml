import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: root

    property var videoSources: []
    property alias videoSource: video.videoSource

    signal selectVideoSource(int index)

    implicitHeight: video.implicitHeight + pane.height

    VideoView {
        id: video
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
    }

    Controls.Pane {
        id: pane
        width: parent.width
        height: palette.controlBaseSize
        anchors.bottom: parent.bottom

        RowLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left

            Controls.ComboBox {
                model: videoSources
                onCurrentIndexChanged: selectVideoSource(currentIndex)
            }
        }
    }
}

