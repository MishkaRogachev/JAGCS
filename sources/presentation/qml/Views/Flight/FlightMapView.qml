import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    property var vehicleModel

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
