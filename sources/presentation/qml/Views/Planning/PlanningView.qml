import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "Mission"
import "../Map"

Controls.Pane {
    id: root

    MissionView {
        id: mission
        objectName: "mission"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: mission.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
    }
}
