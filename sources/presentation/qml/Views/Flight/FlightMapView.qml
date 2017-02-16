import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    MapStatusBar {
        id: bar
        anchors.bottom: parent.bottom
        coordinate: root.mouseCoordinate
        width: parent.width
    }

    TrackMapOverlayView {
        model: vehicleModel
    }

    HdopRadiusMapOverlayView {
        model: vehicleModel
    }
}
