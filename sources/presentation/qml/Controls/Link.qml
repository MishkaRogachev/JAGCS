import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Label {
    id: control

    onLinkActivated: Qt.openUrlExternally(link)

    MouseArea {
        anchors.fill: control
        acceptedButtons: Qt.NoButton
        cursorShape: control.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
