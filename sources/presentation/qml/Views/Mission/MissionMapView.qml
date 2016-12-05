import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    property var lineModel
    property var pointModel

    MissionLineMapOverlayView {
        model: lineModel
    }

    MissionPointMapOverlayView {
        model: pointModel
    }
}
