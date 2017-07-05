import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property var videoSources: []
    property alias videoSource: video.videoSource

    signal selectVideoSource(int index)

    spacing: palette.spacing

    VideoView {
        id: video
        Layout.fillWidth: true
    }

    Controls.Pane {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignBottom
        Layout.maximumHeight: palette.controlBaseSize

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

