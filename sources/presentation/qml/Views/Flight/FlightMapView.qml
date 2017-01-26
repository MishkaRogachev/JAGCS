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

    RadiusMapOverlayView {
        model: pointModel
    }

    AcceptanceRadiusMapOverlayView {
        model: pointModel
    }

    MissionPointMapOverlayView {
        model: pointModel
    }

    TrackMapOverlayView {
        model: vehicleModel
    }

    HomePositionMapOverlayView {
        model: vehicleModel
    }

    VehicleMapOverlayView {
        model: vehicleModel
    }
}
