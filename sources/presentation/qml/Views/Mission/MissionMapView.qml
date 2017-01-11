import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    property var lineModel
    property var pointModel
    property var vehicleModel

    MissionLineMapOverlayView {
        model: lineModel
    }

    MissionPointMapOverlayView {
        model: pointModel
    }

    VehicleMapOverlayView {
        model: vehicleModel
    }
}
