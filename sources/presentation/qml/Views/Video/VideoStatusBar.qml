import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    height: palette.controlBaseSize

    RowLayout {
        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Source:") + videoSource
        }
    }
}
