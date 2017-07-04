import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

VideoView {
    id: root

    property var videoSources
    videoSource: videoSource[0]

    Controls.Pane  {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: palette.controlBaseSize

        RowLayout {

            Controls.Button {
                iconSource: "qrc:/icons/left.svg"
            }

            Controls.Button {
                iconSource: "qrc:/icons/right.svg"
            }
        }
    }
}
