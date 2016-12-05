import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Map"
import "../Map/Overlays"

Pane {
    id: root

    property var missionModel

    MapView { // TODO: MissionMapView
        objectName: "map"
        anchors.fill: parent

        MissionMapOverlayView {
            model: missionModel
        }
    }
}
